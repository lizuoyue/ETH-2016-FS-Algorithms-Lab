#include <iostream>

using namespace std;

void buildthesum() {
	int M;
	double sum, a;
	cin >> M;
	sum = 0;
	for (int m = 0; m < M; m++) {
		cin >> a;
		sum += a;
	}
	cout << sum << endl;
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		buildthesum();
	}
}