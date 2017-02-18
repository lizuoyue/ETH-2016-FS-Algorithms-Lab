#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef Triangulation::Finite_edges_iterator Edge_iterator;

using namespace std;

void germs(int nPoint) {

	double left, down, right, up;
	cin >> left >> down >> right >> up;

	vector<K::Point_2> point(nPoint);
	for (int i = 0; i < nPoint; i++) {
		cin >> point[i];
	}

	Triangulation tri;
	tri.insert(point.begin(), point.end());

	map<K::Point_2, double> dist;

	for (Vertex_iterator v = tri.finite_vertices_begin(); v != tri.finite_vertices_end(); ++v) {
		K::Point_2 point = v->point();
		double temp1 = min(point.x() - left, right - point.x());
		double temp2 = min(point.y() - down, up - point.y());
		dist[point] = min(temp1, temp2);
	}

	for (Edge_iterator e = tri.finite_edges_begin(); e != tri.finite_edges_end(); ++e) {

		K::Segment_2 seg = tri.segment(e);
		K::Point_2 src = seg.source();
		K::Point_2 tgt = seg.target();

		double deltaX = src[0] - tgt[0];
		double deltaY = src[1] - tgt[1];
		double distance = sqrt(deltaX * deltaX + deltaY * deltaY) / 2.0;

		dist[src] = min(dist[src], distance);
		dist[tgt] = min(dist[tgt], distance);
	}

	vector<double> result;
	for (map<K::Point_2, double>::iterator iter = dist.begin(); iter != dist.end(); ++iter) {
		result.push_back(iter->second);
	}

	sort(result.begin(), result.end());
	int f = ceil(sqrt(result[0] - 0.5));
	int m = ceil(sqrt(result[result.size() / 2] - 0.5));
	int l = ceil(sqrt(result[result.size() - 1] - 0.5));
	cout << f << " " << m << " " << l << endl;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int nPoint;
	cin >> nPoint;
	while (nPoint > 0) {
		germs(nPoint);
		cin >> nPoint;
	}
	return 0;
}
