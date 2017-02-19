#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

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

void algocoon() {

	int nV, nE;
	cin >> nV >> nE;

	Graph G(nV);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	for (int i = 0; i < nE; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		eaG.addEdge(u, v, c);
	}

	int maxFlow = (1 << 30);
	int source, sink;
	for (int i = 1; i < nV; i++) {
		int flow;
		flow = push_relabel_max_flow(G, 0, i);
		if (flow < maxFlow) {
			maxFlow = flow;
			source = 0;
			sink = i;
		}
		flow = push_relabel_max_flow(G, i, 0);
		if (flow < maxFlow) {
			maxFlow = flow;
			source = i;
			sink = 0;
		}
	}
	cout << maxFlow << endl;

	maxFlow = push_relabel_max_flow(G, source, sink);

	vector<int> visited(nV, 0);
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

	vector<int> result;
	for (int i = 0; i < nV; i++) {
		if (visited[i] == 1) {
			result.push_back(i);
		}
	}
	cout << result.size() << " ";
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}
	cout << endl;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		algocoon();
	}
	return 0;
}
