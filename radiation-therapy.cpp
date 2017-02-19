#include <iostream>
#include <vector>

#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>

typedef CGAL::Gmpzf ET;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int nH, nT, N, lastDeg;
vector<int> edge;
vector< vector<double> > p;
vector< vector<double> > x, y, z;
Program lp;

void featureMapping(int deg) {

	edge.clear();
	for (int i = 0; i <= deg; ++i) {
		for (int dx = 0; dx <= i; ++dx) {
			for (int dy = 0; dy <= (i - dx); ++dy) {
				int dz = i - dx - dy;
				for (int j = 0; j < p.size(); ++j) {
					p[j].push_back(x[j][dx] * y[j][dy] * z[j][dz]);
				}
			}
		}
		edge.push_back(p[0].size());
	}

}

void resetProgram() {

	lp = Program(CGAL::LARGER, false, 0.0, false, 0.0);
	for (int i = 0; i < N; ++i) {
		lp.set_a(0, i, -1.0);
		if (i < nH) {
			lp.set_a(1, i, 1.0);
		} else {
			lp.set_a(1, i, -1.0);
		}
		lp.set_b(i, 0);
	}
	lp.set_c(0, -1.0);
	lp.set_l(0, true, 0.0);

}

bool work(int deg) {

	if (deg >= lastDeg) {

		for (int i = 0; i < nH; ++i) {
			for (int j = edge[lastDeg]; j < edge[deg]; ++j) {
				lp.set_a(j + 1, i, p[i][j]);
			}
		}
		for (int i = nH; i < N; ++i) {
			for (int j = edge[lastDeg]; j < edge[deg]; ++j) {
				lp.set_a(j + 1, i, -p[i][j]);
			}
		}

	} else {

		resetProgram();
		for (int i = 0; i < nH; ++i) {
			for (int j = 1; j < edge[deg]; ++j) {
				lp.set_a(j + 1, i, p[i][j]);
			}
		}
		for (int i = nH; i < N; ++i) {
			for (int j = 1; j < edge[deg]; ++j) {
				lp.set_a(j + 1, i, -p[i][j]);
			}
		}

	}
	lastDeg = deg;

	CGAL::Quadratic_program_options options;
	options.set_pricing_strategy(CGAL::QP_BLAND);
	Solution s = CGAL::solve_linear_program(lp, ET(), options);

	if (s.is_unbounded()) {
		return true;
	}
	if (s.is_optimal()) {
		if (CGAL::to_double(s.objective_value()) > 0) {
			return true;
		}
	}
	return false;

}

void radiation() {

	cin >> nH >> nT;
	N = nH + nT;

	x.clear(); x.resize(N, vector<double>(31, 1));
	y.clear(); y.resize(N, vector<double>(31, 1));
	z.clear(); z.resize(N, vector<double>(31, 1));
	p.clear(); p.resize(N);

	for (int i = 0; i < N; ++i) {
		cin >> x[i][1] >> y[i][1] >> z[i][1];
		for (int d = 2; d <= 30; ++d) {
			x[i][d] = x[i][1] * x[i][d - 1];
			y[i][d] = y[i][1] * y[i][d - 1];
			z[i][d] = z[i][1] * z[i][d - 1];
		}
	}

	if (nH * nT == 0) {
		cout << "0" << endl;
		return;
	}

	featureMapping(30);
	resetProgram();
	lastDeg = 0;

	vector<int> deg, test(6, -1);
	for (int i = 1; i <= 16; i *= 2) {
		deg.push_back(i);
	}
	deg.push_back(30);

	test[0] = work(deg[0]);
	if (test[0]) {
		cout << deg[0] << endl;
		return;
	}

	for (int i = 1; i < 6; ++i) {
		test[i] = work(deg[i]);
		if (!test[i - 1] && test[i]) {
			int l = deg[i - 1], r = deg[i];
			while (l < r) {
				int mid = (l + r) / 2;
				if (work(mid)) {
					r = mid;
				} else {
					l = mid + 1;
				}
			}
			cout << l << endl;
			return;
		}
	}
	cout << "Impossible!" << endl;

}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		radiation();
	}
}