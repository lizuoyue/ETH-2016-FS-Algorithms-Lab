#include <iostream>
#include <vector>

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
typedef	property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor Vertex;
typedef	graph_traits<Graph>::edge_descriptor Edge;

class EdgeAdder {
	Graph &G;
	EdgeCapacityMap &capacitymap;
	ReverseEdgeMap &revedgemap;

public:
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

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

void coin() {
	int nNode, nStreet, nShop;
	cin >> nNode >> nStreet >> nShop;

	Graph G(1 + nNode);
	EdgeCapacityMap edgeCap = get(edge_capacity, G);
	ReverseEdgeMap revEdge = get(edge_reverse, G);
	ResidualCapacityMap resCap = get(edge_residual_capacity, G);
	EdgeAdder edgeAdder(G, edgeCap, revEdge);

	for (int i = 0; i < nStreet; i++) {
		int node1, node2;
		cin >> node1 >> node2;

		if (node1 != 0 && node2 != 0) {
			edgeAdder.addEdge(node1, node2, 1);
			edgeAdder.addEdge(node2, node1, 1);
		} else {
			if (node1 == 0) {
				edgeAdder.addEdge(node1, node2, 1);
			}
			if (node2 == 0) {
				edgeAdder.addEdge(node2, node1, 1);
			}
		}
	}

	for (int i = 0; i < nShop; i++) {
		int node;
		cin >> node;

		edgeAdder.addEdge(node, nNode, 1);
	}

	long flow = push_relabel_max_flow(G, 0, nNode);
	if (flow == nShop) {
		cout << "yes" << endl;
	} else {
		cout << "no" << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		coin();
	}
	return 0;
}