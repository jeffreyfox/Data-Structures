#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <climits>
#include <cassert>
#include <algorithm>
#include "unionfind.h"

using namespace std;

/// vertex structure, not all members are used
struct Vertex {
	int index; // a unique id in graph
	int parent; // parent index in the BFS/DFS tree
	int dist; // distance from the source
	char tag; // tag for the state of the vertex. 'w': white, 'g' grey, 'b' black
	int d, f; //discover and finish time of each vertex
	bool visited; //whether vertex has been visited
	Vertex() : index(-1), parent(-1), dist(INT_MAX), tag('w'), d(0), f(0), visited(false) {}
	Vertex(int i) : index(i), parent(-1), dist(INT_MAX), tag('w'), d(0), f(0), visited(false) {}
};

ostream& operator<<(ostream& os, const Vertex& v) {
	//	os << "(" << v.index << ", (" << v.d << " " << v.f << ")) ";
	os << "(" << v.index << " " << v.dist << ") ";
	return os;
}

struct Edge {
	int src, des, weight;
	Edge() : src(-1), des(-1), weight(-1) {}
	Edge(int s, int d, int w) : src(s), des(d), weight(w) {}
};

ostream& operator<<(ostream& os, const Edge& e) {
	os << "(" << e.src << "-" << e.des << ", " << e.weight << "))";
	return os;
}

bool operator<(const Edge& e1, const Edge& e2) {
	return e1.weight < e2.weight;
}

// element in the adajcency list
struct AdjElem {
	int vidx; //index of the destination vertex
	int weight; //weight of the edge connecting source and destination
	AdjElem() : vidx(-1), weight(0) {}
	AdjElem(int v, int w) : vidx(v), weight(w) {}
};

ostream& operator<<(ostream& os, const AdjElem& ae) {
	//os << "(" << ae.vidx << " " << ae.weight << ") ";
	os << "(" << ae.vidx << ") ";
	return os;
}

enum GraphType { UNDEF=-1, UNDIRECTED, DIRECTED };

//adjacency list form of a graph
class GraphAL { 
public:

	/// constructor, default undirected graph
	GraphAL(int VV, GraphType t = UNDIRECTED);

	/// add an edge to the graph (input: src, des, weight)
	void addEdge(int i, int j, int w = 1);

	/// get the transpose of the graph
	GraphAL transpose();

	/// Bread-first search of the graph from source vertex v
	vector<int> BFS(int v);

	/// Depth-first search of the graph visiting all vertices
	vector<int> DFS(bool classify_edges=false); //recursive
	vector<int> DFS2(); //iterative (stack)

	/// Return whether a directed graph is cyclic or not using DFS search
	bool IsCyclic();

	/// Return a topological sort of the graph stored as vector of vertex indices
	vector<int> TopoSort();

	/// Return all the strongly connected components of a directed graph
	vector<vector<int> > SCC();

	/// Find all articulation points of an undirected graph in O(E), return vector of boolean
	vector<bool> AP();

	/// Find all bridges of an undirected graph in O(E), return vector of edges
	vector<Edge> Bridge();

	/// find mininum spanning tree (Krukal, Prim)
	vector<Edge> MSTKruskal();
	vector<Edge> MSTPrim();

	/// Bellman-Ford algorithm for the single-source shortest-path problem in O(VE)
	/// Returns a boolean indicating whether there is a negative-weight cycle reachable from source
	bool BellmanFord(int src);

	/// Algorithm for the Single-source shortest path in directed acyclic grpahs in O(V+E)
	void SPdag(int src);

	/// Dijkstra's algorithm for the single-source shorted-path problem on graph without negative edges
	void Dijkstra(int src);

	/// Count number of paths from vertex u to v (using depth-first search)
	int countPaths(int u, int v) { return countPathsUtil(u, v); }

	/// Find number of paths from vertex u to v (using depth-first search)
	vector<vector<int> > findPaths(int u, int v);

