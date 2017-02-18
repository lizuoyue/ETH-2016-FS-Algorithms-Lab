#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

vector<int> stateNum(1 << 14), parent;
map<pair<int, int>, vector<int> > mutual;
vector< vector<int> > child, center, centerState, A, B;

int fa(int root, int state);
int fb(int root, int state);

int fa(int root, int state) {

	if (A[root][state] != -1) {
		return A[root][state];
	}

	int num = stateNum[state];
	for (int i = 0; i < child[root].size(); ++i) {
		pair<int, int> e = make_pair(root, child[root][i]);
		if (mutual[e].size() == 2) {
			bool next = (state & (1 << mutual[e][0])) > 0;
			num += fb(child[root][i], next);
		}
		if (mutual[e].size() == 4) {
			bool flag1 = (state & (1 << mutual[e][0])) > 0;
			bool flag2 = (state & (1 << mutual[e][2])) > 0;
			int next = flag2 * 2 + flag1;
			num += fb(child[root][i], next);
		}
	}
	A[root][state] = num;
	return num;

}

int fb(int root, int state) {

	if (B[root][state] != -1) {
		return B[root][state];
	}

	int num = -1;
	pair<int, int> e = make_pair(parent[root], root);
	for (int i = 0; i < centerState[root].size(); ++i) {
		int s = centerState[root][i];
		if (mutual[e].size() == 2) {
			if (state == 0) {
				num = max(num, fa(root, s));
			}
			if (state == 1) {
				if ((mutual[e][1] & s) == 0) {
					num = max(num, fa(root, s));
				}
			}
		}
		if (mutual[e].size() == 4) {
			if (state == 0) {
				num = max(num, fa(root, s));
			}
			if (state == 1) {
				if ((mutual[e][1] & s) == 0) {
					num = max(num, fa(root, s));
				}
			}
			if (state == 2) {
				if ((mutual[e][3] & s) == 0) {
					num = max(num, fa(root, s));
				}
			}
			if (state == 3) {
				if (((mutual[e][1] & s) == 0) && ((mutual[e][3] & s) == 0)) {
					num = max(num, fa(root, s));
				}
			}		
		}
	}
	B[root][state] = num;
	return num;

}

void hope() {

	int nC, nS, m, nState;
	cin >> nC >> nS >> m;
	nState = (1 << nS);

	parent.clear(); parent.resize(nC, -1);
	child.clear(); child.resize(nC);
	center.clear(); center.resize(nC);
	centerState.clear(); centerState.resize(nC);
	mutual.clear();
	A.clear(); A.resize(nC, vector<int>(nState, -1));
	B.clear(); B.resize(nC, vector<int>(4, -1));

	for (int i = 0; i < m; ++i) {
		int u, v, h;
		cin >> u >> v >> h;
		if (u == v) {
			h *= 2;
			center[u].resize(h);
			for (int j = 0; j < h; ++j) {
				cin >> center[u][j];
			}
		} else {
			parent[v] = u;
			child[u].push_back(v);
			pair<int, int> e = make_pair(u, v);
			map<int, int> tempMap;
			for (int j = 0; j < h; ++j) {
				int x, y;
				cin >> x >> y;
				tempMap[x] = tempMap[x] | (1 << y);
			}
			if (tempMap.size() == 1) {
				mutual[e].push_back(tempMap.begin()->first);
				mutual[e].push_back(tempMap.begin()->second);
			}
			if (tempMap.size() == 2) {
				mutual[e].push_back(tempMap.begin()->first);
				mutual[e].push_back(tempMap.begin()->second);
				mutual[e].push_back((++tempMap.begin())->first);
				mutual[e].push_back((++tempMap.begin())->second);
			}
		}
	}

	for (int i = 0; i < nC; ++i) {
		for (int s = 0; s < nState; ++s) {
			bool flag = true;
			for (int k = 0; k < center[i].size(); k += 2) {
				bool flag1 = (s & (1 << center[i][k])) > 0;
				bool flag2 = (s & (1 << center[i][k + 1])) > 0;
				if (flag1 && flag2) {
					flag = false;
					break;
				}
			}
			if (flag) {
				centerState[i].push_back(s);
			}
		}

		if (child[i].size() == 0) {
			pair<int, int> e = make_pair(parent[i], i);
			if (mutual[e].size() == 2) {
				for (int j = 0; j < centerState[i].size(); ++j) {
					int s = centerState[i][j];
					A[i][s] = stateNum[s];
					B[i][0] = max(B[i][0], stateNum[s]);
					if ((mutual[e][1] & s) == 0) {
						B[i][1] = max(B[i][1], stateNum[s]);
					}
				}
			}
			if (mutual[e].size() == 4) {
				for (int j = 0; j < centerState[i].size(); ++j) {
					int s = centerState[i][j];
					A[i][s] = stateNum[s];
					B[i][0] = max(B[i][0], A[i][s]);
					bool flag1 = (mutual[e][1] & s) == 0;
					bool flag2 = (mutual[e][3] & s) == 0;
					if (flag1) {
						B[i][1] = max(B[i][1], A[i][s]);
					}
					if (flag2) {
						B[i][2] = max(B[i][2], A[i][s]);
					}
					if (flag1 && flag2) {
						B[i][3] = max(B[i][3], A[i][s]);
					}
				}
			}
		}
	}

	int maxNum = 0;
	for (int i = 0; i < centerState[0].size(); ++i) {
		int s = centerState[0][i];
		maxNum = max(maxNum, fa(0, s));
	}
	cout << maxNum << endl;

}

int main() {

	ios_base::sync_with_stdio(false);

	for (int s = 0; s < (1 << 14); ++s) {
		int num = 0;
		for (int i = 0; i < 14; ++i) {
			num += ((s & (1 << i)) > 0);
		}
		stateNum[s] = num;
	}

	int T; cin >> T;
	for (int i = 0; i < T; ++i) {
		hope();
	}
	return 0;

}