#include <vector>
#include <iostream>

using namespace std;

void false_coin() {
	int n, k;
	cin >> n >> k;

	vector<int> result(k), weight(n, 0);
	vector< vector<int> > comparison(k, vector<int> (n, 0));

	char sign;
	int num, temp;
	for (int i = 0; i < k; i++) {
		cin >> num;
		for (int j = 0; j < num; j++) {
			cin >> temp;
			temp -= 1;
			comparison[i][temp] = 1;
		}
		for (int j = 0; j < num; j++) {
			cin >> temp;
			temp -= 1;
			comparison[i][temp] = -1;
		}
		cin >> sign;
		switch (sign) {
			case '<': result[i] = -1; break;
			case '=': result[i] = 0; break;
			case '>': result[i] = 1; break;
			default: result[i] = 0;
		}
	}
	
	/*
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {
			cout << comparison[i][j] << " ";
		}
		cout << "    " << result[i];
		cout << endl;
	}
	*/

	int same, oppo;
	int false_idx = 0, false_num = 0;
	for (int i = 0; i < n; i++) {
		same = 0;
		oppo = 0;
		for (int j = 0; j < k; j++) {
			same += (result[j] == comparison[j][i]);
			oppo += (result[j] == -comparison[j][i]);
		}
		//cout << same << " " << oppo << endl;
		if (same == k || oppo == k) {
			false_idx = i;
			false_num += 1;
		}
	}
	if (false_num != 1) {
		false_idx = -1;
	}
	cout << false_idx + 1 << endl;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		false_coin();
	}
}