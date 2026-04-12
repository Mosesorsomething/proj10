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
void to_json(nlohmann::json& j, const Point& p) {
	j = json{{"x", p.x}, {"y", p.y}};
}
void from_json(const nlohmann::json& j, Point& p) {
	j.at("x").get_to(p.x);
	j.at("y").get_to(p.y);
}
template<typename T>
int nodecount(T *A, int size) {
	int c=0;
	for (int i = 0;i<size;i++) c+=A[i];
	return size-c;
}

template<typename P, typename logger>
vector<int> BFS(vector<P> points, vector<bool> adj , int root, int goal, logger log) { // Breadth-First Search
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

template <typename P,typename logger>
pair<vector<int>,vector<int>> Dijkstra(vector<P> points, vector<bool> adj , int root, int goal, logger log) { // Dijkstra’s algorithm
	const int n = points.size();
	vector<bool> explored(n,false); // consider all points, still debating whether queue or bool vector
	vector<int> distance(n, INT_MAX); // pretend INT_MAX is infinity bc we're using ints
	vector<int> parent(n, -1); // -1 means no parent
	// for (int i=0;i<n;i++) explored[i] =; // consider all points
	distance[root] = 0;
	while (!reduce(explored.begin(), explored.end(), true, logical_and<>())) {
		int p1 = 0;
		for (int i=0;i<n;i++) // find min unexplored point, this forces to break the queue rules, since we need to peek at every element without popping, maybe use another temp queue, or bool vector?
			if (!explored[i] && distance[p1] > distance[i])
				p1 = i;
		explored[p1] = true;
		log(points[p1]);
		for (int p2=0;p2<n;p2++) if (adj[p1*n+p2]!=0) {
			int ndist = distance[p1] == INT_MAX? INT_MAX: distance[p1] + adj[p1*n+p2]; // distance is always one in our case, but we still query adj just in case we need to switch from bool to int
			if (ndist < distance[p2]) {
				distance[p2] = ndist;
				parent[p2] = p1;
				if (p2 == goal) return {parent, distance};
			}
		}
	}
	return {parent, distance};
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
	vector<Point> visited{};
	vector<int> BFSparent = BFS(points, adj, r, g, [&visited](Point p) {cout << p.x << " " << p.y << " visited!" << endl;visited.push_back(p);});
	j_arr["parent"] = BFSparent; //store parent array into JSON file.
	j_arr["log"] = visited;
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
	file.close();

	j_arr.clear(); visited.clear();
	vector<int> Dparent, Ddistance;
	tie(Dparent,Ddistance) = Dijkstra(points, adj, r, g, [&visited](Point p) {cout << p.x << " " << p.y << " visited!" << endl;visited.push_back(p);});
	j_arr["parent"] = Dparent; // store parent array into JSON file
	j_arr["distance"] = Ddistance; // store distance array into JSON file, INT_MAX is infinity unfortunately
	j_arr["log"] = visited;
	// print path
	cout << "Path:";
	vector<int> S{};
	for (int u = g; Dparent[u] != -1; u=Dparent[u]) S.push_back(u);
	S.push_back(r);
	for (int u : S) {
		Point p = points[u];
		cout << " ("<< p.x << "," << p.y << ")";
		j_arr["path"].push_back({p.x,p.y});
	}
	cout << endl;
	j_arr["arr"] = A;
	j_arr["root"] = {root.x,root.y};
	j_arr["goal"] = {goal.x,goal.y};
	file.open("dijkstra.json");
	file << j_arr.dump(1);
	file.close();
}