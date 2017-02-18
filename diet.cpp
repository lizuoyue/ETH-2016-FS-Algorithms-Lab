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

void diet(int n, int m) {

	vector<int> minimum(n);
	vector<int> maximum(n);
	for (int i = 0; i < n; i++) {
		cin >> minimum[i] >> maximum[i];
	}

	vector<int> price(m);
	vector< vector<int> > table(m, vector<int>(n));
	for (int i = 0; i < m; i++) {
		cin >> price[i];
		for (int j = 0; j < n; j++) {
			cin >> table[i][j];
		}
	}

	Program qp(CGAL::SMALLER, true, 0, false, 0);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			qp.set_a(i, j, table[i][j]);
			qp.set_a(i, j + n, -table[i][j]);
		}
	}

	for (int j = 0; j < n; j++) {
		qp.set_b(j, maximum[j]);
		qp.set_b(j + n, -minimum[j]);
	}

	for (int i = 0; i < m; i++) {
		qp.set_c(i, price[i]);
	}

	Solution s = CGAL::solve_linear_program(qp, ET());
	if (!s.is_optimal()) {
		cout << "No such diet." << endl;
	} else {
		cout << floor(CGAL::to_double(s.objective_value())) << endl;
	}
}

int main(void) {
	int n, m;
	cin >> n >> m;
	while (n && m) {
		diet(n, m);
		cin >> n >> m;
	}
}