	/// whether the graph can be colored with 2 colors
	bool twoColor(int v);

	/// printVertices
	void printVertices() { 
		for(int v = 0; v < V; ++v) cout << vs[v] << " ";
		cout << endl;
	}

	/// print path from src to v (using parent attribute)
	void printPath(int src, int v);

	friend ostream& operator<<(ostream& os, const GraphAL& g);

protected:
	///Data members
	GraphType type; //type of graph (directed or undirected)
	int V; //number of vertices in the graph
	vector<Vertex> vs; //list of all vertices
	vector<list<AdjElem> > adj; //adjacency list of each vertex

private:
	/// Utility function for depth first search, increment time for stamping
	void DFSUtil(int u, int& time, vector<int>& dfs, bool classify_edges = false); //recursive
	void DFSUtil2(int u, int& time, vector<int>& dfs); //iterative

	/// Utility function to determine is a directed graph is cyclic or not
	bool IsCyclicUtil(int u);

	/// Utility function for topological sorting, return stack of topo sort
	void TopoSortUtil(int v, vector<int>& ts);

	/// Utility funciton for articulation point searching
	void APUtil(int v, int &time, vector<int>& low, vector<bool> &ap);

	/// Utility funciton for bridge searching
	void BridgeUtil(int v, int &time, vector<int>& low, vector<Edge> &bridge);

	/// Function to relax on edge [u,v]
	void Relax(int u, int v, int wt);

	/// Utility functions for path-finding between two vertices
	int countPathsUtil(int u, int v);
	void findPathsUtil(int u, int v, const vector<int> &path, vector<vector<int> >& ret);
};

GraphAL::GraphAL(int VV, GraphType t) : V(VV), type(t) { 
	vs.resize(V);
	for(int k = 0; k < V; ++k) vs[k] = k;
	adj.resize(V); 
}

GraphAL GraphAL::transpose() {
	assert(type == DIRECTED); //only directed graph has transpose
	GraphAL T(V, type);
	for(int v = 0; v < V; ++v)
		for(list<AdjElem>::const_iterator it = adj[v].begin(); it != adj[v].end(); ++it)
			T.adj[it->vidx].push_back(AdjElem(v, it->weight));
	return T;
}

void GraphAL::addEdge(int u, int v, int w) {
	adj[u].push_back(AdjElem(v, w));
	if(type == UNDIRECTED) adj[v].push_back(AdjElem(u, w)); 
}

vector<int> GraphAL::BFS(int v) {
	vector<int> bfs;

	//reset all vertices
	for(int u = 0; u < V; ++u) {
		vs[u].tag = 'w'; vs[u].parent = -1; vs[u].d = vs[u].f = 0;
	}

	vs[v].tag = 'g'; //v tag as grey
	vs[v].dist = 0;
	vs[v].parent = -1;

	deque<int> q;
	q.push_back(v);
	while(!q.empty()) {
		v = q.front(); q.pop_front();
		bfs.push_back(v);
		for(list<AdjElem>::const_iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
			int u = it->vidx;
			if(vs[u].tag == 'w') { //only process white (undiscovered) vertices
				vs[u].tag = 'g'; //first tag as grey
				vs[u].dist = vs[v].dist + 1;
				vs[u].parent = v; //parent index
				q.push_back(u);
			}
		}
		vs[v].tag = 'b'; //finished discovering all v's neighbors, set as black
	}
	return bfs;
}

vector<int> GraphAL::DFS(bool classify_edges) 
{
	//reset all vertices
	for(int u = 0; u < V; ++u) {
		vs[u].tag = 'w'; vs[u].parent = -1; vs[u].d = vs[u].f = 0;
	}

	vector<int> dfs;
	int time = 0;
	for(int u = 0; u < V; ++u) {
		if(vs[u].tag == 'w') DFSUtil(u, time, dfs, classify_edges); //only process white vertices
	}
	return dfs;
}

