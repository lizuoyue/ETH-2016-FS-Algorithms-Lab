#include <iostream>
#include <climits>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Vertex_handle Vertex_handle;

#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>

typedef CGAL::Gmpzf ET;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

void strikesback() {

	int nP, nS, nH;
	double totalE;
	cin >> nP >> nS >> nH >> totalE;

	vector<double> density(nP);
	vector<K::Point_2> particle(nP);
	for (int i = 0; i < nP; ++i) {
		cin >> particle[i] >> density[i];
	}

	vector<K::Point_2> shoot(nS);
	for (int i = 0; i < nS; ++i) {
		cin >> shoot[i];
	}

	vector<K::Point_2> hunter(nH);
	for (int i = 0; i < nH; ++i) {
		cin >> hunter[i];
	}

	Triangulation tri;
	tri.insert(hunter.begin(), hunter.end());

	vector<double> rSquare(nS);
	if (nH > 0) {
		for (int i = 0; i < nS; ++i) {
			Vertex_handle p = tri.nearest_vertex(shoot[i]);
			rSquare[i] = CGAL::to_double(CGAL::squared_distance(p->point(), shoot[i]));
		}
	} else {
		for (int i = 0; i < nS; ++i) {
			rSquare[i] = DBL_MAX;
		}
	}

	Program lp(CGAL::LARGER, true, 0.0, false, 0.0);
	for (int i = 0; i < nP; ++i) {
		for (int j = 0; j < nS; ++j) {
			double dSquare = CGAL::to_double(CGAL::squared_distance(particle[i], shoot[j]));
			if (dSquare <= 1.0) {
				lp.set_a(j, i, 1.0);
			} else if (dSquare <= rSquare[j]) {
				lp.set_a(j, i, 1.0 / dSquare);
			} else {
				lp.set_a(j, i, 0.0);
			}
		}
		lp.set_b(i, density[i]);
	}

	for (int j = 0; j < nS; ++j) {
		lp.set_a(j, nP, -1.0);
	}
	lp.set_b(nP, -totalE);

	for (int j = 0; j < nS; ++j) {
		lp.set_c(j, 1.0);
	}

	Solution s = CGAL::solve_linear_program(lp, ET());
	if (s.is_infeasible()) {
		cout << "n" << endl;
	} else {
		cout << "y" << endl;
	}
}


int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		strikesback();
	}
}