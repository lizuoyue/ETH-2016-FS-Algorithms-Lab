#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor,
				property <edge_weight_t, long> > > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIt;

class EdgeAdder {

	Graph &G;
	EdgeCapacityMap &capacitymap;
	EdgeWeightMap &weightmap;
	ReverseEdgeMap  &revedgemap;

	public:

	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
		: G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

	void addEdge(int u, int v, long c, long w) {
		Edge e, reverseE;
		tie(e, tuples::ignore) = add_edge(u, v, G);
		tie(reverseE, tuples::ignore) = add_edge(v, u, G);
		capacitymap[e] = c;
		weightmap[e] = w;
		capacitymap[reverseE] = 0;
		weightmap[reverseE] = -w;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
	}

};

void casino() {

	int nStop, nTask, lim;
	cin >> nStop >> nTask >> lim;

	Graph G(nStop + 2);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	EdgeWeightMap weightmap = get(edge_weight, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

	const int source = nStop;
	const int target = nStop + 1;
	const int delta = 150;

	for (int i = 0; i < nTask; i++) {
		int u, v, p;
		cin >> u >> v >> p;
		eaG.addEdge(u, v, 1, delta * (v - u) - p);
	}

	for (int i = 0; i < nStop - 1; i++) {
		eaG.addEdge(i, i + 1, lim, delta);
	}

	eaG.addEdge(source, 0, lim, 0);
	eaG.addEdge(nStop - 1, target, lim, 0);

	successive_shortest_path_nonnegative_weights(G, source, target);
	int cost = find_flow_cost(G);
	cout << (nStop - 1) * lim * delta - cost << endl;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		casino();
	}
	return 0;
}
