#include <iostream>
#include <vector>
#include <cmath>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Vertex_handle Vertex_handle;

using namespace std;

void light() {

	int nPeople, nLight;
	cin >> nPeople >> nLight;

	vector<K::Point_2> people(nPeople);
	vector<int> radius(nPeople);
	for (int i = 0; i < nPeople; i++) {
		cin >> people[i] >> radius[i];
	}

	int height;
	cin >> height;

	vector<K::Point_2> light(nLight);
	for (int i = 0; i < nLight; i++) {
		cin >> light[i];
	}

	Triangulation tri;
	tri.insert(light.begin(), light.end());

	int flag = 0;
	for (int i = 0; i < nPeople; i++) {
		Vertex_handle targetLight = tri.nearest_vertex(people[i]);
		K::Point_2 tl = targetLight->point();
		double dist = sqrt(CGAL::to_double(CGAL::squared_distance(tl, people[i])));
		if (dist >= double(radius[i] + height)) {
			flag = 1;
			cout << i << " ";
		}
	}
	if (flag == 1) {
		cout << endl;
	} else {
		int left = 0;
		int right = nLight - 1;
		while (left < right) {
			int mid = (left + right + 1) / 2;
			Triangulation tempTri;
			tempTri.insert(&light[0], &light[mid]);

			int tempFlag = 0;
			for (int i = 0; i < nPeople; i++) {
				Vertex_handle targetLight = tempTri.nearest_vertex(people[i]);
				K::Point_2 tl = targetLight->point();
				double dist = sqrt(CGAL::to_double(CGAL::squared_distance(tl, people[i])));
				if (dist >= double(radius[i] + height)) {
					tempFlag = 1;
					break;
				}
			}

			if (tempFlag) {
				left = mid;
			} else {
				right = mid - 1;
			}
		}

		Triangulation tempTri;
		tempTri.insert(&light[0], &light[left]);
		for (int i = 0; i < nPeople; i++) {
			Vertex_handle targetLight = tempTri.nearest_vertex(people[i]);
			K::Point_2 tl = targetLight->point();
			double dist = sqrt(CGAL::to_double(CGAL::squared_distance(tl, people[i])));
			if (dist >= double(radius[i] + height)) {
				cout << i << " ";
			}
		}
		cout << endl;
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		light();
	}
	return 0;
}
