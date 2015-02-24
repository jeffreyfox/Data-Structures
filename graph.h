#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <climits>
#include <cassert>

using namespace std;

/// vertex structure, not all members are used
struct Vertex {
	int index; // a unique id in graph
	int parent; // parent index in the BFS/DFS tree
	int dist; // distance from the source in BFS search
	char tag; // tag for the state of the vertex. 'w': white, 'g' grey, 'b' black
	int d, f; //discover and finish time of each vertex
	bool visited; //whether vertex has been visited
	Vertex() : index(-1), parent(-1), dist(INT_MAX), tag('w'), d(0), f(0), visited(false) {}
	Vertex(int i) : index(i), parent(-1), dist(INT_MAX), tag('w'), d(0), f(0), visited(false) {}
};

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
	vector<int> DFS(bool classify_edges=false);
	
	/// Return a topological sort of the graph stored as vector of vertex indices
	vector<int> TopoSort();

	/// Return all the strongly connected components of a directed graph
	vector<vector<int> > findSCC();

	/// Count number of paths from vertex u to v (using depth-first search)
	int countPaths(int u, int v) { return countPathsUtil(u, v); }

	/// Find number of paths from vertex u to v (using depth-first search)
	vector<vector<int> > findPaths(int u, int v);

	/// whether the graph can be colored with 2 colors
	bool twoColor(int v);

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
	//Utility function for depth first search, increment time for stamping
	void DFSUtil(int u, int& time, vector<int>& ret, bool classify_edges = false);

	//Utility function for topological sorting, return stack of topo sort
	void TopoSortUtil(int v, vector<int>& ts);

	//Utility functions for path-finding between two vertices
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
	vector<int> ret;
	
	//reset all vertices
	for(int u = 0; u < V; ++u) {
		vs[u].tag = 'w'; //set all nodes as white (undiscovered)
		vs[u].parent = 0; 
	}

	vs[v].tag = 'g'; //v tag as grey
	vs[v].dist = 0;
	vs[v].parent = -1;

	deque<int> q;
	q.push_back(v);
	while(!q.empty()) {
		v = q.front(); q.pop_front();
		ret.push_back(v);
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
	return ret;
}

vector<int> GraphAL::DFS(bool classify_edges) 
{
	//reset all vertices
	for(int u = 0; u < V; ++u) {
		vs[u].tag = 'w'; //set all nodes as white (undiscovered)
		vs[u].parent = 0; 
	}
	
	vector<int> ret;
	int time = 0;
	for(int u = 0; u < V; ++u) {
		if(vs[u].tag == 'w') DFSUtil(u, time, ret, classify_edges); //only process white vertices
	}
	return ret;
}

void GraphAL::DFSUtil(int u, int& time, vector<int>& ret, bool classify_edges) 
{
	vs[u].d = ++time;
	vs[u].tag = 'g';
	ret.push_back(u);
	
	for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
		int v = it->vidx;
		if(vs[v].tag == 'w') {
			if(classify_edges) cout << "Edge ("<<u<<", "<<v<<") is tree edge" << endl;
			vs[v].parent = u;
			DFSUtil(v, time, ret, classify_edges);
		} else if(classify_edges) {
			if(vs[v].tag == 'g') cout << "Edge ("<<u<<", "<<v<<") is back edge" << endl;
			else if(vs[u].d < vs[v].d) cout << "Edge ("<<u<<", "<<v<<") is forward edge" << endl;
			else cout << "Edge ("<<u<<", "<<v<<") is cross edge" << endl;
		}
	}
	vs[u].tag = 'b';
	vs[u].f = ++time;
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

vector<vector<int> > GraphAL::findSCC()
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
		if(gT.vs[*it].tag == 'w') {
			dfs.clear();
			DFSUtil(*it, time, dfs);
			scc.push_back(dfs);
		}
	}
	return scc;
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
