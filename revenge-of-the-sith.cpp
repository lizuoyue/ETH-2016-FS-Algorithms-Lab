#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

using namespace std;
using namespace boost;

vector<K::Point_2> planet;

bool ok(int k, int rad) {

	Triangulation tri;
	tri.insert(planet.begin() + k, planet.end());

	int nV = planet.size() - k;
	Graph G(nV);

	map<K::Point_2, int> idx;
	for (int i = k; i < planet.size(); i++) {
		idx[planet[i]] = i - k;
	}

	Edge_iterator e;
	for (e = tri.finite_edges_begin(); e != tri.finite_edges_end(); ++e) {
		K::Segment_2 seg = tri.segment(e);
		K::Point_2 source = seg.source();
		K::Point_2 target = seg.target();
		double dist = sqrt(CGAL::to_double(CGAL::squared_distance(source, target)));
		if (dist <= rad) {
			add_edge(idx[source], idx[target], G);
		}
	}

	vector<int> componentMap(nV);
	int ncc = connected_components(G, make_iterator_property_map(componentMap.begin(), get(vertex_index, G))); 
	vector<int> componentsize(ncc);
	for (int i = 0; i < nV; ++i)
		++componentsize[componentMap[i]];
	int result = 0;
	for (int i = 0; i < ncc; ++i)
		result = max(result, componentsize[i]);
	return (result >= k);
}

void sith() {

	int nV, rad;
	cin >> nV >> rad;

	planet.clear(); planet.resize(nV);
	for (int i = 0; i < nV; i++) {
		cin >> planet[i];
	}

	int left = 0;
	int right = nV / 2;
	
	while (left < right) {
		int mid = (left + right + 1) / 2;
		if (ok(mid, rad)) {
			left = mid;
		} else {
			right = mid - 1;
		}
	}
	cout << left << endl;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		sith();
	}
}
