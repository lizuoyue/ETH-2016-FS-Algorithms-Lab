#include <iostream>
#include <vector>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
typedef	property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor Vertex;
typedef	graph_traits<Graph>::edge_descriptor Edge;

class EdgeAdder {

	Graph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:

	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap) {}

	void addEdge(int from, int to, long capacity) {
		Edge e, reverseE;
		bool success;
		tie(e, success) = add_edge(from, to, G);
		tie(reverseE, success) = add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[reverseE] = 0;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
	}

};

int find(int x, vector<int> &root) {

	if (root[x] == x) {
		return x;
	} else {
		root[x] = find(root[x], root);
		return root[x];
	}

}

void merge(int x, int y, vector<int> &root) {

	int u = find(x, root);
	int v = find(y, root);
	if (u != v) {
		root[v] = u;
	}

}

void sweepers() {

	int n, m, s;
	cin >> n >> m >> s;

	Graph G(n + 2);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	const int source = n;
	const int target = n + 1;

	vector<int> root(n);
	vector<int> degree(n, 0);
	for (int i = 0; i < n; ++i) {
		root[i] = i;
	}

	vector<int> src(s), tgt(s);
	for (int i = 0; i < s; ++i) {
		cin >> src[i];
		degree[src[i]] += 1;
		eaG.addEdge(source, src[i], 1);
	}
	for (int i = 0; i < s; ++i) {
		cin >> tgt[i];
		degree[tgt[i]] += 1;
		eaG.addEdge(tgt[i], target, 1);
	}

	for (int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		merge(x, y, root);
		degree[x] += 1;
		degree[y] += 1;
		eaG.addEdge(x, y, 1);
		eaG.addEdge(y, x, 1);
	}

	long flow = push_relabel_max_flow(G, source, target);
	if (flow != s) {
		cout << "no" << endl;
		return;
	}

	map<int, int> nPoint, nSource;
	for (int i = 0; i < n; ++i) {
		nPoint[find(i, root)] += 1;
	}
	for (int i = 0; i < s; ++i) {
		nSource[find(src[i], root)] += 1;
	}

	for (map<int, int>::iterator iter = nPoint.begin(); iter != nPoint.end(); ++iter) {
		if (iter->second > 1 && nSource[iter->first] == 0) {
			cout << "no" << endl;
			return;
		}
	}

	for (int i = 0; i < n; ++i) {
		if (degree[i] % 2 != 0) {
			cout << "no" << endl;
			return;
		}
	}

	cout << "yes" << endl;

}

int main(void) {
	int T;
	cin >> T;
	for(int t = 0; t < T; ++t) {
		sweepers();
	}
}
