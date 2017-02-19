#include <iostream>
#include <climits>

#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>

typedef CGAL::Gmpzf ET;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

bool work(Program &qp, int risk, int reward) {

	qp.set_b(1, reward);

	Solution s = CGAL::solve_quadratic_program(qp, ET());

	if (!s.is_infeasible() && s.is_optimal()) {
		double trueRisk = CGAL::to_double(s.objective_value());
		return (trueRisk <= risk);
	} else {
		return false;
	}

}

void portfolios(int n, int m) {

	vector<int> c(n), r(n);
	vector< vector<int> > v(n, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		cin >> c[i] >> r[i];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> v[i][j];
		}
	}

	Program qp(CGAL::LARGER, true, 0.0, false, 0.0);
	for (int i = 0; i < n; ++i) {
		qp.set_a(i, 0, -c[i]);
		qp.set_a(i, 1, r[i]);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			qp.set_d(i, j, v[i][j] * 2.0);
		}
	}

	for (int i = 0; i < m; ++i) {
		int cost, risk;
		cin >> cost >> risk;
		qp.set_b(0, -cost);

		int l = 0, r = INT_MAX - 1;
		while (l < r) {
			int mid = (l + r + 1) / 2;
			if (work(qp, risk, mid)) {
				l = mid;
			} else {
				r = mid - 1;
			}
		}
		cout << l << endl;
	}
	return;

}

int main(void) {
	int n, m;
	cin >> n >> m;
	while (!(n == 0 && m == 0)) {
		portfolios(n, m);
		cin >> n >> m;
	}
	return 0;
}
