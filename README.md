# rotten-bananas
CSCI 2270 final project

To run this program:
 - Download all the files, and use the following to compile: `g++ -std=c++11 -o baaad graph.cpp segtree.cpp bad.cpp`. Then run the file that is produced


In the country of Segfault, there are n cities, connected by m bidirectional roads. It is always possible to go from any one city to any other using these roads. 
Each road is owned by some person. None of the people owning roads like delivery trucks, so they do not allow delivery trucks onto the roads. 
A delivery company wants to open in the country. Since the road owners do not let the company use the roads, the company decides to buy some of the roads from the owners.
Each owner is willing to sell their road for some price. The company wants to spend the least amount of money possible on the roads such that their delivery trucks can travel from any city to any other city using the roads the company bought.

One sector of the delivery company is in charge of delivering rotten bananas from a particular town X to a particular town Y. Their truck will go from town X to town Y using the roads the company bought. 
The truck used for this trip always has a hole in it. As a result, each time this delivery is made, for two towns A and B on the route the truck takes, the truck will drop K rotten bananas in each town between town A and B in its route. 
Sometimes, the people in the cities will clean up rotten bananas the trucks dropped. When this happens, choose two towns A and B that have rotten bananas in them. Each town between A and B in the delivery truck's route will clean up Y bananas that were dropped in them. Y cannot exceed the number of bananas in the town between A and B with the minimum number of bananas (otherwise, that town will have negative bananas). 
Some other times, the people in the cities will count the number of bananas in them. When this happens, choose two cities A and B that have rotten bananas in them. Eacn town between A and B in the delivery truck's route will count the number of bananas in them, and somone in a town with the maximal number of bananas will write a bad review for the company. The company will lose a number of reputation points equal to the number of bananas in that person's city. The company starts with 0 reputation. 
Finally, some times the company wants to know how many bananas they dropped. Choose two cities A and B that contain rotten bananas. The company hires people to count the bananas in all the towns between A and B. 


Specifications:

The user will be prompted for n, the number of cities in the country. For convenience, the names of the cities will be 0, 1, 2, ..., n-1. 
Then the user will input m, the number of roads in the country. 
For each road, the user will be asked for the following:
 - The first city it connects
 - The second city it connects
 - The cost that the city owner is willing to sell the road at

Then, a graph will be constructed with the cities as nodes and the roads as weighted edges (with weight equal to the cost to buy). 
A DFS will be performed to ensure that each city can be reached from any other using the roads. If it is not possible, the program ends. 
Then, we will use Kruskal's algorithm to find the minimum spanning tree of this graph. The company will buy all the roads in this minimum spanning tree. The program will display all the edges in this minimum spanning tree, as well as the total cost. 


The user will then be asked for cities X and Y. The delivery company will be delivering rotten bananas from city X to city Y. 
The program will find the path on the minimum spanning tree that connects X and Y, and display this path. 

At this point, a lazy propogating segment tree will be created in order to perform further queries. The leaves of this tree are the cities between X and Y on the MST.

The user will then be given the following options:
1. A delivery truck drops rotten banans. The user will be asked for 2 cities (both must be on the MST path between X and Y), as well as a number K. Then, K rotten bananas will be dropped in each city between X and Y on the MST.
2. People decide to clean up bananas. The user will be asked for two cities A and B. The program will tell the user the minimum number of bananas in a town between A and B. Then, the user chooses an integer K that does not exceed this minimum. Each town between A and B will clean up K bananas. 
3. People count bananas. The user will be asked for two cities A and B. The program will tell the user the maximum number of bananas in the cities between A and B. Then, it will display the number of reputation points the company has after someone writes a bad review about them. 
4. The company counts bananas. The user chooses two cities A and B. The program tells the user the total number of bananas in all the cities between A and B. 
5. The company is forced to shut down because angry citizens are shooting the tires in their trucks. This option can only be selected when the company has negative reputation points. This will destroy the stored graph and segment tree, and exit the program. 

Let q be the number of times the user selects one of the above options. 
The complexity for the DFS to check for connectedness is O(n+m).
The complexity for Kruskal's algorithm is O(m log n)
The complexity of finding the path between two cities on the minimum spanning tree is O(n). The maximum length of this path is n. 
The complexity of creating a segment tree is O(n log n)
The complexity of each query (other than 5) is O(log n) due to the usage of a segment tree. The complexity of 5 is O(n log n). The complexity of doing all the queries other than 5 is O(q log n) since there are q-1 such queries. 
Adding these together, the complexity of the entire program is O((n+m+q) log n). 


Restriction: 2 <= n <= 1000000. 

If any user input is invalid, the program will terminate early. 

class segtree - public methods:
 - segtree
 - long long querySum(a,b)
 - long long queryMax(a,b)
 - long long queryMin(a,b)
 - long long at(c)
 - void update(a,b,k)
 - int size()
 - ~segtree
