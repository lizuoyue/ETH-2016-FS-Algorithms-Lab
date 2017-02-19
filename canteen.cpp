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

void canteen() {

	int nDay;
	cin >> nDay;

	Graph G(nDay + 2);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	EdgeWeightMap weightmap = get(edge_weight, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

	const int source = nDay;
	const int target = nDay + 1;
	const int delta = 30;

	for (int i = 0; i < nDay; i++) {
		int a, c;
		cin >> a >> c;
		eaG.addEdge(source, i, a, c);
	}

	int nStudent = 0;
	for (int i = 0; i < nDay; i++) {
		int s, p;
		cin >> s >> p;
		eaG.addEdge(i, target, s, delta - p);
		nStudent += s;
	}

	for (int i = 0; i < nDay - 1; i++) {
		int v, e;
		cin >> v >> e;
		eaG.addEdge(i, i + 1, v, e);
	}

	int flow, cost;

	successive_shortest_path_nonnegative_weights(G, source, target);
	cost = find_flow_cost(G);
	flow = 0;

	OutEdgeIt eBeg, eEnd;
	for(tie(eBeg, eEnd) = out_edges(vertex(source, G), G); eBeg != eEnd; ++eBeg) {
		flow += capacitymap[*eBeg] - rescapacitymap[*eBeg];
	}

	if (flow < nStudent) {
		cout << "impossible ";
	} else {
		cout << "possible ";
	}
	cout << flow << " " << delta * flow - cost << endl;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		canteen();
	}
	return 0;
}
