#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;	
typedef property_map<Graph, edge_weight_t>::type WeightMap;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > undirGraph;
typedef graph_traits<undirGraph>::vertex_descriptor undirVertex;	

void avalanche() {
	int nV, nE, nA, nS, cap, delay;
	cin >> nV >> nE >> nA >> nS >> cap >> delay;

	Graph G(nV);
	WeightMap lenEdge = get(edge_weight, G);
	for (int i = 0; i < nE; i++) {
		char edgeType;
		int start, end, len;
		cin >> edgeType >> start >> end >> len;
		Edge e; bool success;
		if (edgeType == 'S') {
			tie(e, success) = add_edge(start, end, G);
			lenEdge[e] = len;
		} else if (edgeType == 'L') {
			tie(e, success) = add_edge(start, end, G);
			lenEdge[e] = len;
			tie(e, success) = add_edge(end, start, G);
			lenEdge[e] = len;
		}
	}

	vector<int> agentPos(nA);
	for (int i = 0; i < nA; i++) {
		cin >> agentPos[i];
	}

	vector<int> shelterPos(nS);
	for (int i = 0; i < nS; i++) {
		cin >> shelterPos[i];
	}

	vector< vector<int> > distTable(nA, vector<int>(nS, 0));
	for (int i = 0; i < nA; i++) {
		vector<int> dist(nV);
		dijkstra_shortest_paths(G, agentPos[i],
			distance_map(make_iterator_property_map(dist.begin(), get(vertex_index, G))));
		for (int j = 0; j < nS; j++) {
			distTable[i][j] = dist[shelterPos[j]];
		}
	}

	if (cap == 1) {
		int left = 0, right = 2147483647;
		while (left < right) {
			int boundary = (left + right) / 2;
			undirGraph bipartG(nA + nS);
			for (int i = 0; i < nA; i++) {
				for (int j = 0; j < nS; j++) {
					if (distTable[i][j] <= boundary) {
						add_edge(i, j + nA, bipartG);
					}
				}
			}

			vector<undirVertex> mate(nA + nS);
			edmonds_maximum_cardinality_matching(bipartG,
				make_iterator_property_map(mate.begin(), get(vertex_index, bipartG)));
			int numPair = matching_size(bipartG,
				make_iterator_property_map(mate.begin(), get(vertex_index, bipartG)));

			if (numPair < nA) {
				left = boundary + 1;
			} else {
				right = boundary;
			}
		}
		cout << left + delay << endl;
	} else if (cap == 2) {
		int left = 0, right = 2147483647;
		while (left < right) {
			int boundary = (left + right) / 2;
			undirGraph bipartG(nA + nS + nS);
			for (int i = 0; i < nA; i++) {
				for (int j = 0; j < nS; j++) {
					if (distTable[i][j] <= boundary) {
						add_edge(i, j + nA, bipartG);
					}
					if (distTable[i][j] != 2147483647 && (distTable[i][j] + delay) <= boundary) {
						add_edge(i, j + nS + nA, bipartG);
					}
				}
			}

			vector<undirVertex> mate(nA + nS + nS);
			edmonds_maximum_cardinality_matching(bipartG,
				make_iterator_property_map(mate.begin(), get(vertex_index, bipartG)));
			int numPair = matching_size(bipartG,
				make_iterator_property_map(mate.begin(), get(vertex_index, bipartG)));
			//cout << (numPair > nA);
			if (numPair < nA) {
				left = boundary + 1;
			} else {
				right = boundary;
			}
		}
		cout << left + delay << endl;
	}
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		avalanche();
	}
}