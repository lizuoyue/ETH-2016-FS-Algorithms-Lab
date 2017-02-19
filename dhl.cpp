#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void dhl() {

	int n;
	cin >> n;

	vector<int> a(n + 1, 0), b(n + 1, 0);
	vector<int> sa(n + 1, 0), sb(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[i] -= 1;
		sa[i] = a[i] + sa[i - 1];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> b[i];
		b[i] -= 1;
		sb[i] = b[i] + sb[i - 1];
	}

	vector< vector<int> > dp(n + 1, vector<int>(n + 1, 0));
	dp[1][1] = a[1] * b[1];
	for (int i = 2; i <= n; ++i) {
		dp[i][1] = (sa[i] - sa[0]) * b[1];
	}
	for (int j = 2; j <= n; ++j) {
		dp[1][j] = a[1] * (sb[j] - sb[0]);
	}
	for (int i = 2; i <= n; ++i) {
		for (int j = 2; j <= n; ++j) {
			dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + a[i] * b[j];
		}
	}
	cout << dp[n][n] << endl;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		dhl();
	}
	return 0;
}