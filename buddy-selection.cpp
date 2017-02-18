#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

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

void buddies() {

	// Initialization
	int nPeople, nHobby, nSame;
	cin >> nPeople >> nHobby >> nSame;
	vector< vector<string> > hobby(nPeople);
	Graph G(nPeople);
	for (int i = 0; i < nPeople; i++) {
		for (int j = 0; j < nHobby; j++) {
			string tempHobby;
			cin >> tempHobby;
			hobby[i].push_back(tempHobby);
		}
		sort(hobby[i].begin(), hobby[i].end());
		for (int j = 0; j < i; j++) {
			int tempSame = 0;
			int a = 0, b = 0;
			while(a < nHobby && b < nHobby) {
				int result = hobby[i][a].compare(hobby[j][b]);
				if (result == 0) {
					tempSame++;
					a++;
					b++;
				} else if (result < 0) {
					a++;
				} else {
					b++;
				}
			}
			if (tempSame > nSame) {
				Edge e;
				bool success;
				tie(e, success) = add_edge(j, i, G);
			}
		}
	}

	vector<Vertex> mateMap(nPeople);
	edmonds_maximum_cardinality_matching(
		G,
		make_iterator_property_map(
			mateMap.begin(),
			get(vertex_index, G)
		)
	);
	int matchingSize = matching_size(
		G,
		make_iterator_property_map(
			mateMap.begin(),
			get(vertex_index, G)
		)
	);
	if (matchingSize == nPeople / 2) {
		cout << "not optimal" << endl;
	} else {
		cout << "optimal" << endl;
	}
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		buddies();
	}
	return 0;
}