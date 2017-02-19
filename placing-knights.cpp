#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_iterator EdgeIt;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

void addEdge(int src, int u, int v, int n, vector< vector<int> > &map, Graph &G) {

	bool flag1 = (u >= 0), flag2 = (u < n), flag3 = (v >= 0), flag4 = (v < n);
	if (flag1 && flag2 && flag3 && flag4) {
		if (map[u][v] == 1) {
			int tgt = u * n + v;
			add_edge(src, tgt, G);
		}
	}

}

void placingknights() {

	int n;
	cin >> n;

	vector< vector<int> > map(n, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> map[i][j];
		}
	}

	Graph G(n * n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (map[i][j]) {
				int src = i * n + j;
				addEdge(src, i - 2, j - 1, n, map, G);
				addEdge(src, i - 2, j + 1, n, map, G);
				addEdge(src, i - 1, j - 2, n, map, G);
				addEdge(src, i - 1, j + 2, n, map, G);
				addEdge(src, i + 1, j - 2, n, map, G);
				addEdge(src, i + 1, j + 2, n, map, G);
				addEdge(src, i + 2, j - 1, n, map, G);
				addEdge(src, i + 2, j + 1, n, map, G);
			}
		}
	}

	vector<int> mateMap(n * n);
	edmonds_maximum_cardinality_matching(G, make_iterator_property_map(mateMap.begin(), get(vertex_index, G)));
	int matchingSize = matching_size(G, make_iterator_property_map(mateMap.begin(), get(vertex_index, G)));
	const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			matchingSize += (mateMap[i * n + j] == NULL_VERTEX) * map[i][j];
		}
	}
	cout << matchingSize << endl;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		placingknights();
	}
	return 0;
}