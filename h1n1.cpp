#include <iostream>
#include <vector>
#include <cmath>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Edge_circulator Edge_circulator;

using namespace std;

int dfs(Triangulation &tri, Face_handle face, double dist, map<Face_handle, int> &isVisited) {

	isVisited[face] = 1;

	vector<double> deltaX(3);
	vector<double> deltaY(3);
	vector<double> constrain(3);

	deltaX[0] = face->vertex(1)->point().x() - face->vertex(2)->point().x();
	deltaX[1] = face->vertex(2)->point().x() - face->vertex(0)->point().x();
	deltaX[2] = face->vertex(0)->point().x() - face->vertex(1)->point().x();

	deltaY[0] = face->vertex(1)->point().y() - face->vertex(2)->point().y();
	deltaY[1] = face->vertex(2)->point().y() - face->vertex(0)->point().y();
	deltaY[2] = face->vertex(0)->point().y() - face->vertex(1)->point().y();

	for (int i = 0; i < 3; i++) {
		constrain[i] = (deltaX[i] * deltaX[i] + deltaY[i] * deltaY[i]) / 4.0;
		if (!tri.is_infinite(face->neighbor(i))) {
			if (dist <= constrain[i]) {
				if (isVisited[face->neighbor(i)] != 1) {
					if(dfs(tri, face->neighbor(i), dist, isVisited)) {
						return 1;
					};
				}
			}
		} else {
			if (dist <= constrain[i]) {
				return 1;
			}
		}
	}
	return 0;
}

void h1n1(int nPeople) {

	vector<K::Point_2> people(nPeople);
	for (int i = 0; i < nPeople; i++) {
		cin >> people[i];
	}

	Triangulation tri;
	tri.insert(people.begin(), people.end());

	int nNewPeople;
	cin >> nNewPeople;
	for (int i = 0; i < nNewPeople; i++) {
		K::Point_2 newPeople;
		double dist;
		cin >> newPeople;
		cin >> dist;

		Face_handle targetFace = tri.locate(newPeople);
		int isOutside = tri.is_infinite(targetFace);

		Vertex_handle targetPeople = tri.nearest_vertex(newPeople);
		K::Point_2 tp = targetPeople->point();

		double deltaX = tp.x() - newPeople.x();
		double deltaY = tp.y() - newPeople.y();
		double realDist = deltaX * deltaX + deltaY * deltaY;
		if (dist > realDist) {
			cout << "n";
		} else {
			if (isOutside) {
				cout << "y";
			} else {
				map<Face_handle, int> isVisited;
				int flag = dfs(tri, targetFace, dist, isVisited);
				if (flag) {
					cout << "y";
				} else {
					cout << "n";
				}
			}
		}
	}
	cout << endl;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	int nPeople;
	cin >> nPeople;
	while (nPeople > 0) {
		h1n1(nPeople);
		cin >> nPeople;
	}
}
