#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void newtiles() {

	int h, w;
	cin >> h >> w;

	vector<int> bitNum(h);
	vector< vector<int> > bitMap(h, vector<int>(w));
	for (int i = 0; i < h; ++i) {
		int num = 0;
		for (int j = 0; j < w; ++j) {
			cin >> bitMap[i][j];
			num += bitMap[i][j] * (1 << (j));
		}
		bitNum[i] = num;
	}

	int nS = (1 << w);
	vector<int> twoOnes(nS, 0);
	vector< vector<int> > lastState(nS);
	for (int i = 0; i < nS; ++i) {
		for (int j = 1; j < w; ++j) {
			if ((i & (1 << j)) && (i & (1 << (j - 1)))) {
				twoOnes[i] += 1;
				j += 1;
			}
		}
		for (int j = 0; j < w; ++j) {
			if (i & (1 << j)) {
				lastState[i].push_back(i - (1 << j));
			}
		}
	}

	vector< vector<int> > numSquare(h, vector<int>(nS, 0));
	for (int i = 1; i < h; ++i) {
		for (int j = 0; j < nS; j++) {
			numSquare[i][j] = twoOnes[(bitNum[i] & bitNum[i - 1] & j)];
		}
	}

	vector< vector<int> > dp(h, vector<int>(nS, 0));
	for (int i = 1; i < h; ++i) {
		dp[i][0] = dp[i - 1][nS - 1];
		for (int j = 1; j < nS; ++j) {
			for (int k = 0; k < lastState[j].size(); ++k) {
				dp[i][j] = max(dp[i][j], dp[i][lastState[j][k]]);
			}
			dp[i][j] = max(dp[i][j], dp[i - 1][nS - 1 - j] + numSquare[i][j]);
		}
	}
	cout << dp[h - 1][nS - 1] << endl;

}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		newtiles();
	}
	return 0;
}