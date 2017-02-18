#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void light_pattern() {

	int n, k, x;
	cin >> n >> k >> x;

	int xx = x;
	vector<int> pattern(k);
	for (int i = 0; i < k; i++) {
		pattern[k - i - 1] = xx % 2;
		xx /= 2;
	}

	int s = n / k;
	vector<int> light(n);
	vector<int> simi(s);
	vector<int> dist(s);
	
	for (int i = 0; i < n / k; i++) {
		int sum = 0;
		for (int j = 0; j < k; j++) {
			cin >> light[i * k + j];
			sum += (light[i * k + j] != pattern[j]);
		}
		dist[i] = sum;
		simi[i] = k - sum;
	}

	vector<int> min_time_pos(s);
	vector<int> min_time_neg(s);
	min_time_pos[0] = min(dist[0], simi[0] + 1);
	min_time_neg[0] = min(dist[0] + 1, simi[0]);
	for (int i = 1; i < s; i++) {
		min_time_pos[i] = min(dist[i] + min_time_pos[i - 1], simi[i] + 1 + min_time_neg[i - 1]);
		min_time_neg[i] = min(simi[i] + min_time_neg[i - 1], dist[i] + 1 + min_time_pos[i - 1]);
	}

	cout << min_time_pos[s - 1] << endl;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		light_pattern();
	}
	return 0;
}