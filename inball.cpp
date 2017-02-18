#include <iostream>
#include <cmath>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void inball(int n, int d) {

	vector< vector<int> > A(n, vector<int>(d));
	vector<int> B(n);
	vector<int> norm(n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++) {
			cin >> A[i][j];
			norm[i] += A[i][j] * A[i][j];
		}
		cin >> B[i];
		norm[i] = sqrt(norm[i]);
	}

	Program lp(CGAL::SMALLER, false, 0, false, 0);
	const int R = d;

	lp.set_l(R, true, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++) {
			lp.set_a(j, i, A[i][j]);
		}
		lp.set_a(R, i, norm[i]);
		lp.set_b(i, B[i]);
	}
	lp.set_c(R, -1);

	Solution s = CGAL::solve_linear_program(lp, ET());
	if (s.is_optimal()) {
		cout << int(floor(-CGAL::to_double(s.objective_value()))) << endl;
	} else {
		if (s.is_infeasible()) {
			cout << "none" << endl;
		} else {
			cout << "inf" << endl;
		}
	}
}

int main(void) {
	int n, d;
	cin >> n;
	while (n) {
		cin >> d;
		inball(n, d);
		cin >> n;
	}
}
