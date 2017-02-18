#include <iostream>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void portfolios(int nAsset, int nPeople) {

	vector<int> cost(nAsset);
	vector<int> refund(nAsset);
	for (int i = 0; i < nAsset; i++) {
		cin >> cost[i] >> refund[i];
	}

	vector< vector<int> > cov(nAsset, vector<int>(nAsset));
	for (int i = 0; i < nAsset; i++) {
		for (int j = 0; j < nAsset; j++) {
			cin >> cov[i][j];
		}
	}

	vector<int> max_cost(nPeople);
	vector<int> min_refund(nPeople);
	vector<int> max_var(nPeople);
	for (int i = 0; i < nPeople; i++) {
		cin >> max_cost[i] >> min_refund[i] >> max_var[i];
	}

	Program lp(CGAL::SMALLER, true, 0, false, 0);
	for (int i = 0; i < nAsset; i++) {
		lp.set_a(i, 0, cost[i]);
		lp.set_a(i, 1, refund[i]);
		for (int j = i; j < nAsset; j++) {
			lp.set_d(j, i, cov[i][j] + cov[i][j]);
		}
	}

	for (int i = 0; i < nPeople; i++) {
		lp.set_b(0, max_cost[i]);
		lp.set_b(1, min_refund[i]);
		lp.set_r(1, CGAL::LARGER);

		Solution s = CGAL::solve_quadratic_program(lp, ET());
		if (s.is_optimal()) {
			double currentV = CGAL::to_double(s.objective_value());
			//cout << currentV << " " << max_var[i] << endl;
			if (currentV > max_var[i]) {
				cout << "No." << endl;
			} else {
				cout << "Yes." << endl;
			}
		} else {
			cout << "No." << endl;
		}
	}
}

int main(void) {
	int nAsset, nPeople;
	cin >> nAsset >> nPeople;
	while (nAsset && nPeople) {
		portfolios(nAsset, nPeople);
		cin >> nAsset >> nPeople;
	}
}
