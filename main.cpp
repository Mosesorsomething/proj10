#include <functional>
#include <iostream>
#include "json.hpp"
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

using json = nlohmann::json;

struct Point {
	int x, y;
};
template<typename T>
int nodecount(T *A, int size) {
	int c=0;
	for (int i = 0;i<size;i++) c+=A[i];
	return size-c;
}

template<typename P, auto log>
vector<int> BFS(vector<P> points, vector<bool> adj , int root, int goal) { // Breadth-First Search
	const int n = points.size();
	queue<int> Q;
	vector<bool> explored(n,false);
	vector<int> parent(n,-1);

	explored[root] = true;
	log(points[root]);
	Q.push(root);
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		if (v==goal) return parent; // return the parent vector, because we already know the goal and the parent vector is more useful
		for (int w=0;w<n;w++) if (adj[n*v+w]) { //shortest path?
			if (!explored[w]) {
				explored[w] = true;
				log(points[w]);
				parent[w] = v;
				Q.push(w);
			}
		}
		
	}
	return parent; // compiler stop crying
}

int main() {
	json j_arr;
	// input
	bool A[5][5]{
		1,1,1,1,1,
		1,0,0,0,1,
		1,1,0,1,1,
		1,0,0,1,1,
		1,1,1,1,1,
		};
	j_arr["arr"] = A;
	Point root{2,2};
	Point goal{1,3};
	j_arr["root"] = {root.x,root.y};
	j_arr["goal"] = {goal.x,goal.y};

	// preprocessing
	int n = nodecount((bool*)A, sizeof A);
	
	vector<Point> points;
	points.reserve(n);
	for (int i=0;i<extent_v<decltype(A),0>;i++) {
		for (int j=0;j<extent_v<decltype(A),1>;j++) {
			if (not A[i][j]) points.push_back(Point{i,j});}
	}
	int r = 0, g = 0;
	for (int i=0;i<n;i++) if (points[i].x == root.x and points[i].y == root.y) r = i;
	for (int i=0;i<n;i++) if (points[i].x == goal.x and points[i].y == goal.y) g = i;

	vector<bool> adj; // adjacency matrix
	adj.reserve(n*n);
	for (Point p1 : points) {
		for (Point p2 : points)
			adj.push_back(1==(abs(p1.x-p2.x) + abs(p1.y-p2.y)));
	}
	// use points,r,g,adj

	vector<int> BFSparent = BFS<Point, [](Point p){cout << p.x << " " << p.y << " visited!" << endl;}>(points, adj, r, g);
	j_arr["parent"] = BFSparent; //store parent array into JSON file.
	vector<int> revpath(1,g); // create reverse path
	{
		int current = g;
		while (BFSparent[current]!=-1) {
			revpath.push_back(BFSparent[current]);
			current = BFSparent[current];
		}
	}
	// print path
	cout << "Path:";
	for (int i=revpath.size()-1;i>=0;i--) {
		Point p = points[revpath[i]];
		cout << " ("<< p.x << "," << p.y << ")";
		j_arr["path"].push_back({p.x,p.y});
	}
	cout << endl;
	// show debug info
	for (Point p : points) cout << p.x << " " << p.y << endl; // list of points
	for (int i=0;i<n;i++) { // adjacency
		for (int j=0;j<n;j++)
			cout << " " << adj[n*i+j]; 
		cout << endl;
	}
	ofstream file("bfs.json");
	file << j_arr.dump(1);
}


// 10. Multi-Algorithm Pathfinding Visualizer (Graphs + DP/Greedy)
// **Level**: Advanced
// **Main topics**: Graph algorithms, greedy vs DP flavor, runtime analysis, algorithmic comparison
// **Formal project statement**
// Create a **pathfinding visualizer** on a 2D grid or maze that allows users to compare different pathfinding algorithms. The grid has:
//     - Free cells
//     - Blocked cells (obstacles)
//     - A start cell and a goal cell
// You must:
//     - Represent the grid as a graph (implicit or explicit adjacency).
//     - Implement at least **three pathfinding algorithms**, e.g.:
//         - Breadth-First Search (BFS) for unweighted shortest paths
//         - Dijkstra’s algorithm for weighted paths
//         - A* search with an admissible heuristic (e.g. Manhattan distance)
//     - Visually (or textually) show the **order in which cells are visited** and the final path.
//     - Compare their **theoretical time complexity** and **empirical performance** (nodes expanded, runtime) on different map types.
