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

void work(int p, int a, int b) {

	if (p == 1) {
		Program qp(CGAL::SMALLER, true, 0, false, 0);
		const int x = 0;
		const int y = 1;

		qp.set_a(x, 0, 1);
		qp.set_a(y, 0, 1);
		qp.set_b(   0, 4);

		qp.set_a(x, 1, 4);
		qp.set_a(y, 1, 2);
		qp.set_b(   1, a * b);

		qp.set_a(x, 2, -1);
		qp.set_a(y, 2, 1);
		qp.set_b(   2, 1);

		qp.set_d(x, x, a + a);
		qp.set_c(y, -b);

		Solution s = CGAL::solve_quadratic_program(qp, ET());
		if (s.is_optimal()) {
			cout << int(floor(-CGAL::to_double(s.objective_value()))) << endl;
		} else {
			if (s.is_infeasible()) {
				cout << "no" << endl;
			} else {
				cout << "unbounded" << endl;
			}
		}
	}

	if (p == 2) {
		Program qp(CGAL::LARGER, false, 0, false, 0);
		const int x = 0;
		const int y = 1;
		const int z = 2;

		qp.set_u(x, true, 0); qp.set_u(y, true, 0); qp.set_l(z, true, 0);

		qp.set_a(x, 0, 1); qp.set_a(y, 0, 1); qp.set_b(0, -4);
		qp.set_a(x, 1, 4); qp.set_a(y, 1, 2); qp.set_a(z, 1, 1); qp.set_b(1, -a * b);
		qp.set_a(x, 2, -1); qp.set_a(y, 2, 1); qp.set_b(2, -1);

		qp.set_d(x, x, a + a);
		qp.set_d(z, z, 2);
		qp.set_c(y, b);

		Solution s = CGAL::solve_quadratic_program(qp, ET());
		if (s.is_optimal()) {
			cout << int(ceil(CGAL::to_double(s.objective_value()))) << endl;
		} else {
			if (s.is_infeasible()) {
				cout << "no" << endl;
			} else {
				cout << "unbounded" << endl;
			}
		}
	}
}

int main(void) {
	int p, a, b;
	cin >> p;
	while (p) {
		cin >> a >> b;
		work(p, a, b);
		cin >> p;
	}
}
