```cpp
//	//| const	| worst	| best	|
/**/template<typename P, typename logger>	//| 	| 	| 	|
/**/vector<int> BFS(vector<P> points, vector<bool> adj, int root, int goal, logger log) { // Breadth-First Search	//| 	| 	| 	|
/**/    const int n = points.size();	//| c1	| 1	| 1	|
/**/    queue<int> Q;	//| c2	| 1	| 1	|
/**/    vector<bool> explored(n,false);	//| c3	| n	| n	|
/**/    vector<int> parent(n,-1);	//| c4	| n	| n	|
/**/	//| 	| 	| 	|
/**/    explored[root] = true;	//| c5	| 1	| 1	|
/**/    log(points[root]);	//| c6	| 1	| 1	|
/**/    Q.push(root);	//| c7	| 1	| 1	|
/**/    while (!Q.empty()) {	//| c8	| n+1	| 1	|
/**/        int v = Q.front();	//| c9	| n	| 1	|
/**/        Q.pop();	//| c10	| n	| 1	|
/**/        if (v==goal) return parent; // return the parent vector, because we already know the goal and the parent vector is more useful	//| c11	| n	| 1	|
/**/        for (int w=0;w<n;w++) if (adj[n*v+w]) { //shortest path?	//| c12	| n*(n+1)	| 0	|
/**/            if (!explored[w]) {	//| c13	| n*n	| 0	|
/**/                explored[w] = true;	//| c14	| n*n	| 0	|
/**/                log(points[w]);	//| c15	| n*n	| 0	|
/**/                parent[w] = v;	//| c16	| n*n	| 0	|
/**/                Q.push(w);	//| c17	| n*n	| 0	|
/**/            }	//| 	| 	| 	|
/**/        }	//| 	| 	| 	|
/**/    }	//| 	| 	| 	|
/**/    return parent; // compiler stop crying	//| c18	| 1	| 0	|
/**/}	//| 	| 	| 	|

// # worst
// c1(1)+c2(1)+c3(n)+c4(n)+c5(1)+c6(1)+c7(1)+c8(n+1)+c9(n)+c10(n)+c11(n)+c12(n*(n+1))+c13(n^2)+c14(n^2)+c15(n^2)+c16(n^2)+c17(n^2)+c18(1)
// =c1+c2+c3*n+c4*n+c5+c6+c7+c8*n+c8+c9*n+c10*n+c11*n+c12*n^2+c12*n+c13*n^2+c14*n^2+c15*n^2+c16*n^2+c17*n^2+c18
// ⇒θ(n^2)

// # best
// c1(1)+c2(1)+c3(n)+c4(n)+c5(1)+c6(1)+c7(1)+c8(1)+c9(1)+c10(1)+c11(1)+c12(0)+c13(0)+c14(0)+c15(0)+c16(0)+c17(0)+c18(0)
// =c1+c2+c3*n+c4*n+c5+c6+c7+c8+c9+c10+c11
// ⇒θ(n)


//	//| const	| worst	| best	|
/**/template <typename P,typename logger>	//| 	| 	| 	|
/**/pair<vector<int>,vector<int>> Dijkstra(vector<P> points, vector<bool> adj , int root, int goal, logger log) { // Dijkstra’s algorithm	//| 	| 	| 	|
/**/    const int n = points.size();	//| c1	| 1	| 1	|
/**/    using PQ = MinHeap<pair<int,int>>; // priority queue functions	//| 	| 	| 	|
/**/    vector<pair<int,int>> Q{}; // priority queue	//| c2	| 1	| 1	|
/**/    // we're using pair<distance,point> since it works like APL total array ordering, i.e. first compare distance (what we want) and then compare vector (doesn't matter)	//| 	| 	| 	|
/**/    vector<int> distance(n, INT_MAX); // pretend INT_MAX is infinity bc we're using ints	//| c3	| n	| n	|
/**/    vector<int> parent(n, -1); // -1 means no parent	//| c4	| n	| n	|
/**/    distance[root] = 0;	//| c5	| 1	| 1	|
/**/    PQ::insert(Q,{0,root});	//| c6	| 1	| 1	|
/**/    for (int i=0;i<n;i++) if (i!=root) PQ::insert(Q,{INT_MAX,i}); // insert all other nodes with matching distances	//| c7	| n	| n	|
/**/    while (!Q.empty()) {	//| c8	| n+1	| 1	|
/**/        int p1 = PQ::extract(Q).second;	//| c9	| n	| 1	|
/**/        log(points[p1]);	//| c10	| n	| 1	|
/**/        for (int p2=0;p2<n;p2++) if (adj[p1*n+p2]!=0) {	//| c11	| n*(n+1)	| 1	|
/**/            int ndist = distance[p1] == INT_MAX? INT_MAX: distance[p1] + adj[p1*n+p2]; // distance is always one in our case, but we still query adj just in case we need to switch from bool to int	//| c12	| n*n	| 1	|
/**/            if (ndist < distance[p2]) {	//| c13	| n*n	| 1	|
/**/                distance[p2] = ndist;	//| c14	| n*n	| 1	|
/**/                parent[p2] = p1;	//| c15	| n*n	| 1	|
/**/                if (p2 == goal) return {parent, distance};	//| c16	| n*n	| 1	|
/**/            }	//| 	| 	| 	|
/**/        }	//| 	| 	| 	|
/**/    }	//| 	| 	| 	|
/**/    return {parent, distance};	//| c17	| 1	| 0	|
/**/}	//| 	| 	| 	|

// # worst
// c1(1)+c2(1)+c3(n)+c4(n)+c5(1)+c6(1)+c7(n)+c8(n+1)+c9(n)+c10(n)+c11(n*(n+1))+c12(n^2)+c13(n^2)+c14(n^2)+c15(n^2)+c16(n^2)+c17(1)
// =c1+c2+c3*n+c4*n+c5+c6+c7*n+c8*n+c8+c9*n+c10*n+c11*n^2+c11*n+c12*n^2+c13*n^2+c14*n^2+c15*n^2+c16n^2+c17
// ⇒θ(n^2)

// # best
// c1(1)+c2(1)+c3(n)+c4(n)+c5(1)+c6(1)+c7(n)+c8(1)+c9(1)+c10(1)+c11(1)+c12(1)+c13(1)+c14(1)+c15(1)+c16(1)+c17(0)
// =c1+c2+c3*n+c4*n+c5+c6+c7*n+c8+c9+c10+c11+c12+c13+c14+c15+c16
// ⇒θ(n)

template <typename P>
auto manhattan_distance(P a, P b) {P r =(b-a); return abs(r.x)+abs(r.y);}

//	//| const	| worst	| best	|
/**/template <typename P, typename logger>	//| 	| 	| 	|
/**/tuple<vector<int>,vector<int>,vector<int>> AStar(vector<P> points, vector<bool> adj, int root, int goal, logger log) {	//| 	| 	| 	|
/**/    const int n = points.size();	//| c1	| 1	| 1	|
/**/    using PQ = MinHeap<pair<int,int>>; // priority queue functions	//| 	| 	| 	|
/**/    vector<pair<int,int>> Q{}; // priority queue	//| c2	| 1	| 1	|
/**/    // we're using pair<distance,point> since it works like APL total array ordering, i.e. first compare distance (what we want) and then compare vector (doesn't matter)	//| 	| 	| 	|
/**/    vector<int> gdist(n, INT_MAX); // pretend INT_MAX is infinity bc we're using ints	//| c3	| n	| n	|
/**/    vector<int> fdist(n, INT_MAX); // pretend INT_MAX is infinity bc we're using ints	//| c4	| n	| n	|
/**/    vector<int> parent(n, -1); // -1 means no parent	//| c5	| n	| n	|
/**/    gdist[root] = 0;	//| c6	| 1	| 1	|
/**/    fdist[root] = manhattan_distance(points[root], points[goal]);	//| c7	| 1	| 1	|
/**/    PQ::insert(Q,{fdist[root],root}); // should sync with fdist now	//| c8	| 1	| 1	|
/**/    for (int i=0;i<n;i++) if (i!=root) PQ::insert(Q,{INT_MAX,i}); // insert all other nodes with matching distances	//| c9	| n	| n	|
/**/    while (!Q.empty()) { // while not empty	//| c10	| n+1	| 1	|
/**/        int p1 = PQ::extract(Q).second;	//| c11	| n	| 1	|
/**/        if (p1 == goal) return {parent, gdist, fdist};	//| c12	| n	| 1	|
/**/        log(points[p1]);	//| c13	| n	| 0	|
/**/	//| 	| 	| 	|
/**/        for (int p2=0;p2<n;p2++) if (adj[p1*n+p2]!=0) {	//| c14	| n*(n+1)	| 0	|
/**/            int ndist = gdist[p1] == INT_MAX? INT_MAX: gdist[p1] + adj[p1*n+p2];	//| c15	| n*n	| 0	|
/**/            if (ndist < gdist[p2]) {adj[p1*n+p2];	//| c16	| n*n	| 0	|
/**/                parent[p2] = p1;	//| c17	| n*n	| 0	|
/**/                gdist[p2] = ndist;	//| c18	| n*n	| 0	|
/**/                fdist[p2] = ndist + manhattan_distance(points[p2],points[goal]);	//| c19	| n*n	| 0	|
/**/                if (PQ::find(Q, {fdist[p2],p2})==-1) PQ::insert(Q,{fdist[p2],p2}); // if not in the set, add it	//| c20	| n*n*log(n)	| 0	|
/**/            }	//| 	| 	| 	|
/**/        }	//| 	| 	| 	|
/**/    }	//| 	| 	| 	|
/**/    return {parent, gdist, fdist};	//| c21	| 1	| 0	|
/**/}	//| 	| 	| 	|

// # worst
// c1(1)+c2(1)+c3(n)+c4(n)+c5(n)+c6(1)+c7(1)+c8(1)+c9(n)+c10(n+1)+c11(n)+c12(n)+c13(n)+c14(n*(n+1))+c15(n^2)+c16(n^2)+c17(n^2)+c18(n^2)+c19(n^2)+c20(n^2*log(n))+c21(1)
// =c1+c2+c3*n+c4*n+c5*n+c6+c7+c8+c9*n+c10*n*+c10+c11*n+c12*n+c13*n+c14*n^2+c14*n+c15*n^2+c16*n^2+c17*n^2+c18*n^2+c19*n^2+c20*n^2*log(n)+c21
// ⇒θ(n^2*log(n))

// # best
// c1(1)+c2(1)+c3(n)+c4(n)+c5(n)+c6(1)+c7(1)+c8(1)+c9(n)+c10(1)+c11(1)+c12(1)+c13(0)+c14(0)+c15(0)+c16(0)+c17(0)+c18(0)+c19(0)+c20(0)+c21(0)
// =c1+c2+c3*n+c4*n+c5*n+c6+c7+c8+c9*n+c10+c11+c12
// ⇒θ(n)


```
