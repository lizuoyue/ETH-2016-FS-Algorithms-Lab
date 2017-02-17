#include <vector>
#include <iostream>

using namespace std;

void even_matrices() {

	int n;
	cin >> n;

	vector< vector<int> > x(n, vector<int> (n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> x[i][j];
			//cout << x[i][j] << " ";
		}
		//cout << endl;
	}

	vector< vector<int> > s_col(n, vector<int> (n, 0));
	for (int j = 0; j < n; j++) {
		s_col[0][j] = x[0][j];
		for (int i = 1; i < n; i++) {
			s_col[i][j] = s_col[i - 1][j] + x[i][j];
		}
	}

	/*
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++) {
			cout << s_col[i][j] << " ";
		}
		cout << endl;
	}
	*/

	vector< vector< vector<int> > > evens(n, vector< vector<int> > (n, vector<int> (n, 0)));
	vector< vector< vector<int> > > odds(n, vector< vector<int> > (n, vector<int> (n, 0)));
	for (int i = 0; i < n; i++) {
		for (int h = 0; h < i; h++) {
			int temp_sum = s_col[i][0] - s_col[i - h - 1][0];
			evens[i][0][h] = (temp_sum % 2 == 0);
			odds[i][0][h] = (temp_sum % 2 == 1);
			//cout << evens[i][0][h] << " " << odds[i][0][h] << endl;
		}
		evens[i][0][i] = (s_col[i][0] % 2 == 0);
		odds[i][0][i] = (s_col[i][0] % 2 == 1);
		//cout << evens[i][0][i] << " " << odds[i][0][i] << endl;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n; j++) {
			for (int h = 0; h < i; h++) {
				int temp_sum = s_col[i][j] - s_col[i - h - 1][j];
				if (temp_sum % 2 == 0) {
					evens[i][j][h] = evens[i][j - 1][h] + 1;
					odds[i][j][h] = odds[i][j - 1][h];
				} else {
					evens[i][j][h] = odds[i][j - 1][h];
					odds[i][j][h] = evens[i][j - 1][h] + 1;
				}
			}
			if (s_col[i][j] % 2 == 0) {
				evens[i][j][i] = evens[i][j - 1][i] + 1;
				odds[i][j][i] = odds[i][j - 1][i];
			} else {
				evens[i][j][i] = odds[i][j - 1][i];
				odds[i][j][i] = evens[i][j - 1][i] + 1;
			}
		}
	}

	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int h = 0; h <= i; h++) {
				count += evens[i][j][h];
			}
		}
	}
	cout << count << endl;

}

int main(void) {

	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		even_matrices();
	}

}