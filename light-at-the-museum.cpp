#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct mySum {
	int time;
	vector<int> sum;
	bool operator< (const mySum &mySum_inst) const {
		return (sum < mySum_inst.sum) || ((sum == mySum_inst.sum) && (time < mySum_inst.time));
	}
};

void museum() {

	int nS, nR;
	cin >> nS >> nR;

	vector<int> target(nR);
	for (int i = 0; i < nR; i++) {
		cin >> target[i];
	}

	vector< vector<int> > control(nS, vector<int>(nR));
	for (int i = 0; i < nS; i++) {
		for (int j = 0; j < nR; j++) {
			int a, b;
			cin >> a >> b;
			target[j] -= a;
			control[i][j] = b - a;
		}
	}

	int leftNum = nS / 2;
	int rightNum = nS - leftNum;
	vector<mySum> leftSum((1 << leftNum));
	vector<mySum> rightSum((1 << rightNum));

	for (int s = 0; s < (1 << leftNum); s++) {
		leftSum[s].time = 0;
		leftSum[s].sum.clear();
		leftSum[s].sum.resize(nR, 0);
		for (int i = 0; i < leftNum; i++) {
			if (s & (1 << i)) {
				leftSum[s].time++;
				for (int j = 0; j < nR; j++) {
					leftSum[s].sum[j] += control[i][j];
				}
			}
		}
	}

	for (int s = 0; s < (1 << rightNum); s++) {
		rightSum[s].time = 0;
		rightSum[s].sum.clear();
		rightSum[s].sum.resize(nR, 0);
		for (int i = 0; i < rightNum; i++) {
			if (s & (1 << i)) {
				rightSum[s].time++;
				for (int j = 0; j < nR; j++) {
					rightSum[s].sum[j] += control[i + leftNum][j];
				}
			}
		}
	}

	sort(leftSum.begin(), leftSum.end());
	sort(rightSum.begin(), rightSum.end());

	int i = 0, j = (1 << rightNum) - 1, minTime = nS + 1;
	vector<int> result;
	while (i < (1 << leftNum) && j >= 0) {
		vector<int> tempSum(nR, 0);
		for (int k = 0; k < nR; k++) {
			tempSum[k] = leftSum[i].sum[k] + rightSum[j].sum[k];
		}
		if (tempSum < target) {
			i++;
		} else if (tempSum > target) {
			j--;
		} else {
			minTime = min(minTime, leftSum[i].time + rightSum[j].time);
			j--;
		}
	}

	if (minTime > nS) {
		cout << "impossible" << endl;
	} else {
		cout << minTime << endl;
	}
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		museum();
	}
	return 0;
}
