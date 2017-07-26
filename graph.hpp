


#include <vector>
#define ll long long
using namespace std;

struct edge {
	int s, e; // start, end
	ll w; // weight
	edge(int ss, int ee, ll ww) {
		s = ss;
		e = ee;
		w = ww;
	}
};


class Compare { // compare class for priority queue
public:
	bool operator() (edge a, edge b) {
		return a.w > b.w;
	}
};

// a very simple graph class that does not store values for the vertices
// all vertices are referred to by a unique index (0 through n-1). they do not have their own struct
// this is sufficient for our purposes
class graph {
private:
	vector<edge>* al; // adjacency list
	int v, edges; // number of vertices, number of edges
public:
	graph(int vertices);
	void add_edge(int a, int b, ll weight); // adds edge between a and b with given weight
	bool connected(); // bfs traversal to test if graph is connected
	vector<edge> min_spanning_tree(); // finds min spanning tree, assuming the graph is connected
	vector<int> tree_path(int a, int b); // path between two nodes on a tree. will return some trash if graph is not a tree
	virtual ~graph();
};

