#include <iostream>
#include <vector>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef	property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor Vertex;
typedef	graph_traits<Graph>::edge_descriptor Edge;
typedef	graph_traits<Graph>::out_edge_iterator OutEdgeIt;

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

void satellites() {

	int nG, nS, nL;
	cin >> nG >> nS >> nL;

	Graph G(nG + nS + 2);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	const int source = nG + nS;
	const int sink = nG + nS + 1;

	for (int i = 0; i < nG; i++) eaG.addEdge(source, i, 1);
	for (int i = 0; i < nS; i++) eaG.addEdge(i + nG, sink, 1);

	for (int i = 0; i < nL; i++) {
		int u, v;
		cin >> u >> v;
		eaG.addEdge(u, v + nG, 1);
	}

	int flow = push_relabel_max_flow(G, source, sink);

	vector<int> visited(nG + nS + 2, 0);
	std::queue<int> Q;
	visited[source] = 1;
	Q.push(source);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		OutEdgeIt eBegin, eEnd;
		for (tie(eBegin, eEnd) = out_edges(u, G); eBegin != eEnd; ++eBegin) {
			const int v = target(*eBegin, G);
			if (rescapacitymap[*eBegin] == 0 || visited[v]) continue;
			visited[v] = 1;
			Q.push(v);
		}
	}

	vector<int> left, right;
	for (int i = 0; i < nG; i++) {
		if (visited[i] == 0) {
			left.push_back(i);
		}
	}
	for (int i = 0; i < nS; i++) {
		if (visited[i + nG] == 1) {
			right.push_back(i);
		}
	}
	cout << left.size() << " " << right.size() << endl;
	for (int i = 0; i < left.size(); i++) {
		cout << left[i] << " ";
	}
	for (int i = 0; i < right.size(); i++) {
		cout << right[i] << " ";
	}
	if (left.size() > 0 || right.size() > 0) cout << endl;
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		satellites();
	}
	return 0;
}
