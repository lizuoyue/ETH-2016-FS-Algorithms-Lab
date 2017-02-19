#include <iostream>
#include <climits>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property,
			property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

void burden() {

	int n;
	cin >> n;
	int nV = n * (n + 1) / 2;

	Graph G(nV * 2);
	WeightMap weightmap = get(edge_weight, G);

	int p = 0;
	vector< vector<int> > val(n);
	vector< vector<int> > index(n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			int w;
			cin >> w;
			val[i].push_back(w);
			index[i].push_back(p);

			Edge e;	bool success;
			tie(e, success) = add_edge(p, p + 1, G);
			weightmap[e] = w;
			p += 2;
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			int src = index[i][j] + 1;
			if (j != 0) {
				int tgt = index[i][j - 1];
				Edge e;	bool success;
				tie(e, success) = add_edge(src, tgt, G);
				weightmap[e] = 0;
			}
			if (i != 0 && j != 0) {
				int tgt = index[i - 1][j - 1];
				Edge e;	bool success;
				tie(e, success) = add_edge(src, tgt, G);
				weightmap[e] = 0;
			}
			if (j != i) {
				int tgt = index[i][j + 1];
				Edge e;	bool success;
				tie(e, success) = add_edge(src, tgt, G);
				weightmap[e] = 0;
			}
			if (i != (n - 1)) {
				int tgt = index[i + 1][j + 1];
				Edge e;	bool success;
				tie(e, success) = add_edge(src, tgt, G);
				weightmap[e] = 0;
			}
			if (i != 0 && j <= (i - 1)) {
				int tgt = index[i - 1][j];
				Edge e;	bool success;
				tie(e, success) = add_edge(src, tgt, G);
				weightmap[e] = 0;
			}
			if (i != (n - 1)) {
				int tgt = index[i + 1][j];
				Edge e;	bool success;
				tie(e, success) = add_edge(src, tgt, G);
				weightmap[e] = 0;
			}
		}
	}

	vector<int> distMap1(nV * 2);
	vector<int> predMap1(nV * 2);
	vector<int> distMap2(nV * 2);
	vector<int> predMap2(nV * 2);
	vector<int> distMap3(nV * 2);
	vector<int> predMap3(nV * 2);
	dijkstra_shortest_paths(G, index[0][0],
		predecessor_map(make_iterator_property_map(
			predMap1.begin(), get(vertex_index, G))).
		distance_map(make_iterator_property_map(
			distMap1.begin(), get(vertex_index, G))));
	dijkstra_shortest_paths(G, index[n - 1][0],
		predecessor_map(make_iterator_property_map(
			predMap2.begin(), get(vertex_index, G))).
		distance_map(make_iterator_property_map(
			distMap2.begin(), get(vertex_index, G))));
	dijkstra_shortest_paths(G, index[n - 1][n - 1],
		predecessor_map(make_iterator_property_map(
			predMap3.begin(), get(vertex_index, G))).
		distance_map(make_iterator_property_map(
			distMap3.begin(), get(vertex_index, G))));

	int min_val = INT_MAX;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			int idx = index[i][j] + 1;
			min_val = min(min_val, distMap1[idx] + distMap2[idx] + distMap3[idx] - 2 * val[i][j]);
		}
	}
	cout << min_val << endl;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		burden();
	}	
	return 0;
}