vector<int> GraphAL::DFS2() 
{
	//reset all vertices
	for(int u = 0; u < V; ++u) {
		vs[u].tag = 'w'; vs[u].parent = -1; vs[u].d = vs[u].f = 0;
	}

	vector<int> dfs;
	int time = 0;
	for(int u = 0; u < V; ++u) {
		if(vs[u].tag == 'w') DFSUtil2(u, time, dfs); //only process white vertices
	}
	return dfs;
}

void GraphAL::DFSUtil(int u, int& time, vector<int>& dfs, bool classify_edges) 
{
	vs[u].d = ++time; vs[u].tag = 'g';
	dfs.push_back(u);
	for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
		int v = it->vidx;
		if(vs[v].tag == 'w') {
			if(classify_edges) cout << "Edge ("<<u<<", "<<v<<") is tree edge" << endl;
			vs[v].parent = u;
			DFSUtil(v, time, dfs, classify_edges);
		} else if(classify_edges) {
			if(vs[v].tag == 'g') cout << "Edge ("<<u<<", "<<v<<") is back edge" << endl;
			else if(vs[u].d < vs[v].d) cout << "Edge ("<<u<<", "<<v<<") is forward edge" << endl;
			else cout << "Edge ("<<u<<", "<<v<<") is cross edge" << endl;
		}
	}
	vs[u].tag = 'b';
	vs[u].f = ++time;
}

void GraphAL::DFSUtil2(int u, int& time, vector<int>& dfs) 
{
	deque<int> s; //stack
	s.push_back(u);
	while(!s.empty()) {
		u = s.back(); s.pop_back(); //u is always grey
		if(vs[u].tag == 'w') { //discovered
			vs[u].tag = 'g'; vs[u].d = ++time;
			s.push_back(u); //push back to stack
			dfs.push_back(u); //push to dfs array
			//process u's neighbors in reverse order of adajency list, just to be consistent with recursive version
			for(list<AdjElem>::const_reverse_iterator it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
				int v = it->vidx;
				if(vs[v].tag == 'w') {
					vs[v].parent = u;
					s.push_back(v); //push to stack
				}
			}
		} else if(vs[u].tag == 'g') { //grey, already found, just stamp finish time
			vs[u].tag = 'b'; vs[u].f = ++time;
		} else { //it is possible to have a black node popped
			//do nothing
		}
	}
}

bool GraphAL::IsCyclic() 
{
	//reset all vertices
	for(int u = 0; u < V; ++u) {
		vs[u].tag = 'w'; vs[u].parent = -1; vs[u].d = vs[u].f = 0;
	}

	for(int u = 0; u < V; ++u) {
		if(vs[u].tag == 'w' && IsCyclicUtil(u)) return true; //only process white vertices
	}
	return false;
}

bool GraphAL::IsCyclicUtil(int u) 
{
	vs[u].tag = 'g';
	for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
		int v = it->vidx;
		if(vs[v].tag == 'w' && IsCyclicUtil(v)) return true;
		else if(vs[v].tag == 'g') return true;
	}
	vs[u].tag = 'b';
	return false;
}

vector<int> GraphAL::TopoSort() 
{
	for(int v = 0; v < V; ++v) vs[v].tag = 'w';

	vector<int> ts;
	for(int v = 0; v < V; ++v)
		if(vs[v].tag == 'w') TopoSortUtil(v, ts);

	return ts;
}

void GraphAL::TopoSortUtil(int v, vector<int>& ts)
{
	vs[v].tag = 'g'; //first discovered, color as grey
	for(list<AdjElem>::const_iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
		int u = it->vidx;
		if(vs[u].tag == 'w') {
			vs[u].parent = v;
			TopoSortUtil(u, ts);
		} 
	}
	vs[v].tag = 'b'; //finish, color as black
	ts.insert(ts.begin(), v); //insert at head (stack)
}

