#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <cmath>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> V;
typedef CGAL::Triangulation_data_structure_2<V> T;
typedef CGAL::Delaunay_triangulation_2<K, T> Triangulation;

typedef Triangulation::Finite_edges_iterator Edge_iter;
typedef Triangulation::Finite_vertices_iterator Vertex_iter;
typedef Triangulation::Vertex_handle Vertex_handle;

using namespace std;

int find(int x, vector<int> &root) {

	if (root[x] == x) {
		return x;
	} else {
		root[x] = find(root[x], root);
		return root[x];
	}

}

void merge(int x, int y, vector<int> &root) {

	int u = find(x, root);
	int v = find(y, root);
	if (u != v) {
		root[v] = u;
	}

}

bool bfs(vector< vector<int> > &neighbor, vector<int> &visited) {

	queue<int> q;
	for (int i = 0; i < neighbor.size(); ++i) {
		if (visited[i] == -1) {
			q.push(i);
			visited[i] = 0;
			while (!q.empty()) {
				int src = q.front();
				q.pop();
				for (int j = 0; j < neighbor[src].size(); ++j) {
					int tgt = neighbor[src][j];
					if (visited[tgt] == -1) {
						visited[tgt] = !visited[src];
						q.push(tgt);
					} else if (visited[tgt] == visited[src]) {
						return false;
					}
				}
			}
		}
	}
	return true;

}

void clues() {

	int nS, nQ, R;
	cin >> nS >> nQ >> R;
	double R_square = double(R) * double(R);

	vector<int> root(nS);
	vector<K::Point_2> stationNoIdx(nS);
	vector< pair<K::Point_2, int> > station(nS);
	for (int i = 0; i < nS; i++) {
		cin >> stationNoIdx[i];
		station[i] = make_pair(stationNoIdx[i], i);
		root[i] = i;
	}

	Triangulation tri;
	tri.insert(station.begin(), station.end());

	vector< vector<int> > neighbor(nS);
	for (Edge_iter e = tri.finite_edges_begin(); e != tri.finite_edges_end(); ++e) {
		int src = e->first->vertex((e->second + 1) % 3)->info();
		int tgt = e->first->vertex((e->second + 2) % 3)->info();
		double dist_square = CGAL::to_double(CGAL::squared_distance(stationNoIdx[src], stationNoIdx[tgt]));
		if (dist_square <= R_square) {
			neighbor[src].push_back(tgt);
			neighbor[tgt].push_back(src);
			merge(src, tgt, root);
		}
	}

	vector<int> visited(nS, -1);
	bool flag = bfs(neighbor, visited);
	if (flag) {
		vector< vector<K::Point_2> > sub(2);
		vector<Triangulation> subTri(2);
		for (int i = 0; i < nS; ++i) {
			sub[visited[i]].push_back(stationNoIdx[i]);
		}
		for (int i = 0; i < 2; ++i) {
			subTri[i].insert(sub[i].begin(), sub[i].end());
			for (Edge_iter e = subTri[i].finite_edges_begin(); e != subTri[i].finite_edges_end(); ++e) {
				K::Segment_2 seg = subTri[i].segment(e);
				double dist_square = CGAL::to_double(CGAL::squared_distance(seg.source(), seg.target()));
				if (dist_square <= R_square) {
					flag = false;
					break;
				}
			}
			if (!flag) {
				break;
			}
		}
	}

	for (int i = 0; i < nQ; i++) {
		K::Point_2 source, target;
		cin >> source >> target;
		if (!flag) {
			cout << "n";
			continue;
		}
		bool tempFlag = flag;
		int s = tri.nearest_vertex(source)->info();
		int t = tri.nearest_vertex(target)->info();
		double dist = CGAL::to_double(CGAL::squared_distance(source, target));
		double dist1 = CGAL::to_double(CGAL::squared_distance(source, stationNoIdx[s]));
		double dist2 = CGAL::to_double(CGAL::squared_distance(target, stationNoIdx[t]));
		if (dist > R_square) {
			tempFlag = tempFlag && (dist1 <= R_square) && (dist2 <= R_square);
			tempFlag = tempFlag && (find(s, root) == find(t, root));
		}
		if (tempFlag) {
			cout << "y";
		} else {
			cout << "n";
		}
	}
	cout << endl;

}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		clues();
	}
	return 0;
}
