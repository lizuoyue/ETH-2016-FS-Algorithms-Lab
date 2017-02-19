#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator Ei;
typedef Triangulation::Vertex_handle Vh;

#include <boost/pending/disjoint_sets.hpp>
typedef boost::disjoint_sets_with_storage<> uf;

using namespace std;
using namespace boost;

struct myedge {
	K::FT dist;
	int u, v;
	const bool operator<(const myedge e) const {
		return dist < e.dist;
	}
};

double ceil_to_double(const K::FT& x) {
	double a = ceil(CGAL::to_double(x));
	while (a < x) a += 1;
	while (a - 1 >= x) a -= 1;
	return a;
}

void gold() {

	int n, m;
	K::FT p;
	cin >> n >> m >> p;

	vector<pair<K::Point_2, int> > jammer(n);
	for (int i = 0; i < n; ++i) {
		cin >> jammer[i].first;
		jammer[i].second = i;
	}

	Triangulation tri;
	tri.insert(jammer.begin(), jammer.end());

	uf jc(n);
	vector<myedge> edgeList;
	for (Ei e = tri.finite_edges_begin(); e != tri.finite_edges_end(); ++e) {
		K::Segment_2 seg = tri.segment(e);
		K::FT dist = CGAL::squared_distance(seg.source(), seg.target());
		Vh vh1 = e->first->vertex((e->second + 1) % 3);
		Vh vh2 = e->first->vertex((e->second + 2) % 3);
		if (dist <= p) {
			jc.union_set(vh1->info(), vh2->info());
		}
		myedge edge;
		edge.dist = dist;
		edge.u = vh1->info();
		edge.v = vh2->info();
		edgeList.push_back(edge);
	}
	sort(edgeList.begin(), edgeList.end());

	vector<K::Point_2> src(m), tgt(m);
	vector<Vh> v1(m), v2(m);
	vector<K::FT> dist1(m), dist2(m);
	vector<bool> result(m, false);
	for (int i = 0; i < m; ++i) {
		cin >> src[i] >> tgt[i];
		v1[i] = tri.nearest_vertex(src[i]);
		v2[i] = tri.nearest_vertex(tgt[i]);
		dist1[i] = CGAL::squared_distance(src[i], v1[i]->point());
		dist2[i] = CGAL::squared_distance(tgt[i], v2[i]->point());
		result[i] = (dist1[i] <= p / 4 && dist2[i] <= p / 4 && jc.find_set(v1[i]->info()) == jc.find_set(v2[i]->info()));
	}

	uf ja(n);
	K::FT a = 0;
	int idx = -1;
	for (int i = 0; i < m; ++i) {
		a = max(a, dist1[i] * 4);
		a = max(a, dist2[i] * 4);
		while (ja.find_set(v1[i]->info()) != ja.find_set(v2[i]->info())) {
			++idx;
			ja.union_set(edgeList[idx].u, edgeList[idx].v);
			a = max(a, edgeList[idx].dist);
		}
	}

	uf jb(n);
	K::FT b = 0;
	idx = -1;
	for (int i = 0; i < m; ++i) {
		if (result[i]) {
			b = max(b, dist1[i] * 4);
			b = max(b, dist2[i] * 4);
			while (jb.find_set(v1[i]->info()) != jb.find_set(v2[i]->info())) {
				++idx;
				jb.union_set(edgeList[idx].u, edgeList[idx].v);
				b = max(b, edgeList[idx].dist);
			}
		}
	}

	for (int i = 0; i < result.size(); ++i) {
		if (result[i]) {
			cout << "y";
		} else {
			cout << "n";
		}
	}

	cout << endl << setiosflags(ios::fixed) << setprecision(0) << ceil_to_double(a) << endl << ceil_to_double(b) << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int i = 0; i < T; ++i) {
		gold();
	}
	return 0;
}