vector<vector<int> > GraphAL::SCC()
{
	vector<vector<int> > scc;
	for(int v = 0; v < V; ++v) vs[v].tag = 'w';

	vector<int> ts; //step 1, DFS of graph, get topo sort
	for(int v = 0; v < V; ++v)
		if(vs[v].tag == 'w') TopoSortUtil(v, ts);

	GraphAL gT = transpose(); //step 2, get transpose of graph gT

	int time = 0;
	vector<int> dfs;//step 3, dfs of gT in order of ts
	for(vector<int>::const_iterator it = ts.begin(); it != ts.end(); ++it) {
		if(gT.vs[*it].tag == 'w') { //dfs of gT!
			dfs.clear();
			gT.DFSUtil(*it, time, dfs); //dfs of gT!
			scc.push_back(dfs);
		}
	}
	return scc;
}

vector<bool> GraphAL::AP() 
{
	//reset all vertices
	for(int u = 0; u < V; ++u) {
		vs[u].tag = 'w'; vs[u].parent = -1; vs[u].d = vs[u].f = 0;
	}

	//ap[V] is true if v is articulation point
	vector<bool> ap(V, false);
	//low[v] is the minimum discovery time of all vertices reachable from v and v's descedants 
	//(except from edge [v, v.parent]).
	vector<int> low(V, -1);
	int time = 0;
	for(int u = 0; u < V; ++u) {
		if(vs[u].tag == 'w') APUtil(u, time, low, ap); //only process white (unvisited) vertices
	}
	return ap;
}

void GraphAL::APUtil(int u, int &time, vector<int>& low, vector<bool> &ap)
{
	//first time visited, init low and d
	vs[u].d = low[u] = ++time;
	vs[u].tag = 'b'; //color as black (visited)!
	int children = 0; //children for the DFS tree
	for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
		int v = it->vidx; //v is u's child
		if(vs[v].tag == 'w') { //not visited before
			vs[v].parent = u;
			children ++; //only increment when v is not visited before
			APUtil(v, time, low, ap);//recursively call for u's child v

			low[u] = min(low[u], low[v]); //this is where low[u] becomes smaller
			//if u is not root and has a child v that doesn't have any back edge to u's ancestors, then u is art. point
			//we check the minimum reachable vertex from v, low[v], and see if it is >= the discovery time of u, vs[u].d
			//if equal that means there's a back edge to u, but not above, still u is articulation point.
			if(vs[u].parent != -1 && low[v] >= vs[u].d) ap[u] = true;

		} else if(vs[u].parent != v) { //visited before, back edge, excluding edge [u, u.p] case
			low[u] = min(low[u], vs[v].d); //this is where low[u] becomes smaller
		}
		//finally, if u 's root and has >1 children, it is articulation point
		if(vs[u].parent == -1 && children > 1)  ap[u] = true;
	}
}

vector<Edge> GraphAL::Bridge() 
{
	//reset all vertices
	for(int u = 0; u < V; ++u) {
		vs[u].tag = 'w'; vs[u].parent = -1; vs[u].d = vs[u].f = 0;
	}

	//ap[V] is true if v is articulation point
	vector<Edge> bridge;
	//low[v] is the minimum discovery time of all vertices reachable from v and v's descedants 
	//(except from edge [v, v.parent]).
	vector<int> low(V, -1);
	int time = 0;
	for(int u = 0; u < V; ++u) {
		if(vs[u].tag == 'w') BridgeUtil(u, time, low, bridge); //only process white (unvisited) vertices
	}
	return bridge;
}

void GraphAL::BridgeUtil(int u, int &time, vector<int>& low, vector<Edge> &bridge)
{
	//first time visited, init low and d
	vs[u].d = low[u] = ++time;
	vs[u].tag = 'b'; //color as black (visited)!
	for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
		int v = it->vidx; //v is u's child
		if(vs[v].tag == 'w') { //not visited before
			vs[v].parent = u;
			BridgeUtil(v, time, low, bridge);//recursively call for u's child v

			low[u] = min(low[u], low[v]); //this is where low[u] becomes smaller

			//if u has a child v that doesn't have any back edge to u or u's ancestors, then u is art. point
			//we check the minimum reachable vertex from v, low[v], and see if it is > the discovery time of u, vs[u].d
			//if equal that means there's a back edge to u (not thru [v,u]), then u-v is not bridge
			if(low[v] > vs[u].d) bridge.push_back(Edge(u, v, 1));

		} else if(vs[u].parent != v) { //visited before, back edge, excluding edge [u, u.p] case
			low[u] = min(low[u], vs[v].d); //this is where low[u] becomes smaller
		}
	}
}

