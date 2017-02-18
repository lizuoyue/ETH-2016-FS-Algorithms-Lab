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

void knights() {
	int nCol, nRow, nPeople, C;
	cin >> nCol >> nRow >> nPeople >> C;

	int source = nCol * nRow * 2;
	int target = source + 1;
	Graph G(source + 2);

	EdgeCapacityMap edgeCap = get(edge_capacity, G);
	ReverseEdgeMap revEdge = get(edge_reverse, G);
	ResidualCapacityMap resCap = get(edge_residual_capacity, G);
	EdgeAdder edgeAdder(G, edgeCap, revEdge);

	for (int i = 0; i < nPeople; i++) {
		int col, row;
		cin >> col >> row;
		int nodeI = (row * nCol + col) * 2;
		edgeAdder.addEdge(source, nodeI, 1);
	}

	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			int nodeI = (i * nCol + j) * 2;
			int nodeO = nodeI + 1;
			edgeAdder.addEdge(nodeI, nodeO, C);

			if (i != 0) {
				edgeAdder.addEdge(nodeO, ((i - 1) * nCol + j) * 2, 1);
			}
			if (i != (nRow - 1)) {
				edgeAdder.addEdge(nodeO, ((i + 1) * nCol + j) * 2, 1);
			}

			if (j != 0) {
				edgeAdder.addEdge(nodeO, (i * nCol + j - 1) * 2, 1);
			}
			if (j != (nCol - 1)) {
				edgeAdder.addEdge(nodeO, (i * nCol + j + 1) * 2, 1);
			}

			if ((i == 0) || (i == (nRow - 1))) {
				edgeAdder.addEdge(nodeO, target, 1);
			}
			if ((j == 0) || (j == (nCol - 1))) {
				edgeAdder.addEdge(nodeO, target, 1);
			}
		}
	}

	long flow = push_relabel_max_flow(G, source, target);
	cout << flow << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		knights();
	}
	return 0;
}