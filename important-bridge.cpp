#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <list>

#include <boost/config.hpp>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

namespace boost {
	struct edge_component_t {
		enum { num = 555 };
		typedef edge_property_tag kind;
	}
	edge_component;
}

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_component_t, int> > Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIt;
typedef property_map<Graph, edge_component_t>::type EdgeComponent;

void bridge() {

	int nV, nE;
	cin >> nV >> nE;

	Graph G(nV);
	EdgeComponent comp = get(edge_component, G);
	for (int i = 0; i < nE; i++) {
		int u, v;
		cin >> u >> v;
		add_edge(u, v, G);
	}
	int nComp = biconnected_components(G, comp);

	vector< vector< pair<int, int> > > compEdge(nComp);
	EdgeIt ebeg, eend;
	for (tie(ebeg, eend) = edges(G); ebeg != eend; ++ebeg) {
		Vertex u = source(*ebeg, G);
		Vertex v = target(*ebeg, G);
		compEdge[comp[*ebeg]].push_back(make_pair(u, v));
	}

	vector< pair<int, int> > bridge;
	for (int i = 0; i < compEdge.size(); ++i) {
		if (compEdge[i].size() == 1) {
			if (compEdge[i][0].first < compEdge[i][0].second) {
				bridge.push_back(compEdge[i][0]);
			} else {
				bridge.push_back(make_pair(compEdge[i][0].second, compEdge[i][0].first));
			}
		}
	}
	sort(bridge.begin(), bridge.end());
	cout << bridge.size() << endl;
	for (int i = 0; i < bridge.size(); i++) {
		cout << bridge[i].first << " " << bridge[i].second << endl;
	}

}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		bridge();
	}
	return 0;
}
