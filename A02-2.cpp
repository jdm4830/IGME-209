#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// P10 DFS and BFS on graph

#define MAXIMUM_SIZE 100

int adjacentMatrix[MAXIMUM_SIZE][MAXIMUM_SIZE] = { 0 }; // adjacent matrix used to save the graph
int size_node; // the number of nodes

// a road between two castles. The road is undirected, which means you can go either from castle1 to castle2 or castle2 to castle1
struct Road {
	int castle1;
	int castle2;
};

// build the graph
// n is the number of castles
// m is the number of roads
// roads is the array of Road
void BuildGraph(int n, int m, Road* roads) {
	// write your code below
	// Set the size of the graph
	size_node = n;

	// initialize the adjacent matrix with zeros
	for (int i = 0; i < MAXIMUM_SIZE; i++) {
		for (int j = 0; j < MAXIMUM_SIZE; j++) {
			adjacentMatrix[i][j] = 0;
		}
	}

	// populate the adjacent matrix with the edges of the graph
	for (int i = 0; i < m; i++) {
		adjacentMatrix[roads[i].castle1][roads[i].castle2] = 1;
		adjacentMatrix[roads[i].castle2][roads[i].castle1] = 1;
	}
	// write your code above
}

// print the path by backwward traverse
void PrintPath(int* path, int source, int destination) {
	if (source != destination)
		PrintPath(path, source, path[destination]);
	cout << destination << " ";
}

// n: n castles
// m: m roads between the castles
// roads: the roads between the castles, the size is m
// source: the source castle
// destination: the destination castle, we want to check if there is a path between the source and destination
// k: k possible plans to build the roads
// roads_plan: the possible plans to build the roads, the size is k, each plan is a road between two castles,
// roads_plan: the cost of each plan, the size is k
// you are free to define new functions and call them in Solution() if you need
void Solution(int n, int m, Road* roads, int source, int destination,
	int k, Road* roads_plan, int* cost_array) {

	BuildGraph(n, m, roads);

	// write your code below
	// 1. Check and print if there exists a path between source to destination
	// 2. If it exists, print the path
	// 3. If not, for the k plans, check and print if there exists a path after building the road
	// 4. Print the valid plan with the minimum cost
	// Check if there exists a path between the source and destination
	// Check if there exists a path between the source and destination
	
	bool isPathExist = false;
	stack<int> s;
	queue<int> q;
	bool visited[MAXIMUM_SIZE] = { false };
	int path[MAXIMUM_SIZE] = { -1 };

	q.push(source);
	visited[source] = true;

	while (!q.empty()) {
		int current = q.front();
		q.pop();

		if (current == destination) {
			isPathExist = true;
			PrintPath(path, source, destination);
			break;
		}

		for (int i = 0; i < size_node; i++) {
			if (adjacentMatrix[current][i] == 1 && !visited[i]) {
				visited[i] = true;
				path[i] = current;
				q.push(i);
			}
		}
	}

	// path between source and destination
	if (!isPathExist) {
		cout << "No path found from " << source << " to " << destination << "" << endl;
	}
	else {
		cout << "Path from " << source << " to " << destination << " is ";
		PrintPath(path, source, destination);
		cout << endl;
	}

	// path for each plan
	int min_cost = INT_MAX;
	int best_plan = -1;

	for (int i = 0; i < k; i++) {
		// build the new road
		adjacentMatrix[roads_plan[i].castle1][roads_plan[i].castle2] = 1;
		adjacentMatrix[roads_plan[i].castle2][roads_plan[i].castle1] = 1;

		//path between the source and destination after building the new road
		bool isPathExistAfterBuilding = false;
		stack<int> s;
		queue<int> q;
		bool visited[MAXIMUM_SIZE] = { false };
		int path[MAXIMUM_SIZE] = { -1 };

		q.push(source);
		visited[source] = true;

		while (!q.empty()) {
			int current = q.front();
			q.pop();

			if (current == destination) {
				isPathExistAfterBuilding = true;
				PrintPath(path, source, destination);
				break;
			}

			for (int j = 0; j < size_node; j++) {
				if (adjacentMatrix[current][j] == 1 && !visited[j]) {
					visited[j] = true;
					path[j] = current;
					q.push(j);
				}
			}
		}

		//print path that exists
		if (isPathExistAfterBuilding) {
			cout << "If build a road between " << roads_plan[i].castle1 << " and " << roads_plan[i].castle2
				<< " with cost = " << cost_array[i] << ": Path from " << source << " to " << destination << " is ";
			PrintPath(path, source, destination);
			cout << endl;

			//Min cost
			if (cost_array[i] < min_cost) {
				min_cost = cost_array[i];
				best_plan = i;
			}
		}
		//Didn't finish
		else {
			//cout << "If build a road between "
		}
	}
	// write your code above
}

int main() {
	// test case
	int n = 5; // we have 5 castles
	int m = 3; // we have 3 roads
	Road roads[3] = { {0, 1}, {0, 2}, {3, 4} }; // the 3 roads are (0,1), (0,2), and (3,4)

	int source = 0; // we start from castle 0
	int destination = 4; // the destination is castle 4

	int k = 3; // we have 3 possible plans
	Road roads_plan[3] = { {0, 3}, {1, 2}, {2, 4} }; // the 3 plans are build a new road between (0, 3), (1, 2), and (2, 4)
	int cost_array[3] = { 10, 2, 5 }; // the cost of 3 plans are 10, 2, and 5

	Solution(n, m, roads, source, destination, k, roads_plan, cost_array);

	return 0;
}
