#include <iostream>
#include <climits>
#include <vector>
#include <cmath>

using namespace std;

void punch() {

	int n, k;
	cin >> n >> k;

	vector<int> c(n), v(n);
	for (int i = 0; i < n; i++) {
		cin >> c[i] >> v[i];
	}

	vector< vector<int> > f(n, vector<int>(k + 1, INT_MAX));
	vector< vector<int> > g(n, vector<int>(k + 1, 0));

	for (int i = 0; i < n; ++i) {
		f[i][0] = 0;
	}

	for (int j = 1; j <= k; ++j) {
		int idx = max(0, j - v[0]);
		f[0][j] = f[0][idx] + c[0];
		g[0][j] = 1;
	}

	for (int i = 1; i < n; ++i) {
		vector<bool> choose(k + 1, false);
		for (int j = 1; j <= k; ++j) {
			int idx = max(0, j - v[i]);
			if (f[i - 1][j] < f[i][idx] + c[i]) {
				f[i][j] = f[i - 1][j];
				g[i][j] = g[i - 1][j];
			} else if (f[i - 1][j] > f[i][idx] + c[i]) {
				f[i][j] = f[i][idx] + c[i];
				g[i][j] = g[i][idx] + !choose[idx];
				choose[j] = true;
			} else {
				f[i][j] = f[i - 1][j];
				if (g[i - 1][j] >= g[i][idx] + !choose[idx]) {
					g[i][j] = g[i - 1][j];
				} else {
					g[i][j] = g[i][idx] + !choose[idx];
					choose[j] = true;
				}
			}
		}
	}

	cout << f[n - 1][k] << " " << g[n - 1][k] << endl;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		punch();
	}
	return 0;
}
