
#include <vector>
#include <iostream>
#include <map>
#include "segtree.hpp"
#include "graph.hpp"
using namespace std;

#define ll long long

// use `return die("Failed!")` if the user screws up
int die(string s) {
	cout << s << "\n" << "Program terminated due to user error" << endl;
	return 0;
}

int main() {
	// ===== phase 1: creating the graph =====
	cout << "In the country named Segfault, there are some cities and bidirectional roads." << endl;
	cout << "Since the people of Segfault are bad at naming, these cities are all given a number to be referred to as." << endl;
	cout << "It is possible to travel from any city to any other city using these roads."  << endl;
	cout << "No two roads connect the same two cities. Also, no road connects a city to itself." << endl;
	cout << "Each road is owned by some citizen of Segfault. They are all willing to sell their roads at some positive integer cost." << endl;
	cout << "You need to create this country!" << endl;
	cout << "Enter the number of cities:" << endl;
	int v; cin >> v;
	if (v<2 || v>1000000) {
		return die("Failed! City count must be between 2 and 1000000");
	}
	graph g(v);
	cout << "The city names will be the numbers from 0 through " << v-1 << endl;
	cout << "Enter the number of roads:" << endl;
	int edges; cin >> edges;
	if (edges<1) {
		return die("Failed! Edge count must be at least 1");
	}
	// we need to make sure there are no multiple edges or loops
	// for this, we'll use a stl map to store used edges
	map<pair<int,int>,bool> emap;
	for (int i=0;i<edges;i++) {
		int a, b;
		ll w;
		cout << "Enter first city that road " << i+1 << " connects:" << endl;
		cin >> a;
		if (a<0 || a>=v) {
			return die("Failed! That is not a valid city");
		}
		cout << "Enter second city that road " << i+1 << " connects:" << endl;
		cin >> b;
		if (b<0 || b>=v) {
			return die("Failed! That is not a valid city");
		}
		// check if edge is valid
		if (a==b) {
			return die("Failed! A road cannot connect a city to itself");
		}
		if (emap.count({a,b})) {
			return die("Failed! There is already a road connecting those two cities");
		}
		cout << "Enter the cost that the owner of road " <<i+1<< " is willing to sell the road at:" << endl;
		cin >> w;
		if (w<=0) {
			return die("Failed! Road cost must be positive");
		}
		g.add_edge(a,b,w);
		emap[{a,b}] = 1;
		emap[{b,a}] = 1;
	}
	// ===== phase 2: minimum spanning tree =====
	if (!g.connected()) {
		return die("Error! Graph is not connected (it is not possible to go from any city to any other using the roads)");
	}
	cout << "A delivery company is opening in the country of Segfault!" << endl;
	cout << "But, for some reason, none of the road owners want delivery trucks on their roads." << endl;
	cout << "Thus, the delivery company needs to buy all the roads it wants to use!" << endl;
	cout << "The delivery company wants to buy some of the roads such that their trucks can go from any city to any other city using their roads." << endl;
	cout << "The company wants to spend as little money as possible to achieve this." << endl;
	cout << "The following roads will be bought:" << endl;
	vector<edge> mst = g.min_spanning_tree();
	ll totalcost = 0;
	for (edge e : mst) {
		totalcost += e.w;
		cout << " - Road connecting " << e.s << " and " << e.e << " (cost " << e.w << ")" << endl;
	}
	cout << "Total cost of these roads: " << totalcost << endl;
	// ===== phase 3: tree traversal =====
	cout << "One sector of the delivery company is responsible for delivering rotten bananas from city X to city Y." << endl;
	cout << "This sector is named Badbadbad." << endl;
	int cx, cy;
	cout << "Choose city X:" << endl;
	cin >> cx;
	if (cx<0 || cx>=v) {
		return die("Failed! That is not a valid city");
	}
	cout << "Choose city Y (cannot be " << cx << "):" << endl;
	cin >> cy;
	if (cy<0 || cy>=v) {
		return die("Failed! That is not a valid city");
	}
	if (cx==cy) return die("Failed!");
	// construct graph object with the min spanning tree
	graph st(v);
	for (edge e : mst) st.add_edge(e.s,e.e,e.w);
	// get and print the tree path
	vector<int> path = st.tree_path(cx,cy);
	cout << "This is the path between cities X and Y that Badbadbad will take to deliver rotten bananas:" << endl;
	for (int x : path) cout << x << " ";
	cout << "\nThis path is called the Badpath. Remember it!" << endl;
	// ===== phase 4: lazy propagating segment tree =====
	int n = path.size();
	// we need quick access to the locations of all the cities in the path, so we will make an accessor array
	int* index = new int[v];
	for (int i=0;i<v;i++) index[i] = -1;
	for (int i=0;i<n;i++) index[path[i]] = i;
	segtree tree(n);
	cout << "Unfortunately, Badbadbad's delivery trucks have holes in them!" << endl;
	cout << "Whenever they deliver rotten bananas, some bananas will fall in cities on the way from city "<< cx << " to " << cy << " (possibly including endpoints)!" << endl;
	cout << "In particular, for each delivery, there will be cities A and B on the Badpath, such that every city between A and B (including endpoints) will have K rotten bananas dropped on them!" << endl;
	cout << "Badbadbad starts out with a reputation of 0. It may go down, after people get angry at them for dropping rotten bananas." << endl;
	ll reputation = 0;
	while (1) {
		cout << "===== Options =====" << endl;
		cout << "1. Delivery: The company makes a delivery, and drops some rotten bananas." << endl;
		cout << "2. Cleanup: Some citizen decide to clean up some rotten bananas in their cities." << endl;
		cout << "3. Losses: The company decides to count how many rotten bananas they dropped." << endl;
		cout << "4. Bad reviews: Some citizen decides to count the maximum number of bananas dropped in the cities near them, and write a negative review for the company." << endl;
		cout << "5. Attack: Angry citizens shoot out delivery truck tires, forcing the company to shut down. This option should only be selected if the company has negative reputation." << endl;
		cout << "The company currently has "<<reputation<<" reputation points.\nSelect an option by it's number!" << endl;
		string option; cin >> option;
		if (option == "1") {
			cout << "The company made a rotten banana delivery between city " << cx << " and " << cy << "." << endl;
			cout << "Rotten bananas were dropped in all cities between two particular cities, A and B, on the Badpath. " << endl;
			cout << "Input city A:" << endl;
			int a; cin >> a;
			if (a<0 || a>=v) {
				return die("Failed! That is not a city");
			}
			if (index[a]<0) {
				return die("Failed! That city is not on the Badpath");
			}
			cout << "Input city B:" << endl;
			int b; cin >> b;
			if (b<0 || b>=v) {
				return die("Failed! That is not a city");
			}
			if (index[b]<0) {
				return die("Failed! That city is not on the Badpath");
			}
			cout << "Input the number of bananas dropped in each affected city:" << endl;
			ll k; cin >> k;
			if (k<=0) {
				return die("Failed! Number of bananas must be positive");
			}
			int ia = index[a];
			int ib = index[b];
			if (ia>ib) {
				int t = ia;
				ia = ib;
				ib = t;
			}
			tree.update(ia,ib+1,k);
			cout << "Rotten bananas dropped successfully!" << endl;
		}
		else if (option == "2") {
			cout << "A nice citizen of Segfault decides to clean up some rotten bananas!" << endl;
			cout << "They will choose two cities A and B on the Badpath, and clean up the same number of bananas from each city on the way from A to B on the Badpath!" << endl;
			cout << "Input city A:" << endl;
			int a; cin >> a;
			if (a<0 || a>=v) {
				return die("Failed! That is not a city");
			}
			if (index[a]<0) {
				return die("Failed! That city is not on the Badpath");
			}
			cout << "Input city B:" << endl;
			int b; cin >> b;
			if (b<0 || b>=v) {
				return die("Failed! That is not a city");
			}
			if (index[b]<0) {
				return die("Failed! That city is not on the Badpath");
			}
			// find minimum number of bananas in these cities
			int ia = index[a];
			int ib = index[b];
			if (ia>ib) {
				int t = ia;
				ia = ib;
				ib = t;
			}
			ll rmin = tree.queryMin(ia,ib+1);
			cout << "In the path between cities "<<a<<" and "<<b<<" on the Badpath, the city with the minimum number of rotten bananas contains "<<rmin<<" rotten bananas." << endl;
			cout << "Thus, the maximum number of bananas the nice citizen can clean up from each city in this segment is " << rmin << endl;
			cout << "Enter the number of bananas the nice citizen will clean up from each city:" << endl;
			ll k; cin >> k;
			if (k<0) {
				return die("Failed! The citizen cannot clean up a negative number of bananas!");
			}
			if (k>rmin) {
				return die("Failed! If the citizen cleaned up that many bananas from each city, some will have negative bananas!");
			}
			if (k>0) {
				tree.update(ia,ib+1,-k);
				cout << "Successfully cleaned up some rotten bananas!" << endl;
			}
			else {
				cout << "No rotten bananas were cleaned up..." << endl;
			}
		}
		else if (option == "3") {
			cout << "The delivery company wants to know how many bananas they have dropped!" << endl;
			cout << "The company sends an employee to count the number of bananas dropped." << endl;
			cout << "However, the employee is lazy, and only counts the bananas in some of the cities." << endl;
			cout << "In particular, the employee chooses two cities on the Badpath, A and B, and counts the bananas in all the cities between A and B on the Badpath." << endl;
			cout << "Input city A:" << endl;
			int a; cin >> a;
			if (a<0 || a>=v) {
				return die("Failed! That is not a city");
			}
			if (index[a]<0) {
				return die("Failed! That city is not on the Badpath");
			}
			cout << "Input city B:" << endl;
			int b; cin >> b;
			if (b<0 || b>=v) {
				return die("Failed! That is not a city");
			}
			if (index[b]<0) {
				return die("Failed! That city is not on the Badpath");
			}
			int ia = index[a];
			int ib = index[b];
			if (ia>ib) {
				int t = ia;
				ia = ib;
				ib = t;
			}
			ll rsum = tree.querySum(ia,ib+1);
			cout << "The employee counted " << rsum << " rotten bananas!" << endl;
		}
		else if (option == "4") {
			cout << "An angry citizen decided to count the number of bananas in some cities and write a bad review for the company!" << endl;
			cout << "In particular, he chose two cities on the Badpath, A and B, and counted the number of bananas in each city between A and B on the Badpath." << endl;
			cout << "His review will reference the number of rotten bananas in the city with the maxinum number of bananas, out of the ones he counted." << endl;
			cout << "Input city A:" << endl;
			int a; cin >> a;
			if (a<0 || a>=v) {
				return die("Failed! That is not a city");
			}
			if (index[a]<0) {
				return die("Failed! That city is not on the Badpath");
			}
			cout << "Input city B:" << endl;
			int b; cin >> b;
			if (b<0 || b>=v) {
				return die("Failed! That is not a city");
			}
			if (index[b]<0) {
				return die("Failed! That city is not on the Badpath");
			}
			int ia = index[a];
			int ib = index[b];
			if (ia>ib) {
				int t = ia;
				ia = ib;
				ib = t;
			}
			ll rmax = tree.queryMax(ia,ib+1);
			if (rmax > 0) {
				cout << "This is the angry citizen's review:" << endl;
				cout << "------------------------------------------" << endl;
				cout << "|Review for the Segfault Delivery Company" << endl;
				cout << "|By: ANGERY" << endl;
				cout << "|Rating: 0/5" << endl;
				cout << "|In some city, this company dropped" << endl;
				cout << "|" << rmax << " rotten bananas..." << endl;
				cout << "------------------------------------------" << endl;
				reputation -= rmax;
				cout << "Due to this review, the reputation of the company dropped by " << rmax << endl;
			}
			else {
				cout << "The citizen did not find any bananas in the cities he searched, so he did not write a review..."  << endl;
			}
		}
		else if (option == "5") {
			if (reputation >= 0) {
				return die("Failed! This option should only be selected when the company has negative reputation!");
			}
			cout << "The citizens of Segfault decided to shoot out all the tires on the delivery company's trucks!" <<  endl;
			cout << "The company was soon forced to shut down." << endl;
			break;
		}
		else {
			return die("Failed! That is not a valid option.");
		}
	}
}



















