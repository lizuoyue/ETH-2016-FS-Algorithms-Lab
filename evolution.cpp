#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

void dfs(
	int root,
	vector<int> &trace,
	vector<string> &name,
	vector<int> &age,
	vector< vector<int> > &tree,
	vector< vector<int> > &query,
	vector< vector<int> > &order,
	vector<string> &result) {

	trace.push_back(root);
	for (int i = 0; i < query[root].size(); ++i) {
		
		int l = 0, r = trace.size() - 1;
		while (l < r) {
			int mid = (l + r) / 2;
			if (age[trace[mid]] <= query[root][i]) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}
		result[order[root][i]] = name[trace[l]];
	}

	for (int i = 0; i < tree[root].size(); ++i) {
		dfs(tree[root][i], trace, name, age, tree, query, order, result);
	}
	trace.pop_back();

}

void evolution() {

	int n, q;
	cin >> n >> q;

	unordered_map<string, int> name2idx;
	vector<string> name(n);
	vector<int> age(n);
	for (int i = 0; i < n; ++i) {
		cin >> name[i] >> age[i];
		name2idx[name[i]] = i;
	}

	vector< vector<int> > tree(n);
	vector<int> father(n, -1);
	for (int i = 0; i < n - 1; ++i) {
		string u, v;
		cin >> v >> u;
		tree[name2idx[u]].push_back(name2idx[v]);
		father[name2idx[v]] = name2idx[u];
	}

	vector<string> result(q);
	vector< vector<int> > query(n);
	vector< vector<int> > order(n);
	for (int i = 0; i < q; ++i) {
		string str; int num;
		cin >> str >> num;
		query[name2idx[str]].push_back(num);
		order[name2idx[str]].push_back(i);
	}

	int root = -1;
	for (int i = 0; i < n; ++i) {
		if (father[i] == -1) {
			root = i;
		}
	}

	vector<int> trace;
	dfs(root, trace, name, age, tree, query, order, result);

	for (int i = 0; i < q; ++i) {
		cout << result[i] << " ";
	}
	cout << endl;

}

int main() {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		evolution();
	}
	return 0;
}
