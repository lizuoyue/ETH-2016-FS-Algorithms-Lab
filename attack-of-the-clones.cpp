#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct jedi {
	int start;
	int end;
	int len;
	bool flag;
	bool operator< (const jedi &jedi_inst) const {
		return end < jedi_inst.end;
	}
};

void attack() {
	int n, m;
	cin >> n >> m;

	vector<jedi> jedis(n);
	for (int i = 0; i < n; i++) {
		cin >> jedis[i].start >> jedis[i].end;
		jedis[i].flag = (jedis[i].start > jedis[i].end);
		jedis[i].len = jedis[i].end + jedis[i].flag * m - jedis[i].start + 1;
	}

	sort(jedis.begin(), jedis.end());

	/*
	for (int i = 0; i < n; i++) {
		cout << jedis[i].start << " " << jedis[i].end << endl;
	}
	*/
	
	int max_num = 0;
	int start_idx;
	for (start_idx = 0; start_idx < n; start_idx++) {

		if (jedis[start_idx].flag == true) {

			int num = 1;
			int boundary = jedis[start_idx].end;
			int final = jedis[start_idx].start;

			for (int i = start_idx + 1; i < n; i++) {
				if (jedis[i].flag == false && jedis[i].start > boundary && jedis[i].end < final) {
					num++;
					boundary = jedis[i].end;
				}
			}

			if (num > max_num) {
				max_num = num;
			}

		} else {

			int num = 1;
			int boundary = jedis[start_idx].end;

			for (int i = start_idx + 1; i < n; i++) {
				if (jedis[i].flag == false && jedis[i].start > boundary) {
					num++;
					boundary = jedis[i].end;
				}
			}

			if (num > max_num) {
				max_num = num;
			}

			break;

		}

	}

	cout << max_num << endl;

}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		attack();
	}
	return 0;
}