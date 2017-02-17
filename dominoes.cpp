#include <vector>
#include <iostream>

using namespace std;

void dominoes() {
	int n;
	cin >> n;

	vector<int> h(n), hp(n);

	for (int i = 0; i < n; i++) {
		cin >> h[i];
		hp[i] = h[i] + i;
	}
	
	int count = 0, current = hp[0];
	for (int i = 0; i < n; i++) {
		if (i < current) {
			count += 1;
			if (hp[i] > current) {
				current = hp[i];
			}
		}
	}
	cout << count << endl;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		dominoes();
	}
}