vector<Edge> GraphAL::MSTKruskal() {
	assert(type == UNDIRECTED);
	vector<Edge> edges, MSTedges;
	for(int u = 0; u < V; ++u) {
		for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
			int v = it->vidx;
			if(u < v) edges.push_back(Edge(u, v, it->weight));
		}
	}
	sort(edges.begin(), edges.end());

	UnionFind uf(edges.size());
	for(unsigned k = 0; k < edges.size(); ++k) {
		int p1 = edges[k].src, p2 = edges[k].des;
		if(uf.Find(p1) != uf.Find(p2)) {
			MSTedges.push_back(edges[k]);
			uf.Union(p1, p2);
		}
	}
	return MSTedges;
}

vector<Edge> GraphAL::MSTPrim()
{
	assert(type == UNDIRECTED);
	for(int u = 0; u < V; ++u) {
		vs[u].dist = INT_MAX; vs[u].parent = -1; vs[u].tag = 'w';
	}
	vs[0].dist = 0;
	for(int t = 0; t < V; ++t) { //do V times (first time just pick 0)
		//find the one with smallest distance
		int u = 0, mind = INT_MAX;
		for(int k = 0; k < V; ++k) {
			if(vs[k].tag == 'w' && vs[k].dist < mind) {
				mind = vs[k].dist; u = k; 
			}
		}
		vs[u].tag = 'b'; //u is part of MST, mark as black
		//only update unselected (white) neighbors
		for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
			int v = it->vidx;
			if(vs[v].tag == 'w' && vs[v].dist > it->weight) { 
				vs[v].dist = it->weight; vs[v].parent = u;
			}
		}
	}
	//now prepare vector<Edge> from parent attribute
	vector<Edge> MSTedges;
	for(int v = 0; v < V; ++v) {
		int u = vs[v].parent;
		if(u != -1) {
			int weight = -1;
			for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
				if(it->vidx == v) weight = it->weight;
			}
			MSTedges.push_back(Edge(u, v, weight));
		}
	}
	return MSTedges;
}

bool GraphAL::BellmanFord(int src) {
	for(int v = 0; v < V; ++v) {
		vs[v].dist = INT_MAX; vs[v].parent = -1;
	}
	vs[src].dist = 0;

	for(int i = 0; i < V-1; ++i) { //perform global relaxation for V-1 times
		for(int u = 0; u < V; ++u) {	//relax each edge in G	
			for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
				Relax(u, it->vidx, it->weight);
			}
		}
	}

	//check negative cycles
	for(int u = 0; u < V; ++u) {	//relax each edge in G	
		for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
			int v = it->vidx;
			if(vs[v].dist > vs[u].dist + it->weight) return false;
		}
	}

	return true;
}

void GraphAL::SPdag(int src) {
	assert(!IsCyclic());
	for(int v = 0; v < V; ++v) {
		vs[v].dist = INT_MAX; vs[v].parent = -1;
	}
	vs[src].dist = 0;

	//topological sort order
	vector<int> ts = TopoSort();

	for(unsigned k = 0; k < ts.size(); ++k) { //relax edge in topological order
		int u = ts[k];
		for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
			Relax(u, it->vidx, it->weight);
		}
	}
}

