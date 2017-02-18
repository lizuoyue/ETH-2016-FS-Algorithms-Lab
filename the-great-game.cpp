#include <iostream>
#include <vector>
#include <cmath>

#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;

int min_step(Graph &G, Vertex start, int nV);
int max_step(Graph &G, Vertex start, int nV);
vector<int> min_step_record;
vector<int> max_step_record;

int min_step(Graph &G, Vertex start, int nV) {
	if (min_step_record[start] == -1) {
		int step_num;
		if (start == nV - 1) {
			step_num = 0;
		} else {
			step_num = nV - 1;
		}
		OutEdgeIt outBegin, outEnd;
		for (tie(outBegin, outEnd) = out_edges(start, G); outBegin != outEnd; outBegin++) {
			Vertex end = target(*outBegin, G);
			step_num = min(step_num, max_step(G, end, nV) + 1);
		}
		min_step_record[start] = step_num;
		return step_num;
	} else {
		return min_step_record[start];
	}
}

int max_step(Graph &G, Vertex start, int nV) {
	if (max_step_record[start] == -1) {
		int step_num = 0;
		if (start == nV - 1) {
			step_num = 0;
		} else {
			step_num = 1;
		}
		OutEdgeIt outBegin, outEnd;
		for (tie(outBegin, outEnd) = out_edges(start, G); outBegin != outEnd; outBegin++) {
			Vertex end = target(*outBegin, G);
			step_num = max(step_num, min_step(G, end, nV) + 1);
		}
		max_step_record[start] = step_num;
		return step_num;
	} else {
		return max_step_record[start];
	}
}

void great_game() {

	int nV, nE, redStart, blackStart;
	cin >> nV >> nE >> redStart >> blackStart;
	redStart--;
	blackStart--;

	Graph G(nV);
	for (int i = 0; i < nE; i++) {
		int u, v;
		cin >> u >> v;
		Edge e;
		bool success;
		tie(e, success) = add_edge(u - 1, v - 1, G);
	}

	min_step_record.clear();
	min_step_record.resize(nV, -1);
	max_step_record.clear();
	max_step_record.resize(nV, -1);

	int stepRed = min_step(G, redStart, nV);
	int stepBlack = min_step(G, blackStart, nV);
	//cout << stepRed << " " << stepBlack << endl;

	if (stepRed < stepBlack) {
		cout << "0" << endl;
	} else if (stepRed > stepBlack) {
		cout << "1" << endl;
	} else {
		cout << (stepRed % 2 == 0) << endl;
	}
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		great_game();
	}
	return 0;
}
