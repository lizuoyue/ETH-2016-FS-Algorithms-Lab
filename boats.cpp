#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> len;
vector<int> pos;
vector<int> order;

bool compare(int i, int j) {
	return (pos[i] < pos[j]);
}

void boats() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		len.push_back(a);
		pos.push_back(b);
		order.push_back(i);
	}
	sort(order.begin(), order.end(), compare);

	int i = 0;
	int j = order[0];
	vector<int> bias(n, -1);
	bias[j] = 0;
	int up_border = pos[j];

	i++;
	while(i < n) {
		j = order[i];
		if ((pos[j] - len[j]) < up_border) {

			int new_border = up_border + len[j];
			int min_i = i, min_j = order[min_i];

			int local_i = i + 1;
			while(local_i < n) {
				int local_j = order[local_i];
				if (pos[local_j] >= new_border) {
					break;
				} else {
					int temp;
					if ((pos[local_j] - len[local_j]) < up_border) {
						temp = up_border + len[local_j];
					} else {
						temp = pos[local_j];
					}
					if (temp < new_border) {
						new_border = temp;
						min_i = local_i;
						min_j = order[min_i];
					}
					local_i++;
				}
			}
			bias[min_j] = new_border - pos[min_j];
			up_border = new_border;
			i = local_i;
		} else {
			bias[j] = 0;
			up_border = pos[j];
			i++;
		}
	}

	int count = 0;
	for (int k = 0; k < n; k++) {
		if (bias[k] >= 0) {
			count++;
		}
		//cout << bias[order[k]] << endl;
	}
	cout << count << endl;
	len.resize(0);
	pos.resize(0);
	order.resize(0);
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		boats();
	}
}