void GraphAL::Dijkstra(int src) {
	for(int v = 0; v < V; ++v) {
		vs[v].dist = INT_MAX; vs[v].parent = -1;
	}
	vs[src].dist = 0;

	for(int t = 0; t < V; ++t) { //do V times (first time just pick src)
		//find the one with smallest distance
		int u = 0, mind = INT_MAX;
		for(int k = 0; k < V; ++k) {
			if(vs[k].tag == 'w' && vs[k].dist < mind) {
				mind = vs[k].dist; u = k; 
			}
		}
		vs[u].tag = 'b'; //u is part of shorted-path tree, mark as black
		//only update unselected (white) neighbors
		for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
			int v = it->vidx;
			Relax(u, v, it->weight);
		}
	}
}

void GraphAL::Relax(int u, int v, int wt) {
	// only update when there exist a shorter path to v via u
	// need to check u's dist value to avoid integer overflow. If vs[u].dist = inf, no need to relax
	if(vs[u].dist != INT_MAX && vs[v].dist > vs[u].dist + wt) {
		vs[v].dist = vs[u].dist + wt;
		vs[v].parent = u;
	}
}

vector<vector<int> > GraphAL::findPaths(int u, int v) {
	vector<int> path;
	vector<vector<int> > ret;
	findPathsUtil(u, v, path, ret);
	return ret;
}

int GraphAL::countPathsUtil(int u, int v)
{
	if(u == v) return 1; 
	int n = 0;
	for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
		n += countPathsUtil(it->vidx, v);
	}
	return n;
}

void GraphAL::findPathsUtil(int u, int v, const vector<int> &path, vector<vector<int> >& ret)
{
	vector<int> newpath(path);
	newpath.push_back(u);
	if(u == v) {
		ret.push_back(newpath);
		return;
	}
	for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
		int w = it->vidx;
		findPathsUtil(w, v, newpath, ret);
	}
}

void GraphAL::printPath(int src, int v) {
	if(v == src) cout << v << " ";
	else if(vs[v].parent == -1) cout << "no path from " << src << " to " << v << " exists";
	else { printPath(src, vs[v].parent); cout << v << " ";	}
}

//color it as 'red' or 'blue'
bool GraphAL::twoColor(int v) {
	vs[v].tag = 'r';
	deque<int> q;
	q.push_back(v);
	while(!q.empty()) {
		v = q.front(); q.pop_front();
		//push uncolored neighbor nodes in queue
		for(list<AdjElem>::const_iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
			int u = it->vidx;
			if(vs[u].tag == 'w') { 
				vs[u].tag = vs[v].tag == 'r' ? 'b' : 'r';
				q.push_back(u);
			} else if(vs[u].tag != (vs[v].tag == 'r' ? 'b' : 'r')) {  //already colored, check for conflict
				cout << " Failed to 2-color graph " << endl;
				return false;
			}
		}
	}
	return true;
}

ostream& operator<<(ostream& os, const GraphAL& g) {
	os << "Number of vertices : " << g.V << endl;
	for(int k = 0; k < g.V; ++k) {
		os << k << ": ";
		for(list<AdjElem>::const_iterator it = g.adj[k].begin(); it != g.adj[k].end(); ++it) {
			os << *it;
		}
		os << endl;
	}
	return os;
}

class GraphAM { //adjacency list form
public:

	GraphAM(int VV, GraphType t = UNDIRECTED) : V(VV), type(t) { adj.resize(V, vector<int>(V, 0)); };
	void addEdge(int i, int j, int w = 1) {
		adj[i][j] = w;
		if(type == UNDIRECTED) adj[j][i] = w;
	}
	friend ostream& operator<<(ostream& os, const GraphAM& g);

protected:
	GraphType type;
	int V;
	vector<vector<int> > adj;
};

ostream& operator<<(ostream& os, const GraphAM& g) {
	os << "Number of vertices : " << g.V << endl;
	for(int k = 0; k < g.V; ++k) {
		os << k << ": ";
		for(int l = 0; l < g.V; ++l) {
			if(g.adj[k][l]) os << "(" << l << " " << g.adj[k][l] << ") ";
		}
		os << endl;
	}
	return os;
}

#endif
