
#define ll long long
using namespace std;

struct P {
	ll min, max, sum;
	P(ll a, ll b, ll c) {
		min = a; max = b; sum = c;
	}
};

class segtree {
private:
	int n; // size
	ll* lazy; // lazy propagation
	ll* sumtree;
	ll* mintree;
	ll* maxtree;
	void propagate(int node, int sess);
	P query(int node, int ss, int se, int i, int j);
	void update(int node, int ss, int se, int i, int j, ll val);
public:
	segtree(int size);
	void update(int i, int j, ll val);
	ll queryMin(int i, int j);
	ll queryMax(int i, int j);
	ll querySum(int i, int j);
	int size();
	ll at(int a);
	virtual ~segtree();
};
