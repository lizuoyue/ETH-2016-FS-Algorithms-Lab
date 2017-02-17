#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

struct bomb {
	int index;
	int time;
	int constrain;
	bool operator< (const bomb &bomb_inst) const {
		return (time > bomb_inst.time) || ((time == bomb_inst.time) && (index > bomb_inst.index));
	}
};

void octopussy() {

	int n;
	cin >> n;
	int nLayer = log2(n + 1);
	int nGround = (n - 1) / 2;

	vector<bomb> bombList(n);
	for (int i = 0; i < n; ++i) {
		bombList[i].index = i;
		cin >> bombList[i].time;
		if (i < nGround) {
			bombList[i].constrain = 2;
		} else {
			bombList[i].constrain = 0;
		}
	}

	vector<bomb> waitBomb;
	for (int i = 1; i < n; ++i) {
		if (bombList[i].time >= bombList[(i - 1) / 2].time) {
			bombList[i].time = bombList[(i - 1) / 2].time - 1;
		}
		if (i >= nGround) {
			waitBomb.push_back(bombList[i]);
		}
	}
	make_heap(waitBomb.begin(), waitBomb.end());

	for (int i = 0; i < n; ++i) {
		int time = i + 1;
		pop_heap(waitBomb.begin(), waitBomb.end());
		bomb chooseBomb = waitBomb.back();
		waitBomb.pop_back();

		if (chooseBomb.time < time) {
			cout << "no" << endl;
			return;
		}

		if (chooseBomb.index == 0) {
			break;
		}

		int fatherIdx = (chooseBomb.index - 1) / 2;
		bombList[fatherIdx].constrain -= 1;
		if (bombList[fatherIdx].constrain == 0) {
			waitBomb.push_back(bombList[fatherIdx]);
			push_heap(waitBomb.begin(), waitBomb.end());
		}
	}

	cout << "yes" << endl;

}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		octopussy();
	}
	return 0;
}