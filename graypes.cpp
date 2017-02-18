#include <iostream>
#include <vector>
#include <cmath>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;

using namespace std;

void graypes(int nPoint) {

	vector<K::Point_2> points(nPoint);
	for (int i = 0; i < nPoint; i++) {
		cin >> points[i];
	}

	Triangulation tri;
	tri.insert(points.begin(), points.end());

	double minDist = (1 << 30);
	for (Edge_iterator e = tri.finite_edges_begin(); e != tri.finite_edges_end(); e++) {
		double deltaX = tri.segment(e)[0][0] - tri.segment(e)[1][0];
		double deltaY = tri.segment(e)[0][1] - tri.segment(e)[1][1];
		minDist = min(minDist, deltaX * deltaX + deltaY * deltaY);
	}
	cout << int(ceil(sqrt(minDist) * 50.0)) << endl;
}

int main(void) {
	int nPoint;
	cin >> nPoint;
	while (nPoint > 0) {
		graypes(nPoint);
		cin >> nPoint;
	}
}
