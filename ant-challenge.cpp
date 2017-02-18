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

void ant_challenges() {

	// Initialization
	int nV, nE, nS, startV, endV;
	cin >> nV >> nE >> nS >> startV >> endV;
	vector<Graph> G(nS, Graph(nV));
	vector<WeightMap> lenEdge(nS);
	vector<int> hive(nS);
	vector<int> v1(nE);
	vector<int> v2(nE);

	for (int i = 0; i < nS; i++) {
		lenEdge[i] = get(edge_weight, G[i]);
	}
	
	for (int i = 0; i < nE; i++) {
		cin >> v1[i] >> v2[i];
		for (int j = 0; j < nS; j++) {
			int len;
			cin >> len;
			Edge e;
			bool success;
			tie(e, success) = add_edge(v1[i], v2[i], G[j]);
			lenEdge[j][e] = len;
		}
	}

	for (int i = 0; i < nS; i++) {
		cin >> hive[i];
	}

	// Prim Minimum Spanning Tree
	vector< vector<Vertex>> primPreMap(nS, vector<Vertex>(nV));
	for (int i = 0; i < nS; i++) {
		prim_minimum_spanning_tree(
			G[i],
			make_iterator_property_map(
				primPreMap[i].begin(),
				get(vertex_index, G[i])
			),
			root_vertex(hive[i])
		);
	}
	
	// Combined Graph
	Graph combinedG(nV);
	WeightMap combinedLenEdge = get(edge_weight, combinedG);
	for (int i = 0; i < nE; i++) {
		Edge e;
		bool success;
		tie(e, success) = add_edge(v1[i], v2[i], combinedG);
		int minLen = INT_MAX;
		for (int j = 0; j < nS; j++) {
			Edge tempE;
			bool tempSuccess;
			if (primPreMap[j][v1[i]] == v2[i]) {
				tie(tempE, tempSuccess) = edge(v1[i], v2[i], G[j]);
			} else if (primPreMap[j][v2[i]] == v1[i]) {
				tie(tempE, tempSuccess) = edge(v2[i], v1[i], G[j]);
			} else {
				continue;
			}
			int tempLen = lenEdge[j][tempE];
			if (tempLen < minLen) {
				minLen = tempLen;
			}
		}
		combinedLenEdge[e] = minLen;
	}

	// Dijkstra Shortest Paths
	vector<Vertex> dijkPreMap(nV);
	vector<int> distMap(nV);
	dijkstra_shortest_paths(
		combinedG,
		startV,
		predecessor_map(
			make_iterator_property_map(
				dijkPreMap.begin(),
				get(vertex_index, combinedG)
			)
		).distance_map(
			make_iterator_property_map(
				distMap.begin(),
				get(vertex_index, combinedG)
			)
		)
	);
	cout << distMap[endV] << endl;
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		ant_challenges();
	}
	return 0;
}