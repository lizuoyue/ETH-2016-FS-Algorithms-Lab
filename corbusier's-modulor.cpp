#include <iostream>
#include <vector>

using namespace std;

void corbusier() {

	int n, a, b;
	cin >> n >> a >> b;

	vector<int> len(n);
	for (int i = 0; i < n; ++i) {
		cin >> len[i];
	}

	vector< vector<bool> > dp(n, vector<bool>(b, false));
	dp[0][len[0] % b] = true;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < b; ++j) {
			int val = j - (len[i] % b);
			val += (val < 0) * b;
			dp[i][j] = dp[i - 1][j] || dp[i - 1][val];
		}
	}
	if (dp[n - 1][a]) {
		cout << "yes" << endl;
	} else {
		cout << "no" << endl;
	}
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		corbusier();
	}
	return 0;
}