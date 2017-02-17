#include <vector>
#include <iostream>

using namespace std;

void even_pairs() {
	int n, count;
	cin >> n;
	vector<int> x(n), sum(n), evens(n), odds(n);

	for (int i = 0; i < n; i++) {
		cin >> x[i];
		//cout << x[i] << " ";
	}
	//cout << endl;

	sum[0] = x[0];
	//cout << sum[0] << " ";
	for (int i = 1; i < n; i++) {
		sum[i] = sum[i - 1] + x[i];
		//cout << sum[i] << " ";
	}
	//cout << endl;

	evens[0] = 1;
	odds[0] = 0;
	for (int i = 1; i < n; i++) {
		evens[i] = evens[i - 1] + (sum[i - 1] % 2 == 0);
		odds[i] = odds[i - 1] + (sum[i - 1] % 2 == 1);
	}
	/*
	for (int i = 0; i < n; i++) {
		cout << evens[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << odds[i] << " ";
	}
	cout << endl;
	*/

	count = 0;
	for (int i = 0; i < n; i++) {
		if (sum[i] % 2 == 0) {
			count += evens[i];
		} else {
			count += odds[i];
		}
	}
	cout << count << endl;
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		even_pairs();
	}
}