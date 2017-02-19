#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
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
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;

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

void estate() {

	int nPeople, nSite, nState;
	cin >> nPeople >> nSite >> nState;

	Graph G(nPeople + nSite + nState + 2);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	EdgeWeightMap weightmap = get(edge_weight, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

	const int source = nPeople + nSite + nState;
	const int target = nPeople + nSite + nState + 1;
	const int siteBase = nPeople;
	const int stateBase = nPeople + nSite;

	for (int i = 0; i < nState; i++) {
		int lim;
		cin >> lim;
		eaG.addEdge(i + stateBase, target, lim, 0);
	}

	for (int i = 0; i < nSite; i++) {
		int state;
		cin >> state;
		eaG.addEdge(i + siteBase, state + stateBase - 1, 1, 0);
	}

	const int delta = 200;
	for (int i = 0; i < nPeople; i++) {
		eaG.addEdge(source, i, 1, 0);
		for (int j = 0; j < nSite; j++) {
			int price;
			cin >> price;
			eaG.addEdge(i, j + siteBase, 1, delta - price);
		}
	}

	successive_shortest_path_nonnegative_weights(G, source, target);
	int cost = find_flow_cost(G);
	int flow = push_relabel_max_flow(G, source, target);

	cout << flow << " " << delta * flow - cost << endl;
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		estate();
	}
	return 0;
}
