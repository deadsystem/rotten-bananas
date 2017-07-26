
#include <vector>
#include <queue>
#include <stack>
#include "graph.hpp"
#define ll long long
using namespace std;

graph::graph(int vertices) {
	v = vertices;
	edges = 0;
	al = new vector<edge>[v];
}

void graph::add_edge(int a, int b, ll weight) {
	edge e0 (a,b,weight);
	edge e1 (b,a,weight);
	al[a].push_back(e0);
	al[b].push_back(e1);
	edges++;
}

bool graph::connected() {
	bool* vis = new bool[v]; // 1 if visited, 0 otherwise
	for (int i=1;i<v;i++) vis[i] = 0;
	// start by visiting 0
	queue<int> q;
	q.push(0);
	vis[0] = 1;
	int nvis = 1; // number of nodes visited
	while (q.size()) { // iterate through queue
		int x = q.front();
		q.pop();
		// visit unvisited adjacent nodes and add to queue
		for (edge e : al[x]) {
			if (!vis[e.e]) {
				vis[e.e] = 1;
				q.push(e.e);
				nvis ++;
			}
		}
	}
	delete [] vis;
	return nvis == v; // connected iff all nodes visited
}

// finds min spanning tree using kruskal's algorithm
vector<edge> graph::min_spanning_tree() {
	vector<edge> ans;
	bool* vis = new bool[v];
	for (int i=1;i<v;i++) vis[i] = 0;
	vis[0] = 1;
	// priority queues are what makes algorithms like kruskal and dijkstra O(e log v) instead of O(v^2) or worse
	priority_queue<edge, vector<edge>, Compare> pq;
	for (edge e : al[0]) pq.push(e);
	while (pq.size()) {
		edge e = pq.top();
		pq.pop();
		if (vis[e.e]) continue;
		vis[e.e] = 1;
		ans.push_back(e);
		for (edge f : al[e.e]) {
			if (!vis[f.e]) pq.push(f);
		}
	}
	delete [] vis;
	return ans;
}

vector<int> graph::tree_path(int a, int b) {
	// test if graph is actually a tree (must be connected and edges=v-1)
	vector<int> ans;
	if (!(connected() && edges == v-1)) return ans; // just return some trash if it's not a tree
	// a unqiue path will exist given that the graph is tree
	// proceed with a dfs to find (for each vertex) the previous node visited on the path from b to the vertex
	int* prev = new int[v];
	for (int i=0;i<v;i++) prev[i] = -1;
	prev[b] = b;
	stack<int> s;
	s.push(b);
	while (s.size()) { // start dfs at b
		int x = s.top();
		s.pop();
		for (edge e : al[x]) {
			if (prev[e.e] == -1) {
				prev[e.e] = x;
				if (e.e == a) break; // if we reached a, we can just stop
				s.push(e.e);
			}
		}
	}
	// reverse the steps to reach a from b
	// this creates a vector containing all nodes in the path from a to b
	ans.push_back(a);
	while (a != b) {
		a = prev[a];
		ans.push_back(a);
	}
	return ans;
}

graph::~graph() {
	delete [] al;
}




















