#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor,
				property <edge_weight_t, long> > > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;

class EdgeAdder {

	Graph &G;
	EdgeCapacityMap &capacitymap;
	EdgeWeightMap &weightmap;
	ReverseEdgeMap  &revedgemap;

	public:

	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
		: G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

	void addEdge(int u, int v, long c, long w) {
		Edge e, reverseE;
		tie(e, tuples::ignore) = add_edge(u, v, G);
		tie(reverseE, tuples::ignore) = add_edge(v, u, G);
		capacitymap[e] = c;
		weightmap[e] = w;
		capacitymap[reverseE] = 0;
		weightmap[reverseE] = -w;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
	}

};

struct request {
	int src, tgt, dpt, arv, rwd;
};

void carsharing() {

	int nP, nS;
	cin >> nP >> nS;

	int totalCar = 0;
	vector<int> initNum(nS);
	for (int i = 0; i < nS; i++) {
		cin >> initNum[i];
		totalCar += initNum[i];
	}

	vector<request> booking(nP);
	vector< map<int, int> > stationTimeMap(nS);
	int min_time = INT_MAX, max_time = 0;
	for (int i = 0; i < nP; i++) {
		cin >> booking[i].src >> booking[i].tgt >> booking[i].dpt >> booking[i].arv >> booking[i].rwd;
		booking[i].src -= 1;
		booking[i].tgt -= 1;
		stationTimeMap[booking[i].src][booking[i].dpt] = 1;
		stationTimeMap[booking[i].tgt][booking[i].arv] = 1;
		min_time = min(min_time, booking[i].dpt);
		max_time = max(max_time, booking[i].arv);
	}

	vector< vector<int> > stationTime(nS);
	for (int i = 0; i < nS; i++) {
		stationTimeMap[i][min_time] = 1;
		stationTimeMap[i][max_time] = 1;
		for (map<int, int>::iterator iter = stationTimeMap[i].begin(); iter != stationTimeMap[i].end(); ++iter) {
			stationTime[i].push_back(iter->first);
		}
		sort(stationTime[i].begin(), stationTime[i].end());
	}

	int k = 0;
	for (int i = 0; i < nS; i++) {
		//cout << i + 1 << ": ";
		for (int j = 0; j < stationTime[i].size(); j++) {
			//cout << stationTime[i][j] << " ";
			stationTimeMap[i][stationTime[i][j]] = k;
			k++;
		}
		//cout << endl;
	}
	//cout << "====" << k << "====" << endl;

	const int source = k;
	const int target = k + 1;
	const int delta = 100;

	Graph G(k + 2);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	EdgeWeightMap weightmap = get(edge_weight, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder edgeAdder(G, capacitymap, weightmap, revedgemap);

	for (int i = 0; i < nS; i++) {
		int firstNode = stationTimeMap[i][stationTime[i].front()];
		int lastNode = stationTimeMap[i][stationTime[i].back()];
		edgeAdder.addEdge(source, firstNode, initNum[i], 0);
		edgeAdder.addEdge(lastNode, target, INT_MAX, 0);
	}

	for (int i = 0; i < nP; i++) {
		int begin = stationTimeMap[booking[i].src][booking[i].dpt];
		int end   = stationTimeMap[booking[i].tgt][booking[i].arv];
		edgeAdder.addEdge(begin, end, 1, delta * (booking[i].arv - booking[i].dpt) - booking[i].rwd);
	}

	k = 0;
	for (int i = 0; i < nS; i++) {
		k++;
		for (int j = 1; j < stationTime[i].size(); j++) {
			edgeAdder.addEdge(k - 1, k, INT_MAX, delta * (stationTime[i][j] - stationTime[i][j - 1]));
			k++;
		}
	}

	/*
	int flow = push_relabel_max_flow(G, source, target);
	cycle_canceling(G);
	int cost = find_flow_cost(G);
	*/

	successive_shortest_path_nonnegative_weights(G, source, target);
	int cost = find_flow_cost(G);

	cout << totalCar * (max_time - min_time) * delta - cost << endl;

}

int main(void) {
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		carsharing();
	}
	return 0;
}
