#include <iostream>
#include <climits>
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
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

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

void courier() {

	int nZ, nJ;
	cin >> nZ >> nJ;

	Graph G(nZ + nJ + 2);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	const int source = nZ + nJ;
	const int target = nZ + nJ + 1;

	int sum = 0;
	for (int i = 0; i < nZ; ++i) {
		int val; cin >> val;
		eaG.addEdge(i + nJ, target, val);
	}

	for (int i = 0; i < nJ; ++i) {
		int val; cin >> val;
		eaG.addEdge(source, i, val);
		sum += val;
	}

	for (int i = 0; i < nJ; ++i) {
		int num; cin >> num;
		for (int j = 0; j < num; ++j) {
			int val; cin >> val;
			eaG.addEdge(i, val + nJ, LONG_MAX);
		}
		
	}

	long flow = push_relabel_max_flow(G, source, target);
	cout << sum - flow << endl;

}

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		courier();
	}
	return 0;
}
