#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Gmpzf ET;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

void stamps() {

	int nLamp, nStamp, nWall;
	cin >> nLamp >> nStamp >> nWall;

	vector<K::Point_2> lamp(nLamp);
	for (int i = 0; i < nLamp; i++) {
		cin >> lamp[i];
	}

	vector<K::Point_2> stamp(nStamp);
	vector<int> maxLight(nStamp);
	for (int i = 0; i < nStamp; i++) {
		cin >> stamp[i] >> maxLight[i];
	}

	vector<K::Segment_2> wall(nWall);
	for (int i = 0; i < nWall; i++) {
		K::Point_2 source, target;
		cin >> source >> target;
		wall[i] = K::Segment_2(source, target);
	}

	Program lp(CGAL::SMALLER, true, 1, true, (1 << 12));
	for (int i = 0; i < nStamp; i++) {
		for (int j = 0; j < nLamp; j++) {
			int flag = 1;
			for (int k = 0; k < nWall; k++) {
				K::Segment_2 seg = K::Segment_2(stamp[i], lamp[j]);
				if (CGAL::do_intersect(seg, wall[k])) {
					flag = 0;
					break;
				} 
			}
			double dist = CGAL::to_double(CGAL::squared_distance(stamp[i], lamp[j]));
			double coef = double(flag) / dist;

			lp.set_a(j, i * 2, coef);
			lp.set_a(j, i * 2 + 1, coef);

			//cout << coef << " ";
		}
		lp.set_b(i * 2, maxLight[i]);
		lp.set_b(i * 2 + 1, 1.0);
		lp.set_r(i * 2 + 1, CGAL::LARGER);
		//cout << endl;
	}
	lp.set_c0(1);

	Solution s = CGAL::solve_linear_program(lp, ET());
	if (s.is_infeasible()) {
		cout << "no" << endl;
	} else {
		cout << "yes" << endl;
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		stamps();
	}
	return 0;
}
