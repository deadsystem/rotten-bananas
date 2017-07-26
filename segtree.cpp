
#include <climits>
#include <algorithm>
#include "segtree.hpp"
#define ll long long
using namespace std;

segtree::segtree(int size) {
	n = size;
	lazy = new ll[4*n];
	sumtree = new ll[4*n];
	mintree = new ll[4*n];
	maxtree = new ll[4*n];
	for (int i=0;i<4*n;i++) {
		lazy[i] = 0;
		sumtree[i] = 0;
		mintree[i] = 0;
		maxtree[i] = 0;
	}
}

void segtree::propagate(int node, int sess) {
	if (lazy[node] != 0) {
		maxtree[node] += lazy[node];
		mintree[node] += lazy[node];
		sumtree[node] += lazy[node] * sess;
		if (sess > 1) {
			lazy[2*node+1] += lazy[node];
			lazy[2*node+2] += lazy[node];
		}
		lazy[node] = 0;
	}
}

P segtree::query(int node, int ss, int se, int i, int j) {
	if (j<=ss || se<=i) {
		P zero (LLONG_MAX,LLONG_MIN,0);
		return zero;
	}
	propagate(node,se-ss);
	if (i<=ss && se<=j) {
		P ans(mintree[node], maxtree[node], sumtree[node]);
		return ans;
	}
	int m = (ss+se+1)/2;
	P q0 = query(2*node+1,ss,m,i,j);
	P q1 = query(2*node+2,m,se,i,j);
	P ans (
			min(q0.min,q1.min),
			max(q0.max,q1.max),
			q0.sum+q1.sum
	);
	return ans;
}

ll segtree::queryMin(int i, int j) {
	return query(0,0,n,i,j).min;
}
ll segtree::queryMax(int i, int j) {
	return query(0,0,n,i,j).max;
}
ll segtree::querySum(int i, int j) {
	return query(0,0,n,i,j).sum;
}

void segtree::update(int node, int ss, int se, int i, int j, ll val) {
	propagate(node,se-ss);
	if (j<=ss || se<=i) return;
	if (i<=ss && se<=j) {
		lazy[node] += val;
		propagate(node,se-ss);
		return;
	}
	int m = (ss+se+1)/2;
	update(2*node+1,ss,m,i,j,val);
	update(2*node+2,m,se,i,j,val);
	mintree[node] = min(mintree[2*node+1],mintree[2*node+2]);
	maxtree[node] = max(maxtree[2*node+1],maxtree[2*node+2]);
	sumtree[node] = sumtree[2*node+1]+sumtree[2*node+2];
}

void segtree::update(int i, int j, ll val) {
	update(0,0,n,i,j,val);
}

int segtree::size() {return n;}

ll segtree::at(int i) {return querySum(i,i+1);}

segtree::~segtree() {
	delete [] lazy;
	delete [] mintree;
	delete [] maxtree;
	delete [] sumtree;
}
