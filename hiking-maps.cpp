#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <vector>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

using namespace std;

void hiking_maps() {

	int m, n;
	cin >> m >> n;
	int nLeg = m - 1;

	vector<K::Point_2> turn(m);
	vector< vector<int> > map(n);

	for (int i = 0; i < m; ++i) {
		cin >> turn[i];
	}

	vector< vector<int> > legMap(n);
	vector< vector<bool> > turnMap(n, vector<bool>(m));
	for (int i = 0; i < n; ++i) {
		vector<K::Point_2> point(6);
		for (int j = 0; j < 6; ++j) {
			cin >> point[j];
		}
		int flag1 = CGAL::orientation(point[0], point[1], point[2]);
		int flag2 = CGAL::orientation(point[2], point[3], point[4]);
		int flag3 = CGAL::orientation(point[4], point[5], point[0]);

		for (int j = 0; j < m; ++j) {
			int flag4 = CGAL::orientation(point[0], point[1], turn[j]);
			int flag5 = CGAL::orientation(point[2], point[3], turn[j]);
			int flag6 = CGAL::orientation(point[4], point[5], turn[j]);

			bool flag7 = (flag4 == CGAL::COLLINEAR) || (flag4 == flag1);
			bool flag8 = (flag5 == CGAL::COLLINEAR) || (flag5 == flag2);
			bool flag9 = (flag6 == CGAL::COLLINEAR) || (flag6 == flag3);

			turnMap[i][j] = flag7 && flag8 && flag9;
		}

		for (int j = 0; j < m - 1; ++j) {
			if (turnMap[i][j] && turnMap[i][j + 1]) {
				legMap[i].push_back(j);
			}
		}
	}

	int minCost = n, count = 0;
	vector<int> legNum(nLeg, 0);
	int l = 0, r = 0;
	for (int i = 0; i < legMap[l].size(); ++i) {
		count += (legNum[legMap[l][i]] == 0);
		legNum[legMap[l][i]] += 1;
	}

	while (l < n) {
		if (count < nLeg) {
			if (r < n - 1) {
				++r;
				for (int i = 0; i < legMap[r].size(); ++i) {
					count += (legNum[legMap[r][i]] == 0);
					legNum[legMap[r][i]] += 1;
				}
			} else {
				break;
			}
		} else if (count == nLeg) {
			minCost = min(minCost, r - l + 1);
			for (int i = 0; i < legMap[l].size(); ++i) {
				legNum[legMap[l][i]] -= 1;
				count -= (legNum[legMap[l][i]] == 0);
			}
			++l;
		} else {
			cout << "ERROR!" << endl;
			return;
		}
	}

	cout << minCost << endl;

}

int main() {
	std::ios_base::sync_with_stdio(false);
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		hiking_maps();
	}
	return 0;
}
