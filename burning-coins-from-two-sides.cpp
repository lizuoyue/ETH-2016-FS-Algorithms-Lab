#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void burning_coins() {
	int n;
	cin >> n;
	vector<int> v(n);
	vector<int> s(n + 1, 0);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		s[i + 1] = s[i] + v[i];
	}

	vector< vector<int> > result_store(n + 1, vector<int>(n + 1));

	for (int len = 1; len <= n; len++) {
		for (int i = 0; i <= n - len; i++) {
			int j = i + len;
			if (len == 1) {
				result_store[i][j] = v[i];
			} else if (len == 2) {
				result_store[i][j] = max(v[i], v[j - 1]);
			} else {
				int rest1 = v[i] + s[j] - s[i + 1] - result_store[i + 1][j];
				int rest2 = v[j - 1] + s[j - 1] - s[i] - result_store[i][j - 1];
				result_store[i][j] = max(rest1, rest2);
			}
		}
	}

	cout << result_store[0][n] << endl;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		burning_coins();
	}
	return 0;
}