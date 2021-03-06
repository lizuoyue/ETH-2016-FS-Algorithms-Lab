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

void kingdom() {
	int nNode, nPath;
	cin >> nNode >> nPath;

	Graph G(nNode + 2);
	EdgeCapacityMap edgeCap = get(edge_capacity, G);
	ReverseEdgeMap revEdge = get(edge_reverse, G);
	ResidualCapacityMap resCap = get(edge_residual_capacity, G);
	EdgeAdder edgeAdder(G, edgeCap, revEdge);

	int source = nNode;
	int target = nNode + 1;

	vector<int> capReal(nNode);
	vector<int> capNeed(nNode);
	for (int i = 0; i < nNode; i++) {
		cin >> capReal[i] >> capNeed[i];
	}

	for (int i = 0; i < nPath; i++) {
		int node1, node2, minCap, maxCap;
		cin >> node1 >> node2 >> minCap >> maxCap;

		capReal[node1] -= minCap;
		capReal[node2] += minCap;
		edgeAdder.addEdge(node1, node2, maxCap - minCap);
	}

	int rest = 0, need = 0;
	for (int i = 0; i < nNode; i++) {
		if (capReal[i] > capNeed[i]) {
			rest += (capReal[i] - capNeed[i]);
			edgeAdder.addEdge(source, i, capReal[i] - capNeed[i]);
		} else if (capReal[i] < capNeed[i]) {
			need += (capNeed[i] - capReal[i]);
			edgeAdder.addEdge(i, target, capNeed[i] - capReal[i]);
		}
	}

	long flow = push_relabel_max_flow(G, source, target);
	if (flow == need && rest >= need) {
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
		kingdom();
	}
	return 0;
}