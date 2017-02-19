#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int idx(int a, int b, int c, int d, int n) {
	return n * n * (a * n + b) + (c * n + d);
}

int f(int a, int b, int c, int d, int n, vector< vector<int> > &v, vector<int> &result) {

	int temp;
	temp = result[idx(a, b, c, d, n)];
	if (temp != -1) {
		return temp;
	}
	temp = result[idx(c, d, a, b, n)];
	if (temp != -1) {
		return temp;
	}

	if (a == (n - 1) && b == (n - 1) && c == (n - 1) && d == (n - 1)) {
		result[idx(a, b, c, d, n)] = v[n - 1][n - 1];
		return v[n - 1][n - 1];
	}

	if (a == c && b == d) {

		int score = 0;
		if (a < n - 1) {
			score = max(score, f(a + 1, b, c + 1, d, n, v, result));
		}
		if (b < n - 1) {
			score = max(score, f(a, b + 1, c, d + 1, n, v, result));
		}
		if ((a < n - 1) && (b < n - 1)) {
			score = max(score, f(a, b + 1, c + 1, d, n, v, result));
		}
		score += v[a][b];
		result[idx(a, b, c, d, n)] = score;
		return score;

	} else if (a == c && b == (d - 1)) {

		int score = 0;
		if (a < n - 1) {
			score = max(score, f(a + 1, b, c + 1, d, n, v, result) + v[c][d]);
			score = max(score, f(a, b + 1, c + 1, d, n, v, result));
		}
		if (d < n - 1) {
			score = max(score, f(a, b + 1, c, d + 1, n, v, result));
		}
		if (a < n - 1 && d < n - 1) {
			score = max(score, f(c, d + 1, a + 1, b, n, v, result) + v[c][d]);
		}
		score += v[a][b];
		result[idx(a, b, c, d, n)] = score;
		result[idx(c, d, a, b, n)] = score;
		return score;

	} else if (a == (c - 1) && b == d) {

		int score = 0;
		if (c < n - 1) {
			score = max(score, f(a + 1, b, c + 1, d, n, v, result));
		}
		if (d < n - 1) {
			score = max(score, f(a, b + 1, c, d + 1, n, v, result) + v[c][d]);
			score = max(score, f(a + 1, b, c, d + 1, n, v, result));
		}
		if (c < n - 1 && d < n - 1) {
			score = max(score, f(a, b + 1, c + 1, d, n, v, result) + v[c][d]);
		}
		score += v[a][b];
		result[idx(a, b, c, d, n)] = score;
		result[idx(c, d, a, b, n)] = score;
		return score;

	} else {

		int score = 0;
		if (a < n - 1 && c < n - 1) {
			score = max(score, f(a + 1, b, c + 1, d, n, v, result));
		}
		if (a < n - 1 && d < n - 1) {
			score = max(score, f(a + 1, b, c, d + 1, n, v, result));
		}
		if (b < n - 1 && c < n - 1) {
			score = max(score, f(a, b + 1, c + 1, d, n, v, result));
		}
		if (b < n - 1 && d < n - 1) {
			score = max(score, f(a, b + 1, c, d + 1, n, v, result));
		}
		score += (v[a][b] + v[c][d]);
		result[idx(a, b, c, d, n)] = score;
		result[idx(c, d, a, b, n)] = score;
		return score;
	}
}

void bonus() {
	int n;
	cin >> n;

	vector< vector<int> > v(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> v[i][j];
		}
	}

	vector<int> result(n * n * n * n, -1);
	cout << f(0, 0, 0, 0, n, v, result) << endl;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		bonus();
	}
	return 0;
}
