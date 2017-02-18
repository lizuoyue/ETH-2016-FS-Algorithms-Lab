#include <iostream>
#include <vector>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<
			vecS,
			vecS,
			undirectedS,
			no_property,
			property<edge_weight_t, int>
		> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

void bgl() {

	// Initialization
	int nV, nE;
	cin >> nV >> nE;
	Graph G(nV);
	WeightMap lenEdge = get(edge_weight, G);
	for (int i = 0; i < nE; i++) {
		int v1, v2, len;
		cin >> v1 >> v2 >> len;
		Edge e;
		bool success;
		tie(e, success) = add_edge(v1, v2, G);
		lenEdge[e] = len;
	}

	// Prim Minimum Spanning Tree
	vector<Vertex> primPreMap(nV);
	Vertex primStart = 0;
	prim_minimum_spanning_tree(
		G,
		make_iterator_property_map(
			primPreMap.begin(),
			get(vertex_index, G)
		),
		root_vertex(primStart)
	);
	int totalLen = 0;
	for (int i = 0; i < nV; i++) {
		if (primPreMap[i] != i) {
			Edge e;
			bool success;
			tie(e, success) = edge(i, primPreMap[i], G);
			totalLen += lenEdge[e];
		}
	}
	cout << totalLen << " ";

	// Dijkstra Shortest Paths
	vector<Vertex> dijkPreMap(nV);
	vector<int> distMap(nV);
	Vertex dijkStart = 0;
	dijkstra_shortest_paths(
		G,
		dijkStart,
		predecessor_map(
			make_iterator_property_map(
				dijkPreMap.begin(),
				get(vertex_index, G)
			)
		).distance_map(
			make_iterator_property_map(
				distMap.begin(),
				get(vertex_index, G)
			)
		)
	);
	int maxDist = 0;
	for (int i = 0; i < nV; i++) {
		if (distMap[i] < INT_MAX && distMap[i] > maxDist) {
			maxDist = distMap[i];
		}
	}
	cout << maxDist << endl;
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		bgl();
	}
	return 0;
}