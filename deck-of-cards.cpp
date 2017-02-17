#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void deck_of_cards() {
	int n, k;
	cin >> n >> k;
	
	vector<int> v(n + 1, 0), s(n + 1, 0);

	for (int i = 1; i <= n; i++) {
		cin >> v[i];
		s[i] = s[i - 1] + v[i];
	}

	int i = 0, j = 1;
	int lp = 0, rp = 1;
	int min = fabs(s[j] - s[i] - k);

	while (i < n && j <= n && i < j) {
		int temp = fabs(s[j] - s[i] - k);
		if (temp < min) {
			min = temp;
			lp = i;
			rp = j;
		}
		if (s[j] - s[i] < k) {
			j++;
		} else {
			i++;
			if (i == j) {
				j++;
			}
		}
	}
	cout << lp << " " << rp - 1 << endl;
}


int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		deck_of_cards();
	}
	return 0;
}