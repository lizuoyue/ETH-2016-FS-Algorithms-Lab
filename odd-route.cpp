#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

vector< vector<int> > outEdge;
vector< vector<int> > weight;
vector<int> onow;
vector<int> onew;
vector<int> enew;
vector<int> enow;
queue<int> q_onow;
queue<int> q_onew;
queue<int> q_enew;
queue<int> q_enow;

void route() {

	int nV, nE, source, target;
	cin >> nV >> nE >> source >> target;

	outEdge.clear(); outEdge.resize(nV);
	weight.clear(); weight.resize(nV);
	for (int i = 0; i < nE; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		outEdge[u].push_back(v);
		weight[u].push_back(w);
	}

	onow.clear(); onow.resize(nV, INT_MAX); q_onow = queue<int>();
	onew.clear(); onew.resize(nV, INT_MAX); q_onew = queue<int>();
	enew.clear(); enew.resize(nV, INT_MAX); q_enew = queue<int>();
	enow.clear(); enow.resize(nV, INT_MAX); q_enow = queue<int>();

	enew[source] = 0;
	q_enew.push(source);
	while (!q_onow.empty() || !q_onew.empty() || !q_enew.empty() || !q_enow.empty()) {

		if(!q_onow.empty()) {
			int root = q_onow.front(); q_onow.pop();
			for (int i = 0; i < outEdge[root].size(); i++) {
				int child = outEdge[root][i];
				int val = onow[root] + weight[root][i];
				if (weight[root][i] % 2 == 0) {
					if (enow[child] > val) {
						enow[child] = val;
						q_enow.push(child);
					}
				} else {
					if (enew[child] > val) {
						enew[child] = val;
						q_enew.push(child);
					}
				}
			}
		}

		if(!q_onew.empty()) {
			int root = q_onew.front(); q_onew.pop();
			for (int i = 0; i < outEdge[root].size(); i++) {
				int child = outEdge[root][i];
				int val = onew[root] + weight[root][i];
				if (weight[root][i] % 2 == 0) {
					if (enew[child] > val) {
						enew[child] = val;
						q_enew.push(child);
					}
				} else {
					if (enow[child] > val) {
						enow[child] = val;
						q_enow.push(child);
					}
				}
			}
		}

		if(!q_enew.empty()) {
			int root = q_enew.front(); q_enew.pop();
			for (int i = 0; i < outEdge[root].size(); i++) {
				int child = outEdge[root][i];
				int val = enew[root] + weight[root][i];
				if (weight[root][i] % 2 == 0) {
					if (onew[child] > val) {
						onew[child] = val;
						q_onew.push(child);
					}
				} else {
					if (onow[child] > val) {
						onow[child] = val;
						q_onow.push(child);
					}
				}
			}
		}

		if(!q_enow.empty()) {
			int root = q_enow.front(); q_enow.pop();
			for (int i = 0; i < outEdge[root].size(); i++) {
				int child = outEdge[root][i];
				int val = enow[root] + weight[root][i];
				if (weight[root][i] % 2 == 0) {
					if (onow[child] > val) {
						onow[child] = val;
						q_onow.push(child);
					}
				} else {
					if (onew[child] > val) {
						onew[child] = val;
						q_onew.push(child);
					}
				}
			}
		}
	}

	if (onow[target] == INT_MAX) {
		cout << "no" << endl;
	} else {
		cout << onow[target] << endl;
	}
	/*
	for (int i = 0; i < nV; i++) {
		cout << onow[i] << " " << onew[i] << " " << enew[i] << " " << enow[i] << endl;
	}
	cout << "===" << endl;*/
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		route();
	}
	return 0;
}
