#include <iostream>
#include <vector>
#include <cmath>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;

using namespace std;

void bistro(int nPoint) {

	vector<K::Point_2> points(nPoint);
	for (int i = 0; i < nPoint; i++) {
		cin >> points[i];
	}

	Triangulation tri;
	tri.insert(points.begin(), points.end());


	int nNewPoint;
	cin >> nNewPoint;
	for (int i = 0; i < nNewPoint; i++) {
		K::Point_2 newPoint;
		cin >> newPoint;
		Vertex_handle target = tri.nearest_vertex(newPoint);
		double deltaX = target->point()[0] - newPoint[0];
		double deltaY = target->point()[1] - newPoint[1];
		cout << setprecision(0) << setiosflags(ios::fixed) << round(deltaX * deltaX + deltaY * deltaY) << endl;
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int nPoint;
	cin >> nPoint;
	while (nPoint > 0) {
		bistro(nPoint);
		cin >> nPoint;
	}
}
