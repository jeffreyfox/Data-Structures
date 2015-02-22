#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <climits>
#include <cassert>

using namespace std;

struct Vertex {
	int index;
	int parent; //parent index in the BFS tree
	int dist; //distance from the source in BFS search
	char tag; //w means undiscovered, 'g' means neighbors are to be processed, 'b' means finished discvery
	int d, f;
	bool visited;
	Vertex() : index(-1), parent(-1), dist(INT_MAX), visited(false), tag('w'), d(0), f(0) {}
	Vertex(int i) : index(i), parent(-1), dist(INT_MAX), visited(false), tag('w'), d(0), f(0) {};
};

struct AdjElem {
	int vertex;
	int weight;
	AdjElem() : vertex(), weight(0) {}
	AdjElem(int v, int w) : vertex(v), weight(w) {}

};

ostream& operator<<(ostream& os, const AdjElem& ae) {
	//os << "(" << ae.vertex << " " << ae.weight << ") ";
	os << "(" << ae.vertex << ") ";
	return os;
}

enum GraphType { UNDEF=-1, UNDIRECTED, DIRECTED };

class GraphAL { //adjacency list form
public:

	GraphAL(int VV, GraphType t = UNDIRECTED) : V(VV), type(t) { 
		vs.resize(V);
		for(int k = 0; k < V; ++k) vs[k] = k;
		adj.resize(V); 
	};
	void addEdge(int i, int j, int w = 1) {
		adj[i].push_back(AdjElem(j, w));
		if(type == UNDIRECTED) adj[j].push_back(AdjElem(i, w)); 
	}

	void printPath(int src, int v) {
		if(v == src) cout << v << " ";
		else if(vs[v].parent == -1) cout << "no path from " << src << " to " << v << " exists";
		else { printPath(src, vs[v].parent); cout << v << " ";	}
	}

	void BFS(int v);
	void DFS();
	void TopoSort();
	int countPathBFS(int u, int v) { return countPathDFSUtil(u, v); }
	vector<vector<int> > findPathDFS(int u, int v) {
		vector<int> path;
		vector<vector<int> > ret;
		findPathDFSUtil(u, v, path, ret);
		return ret;
	}

	bool twoColor(int v);
	friend ostream& operator<<(ostream& os, const GraphAL& g);

protected:
	GraphType type;
	int V;
	vector<Vertex> vs; //all vertices
	vector<list<AdjElem> > adj;

private:
	void DFSUtil(int u, int& time);
	void TopoSortUtil(int v, list<int>& s);
	int countPathDFSUtil(int u, int v);
	void findPathDFSUtil(int u, int v, const vector<int> &path, vector<vector<int> >& ret);
	bool isAncestor(int u, int v);
};

int GraphAL::countPathDFSUtil(int u, int v)
{
	if(u == v) return 1; 
	int n = 0;
	for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
		n += countPathDFSUtil(it->vertex, v);
	}
	return n;
}

void GraphAL::findPathDFSUtil(int u, int v, const vector<int> &path, vector<vector<int> >& ret)
{
	vector<int> newpath(path);
	newpath.push_back(u);
	if(u == v) {
		ret.push_back(newpath);
		return;
	}
	for(list<AdjElem>::const_iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
		int w = it->vertex;
		findPathDFSUtil(w, v, newpath, ret);
	}
}

bool GraphAL::isAncestor(int u, int v) 
{
	//is v the ancestor of u?
	assert(u != -1);
	int w = vs[u].parent;
	while(w != -1) {
		if(v == w) return true;
		w = vs[w].parent;
	}
	return false;
}

void GraphAL::TopoSort() 
{
	for(int v = 0; v < V; ++v) {
		vs[v].tag = 'w';
	}

	list<int> s;
	for(int v = 0; v < V; ++v) {
		if(vs[v].tag == 'w') TopoSortUtil(v, s);
	}
	for(list<int>::const_iterator it = s.begin(); it != s.end(); ++it) {
		cout << char(*it+'m') << " ";
	}
	cout << endl;
}

void GraphAL::TopoSortUtil(int v, list<int>& s)
{
	vs[v].tag = 'g';
	//visit all neighbors
	for(list<AdjElem>::const_iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
		int u = it->vertex;
		if(vs[u].tag == 'w') {
			vs[u].parent = v;
			TopoSortUtil(u, s);
		} 
	}
	vs[v].tag = 'b';
	s.push_front(v);
}

void GraphAL::DFS() 
{
	for(int v = 0; v < V; ++v) {
		vs[v].tag = 'w';
	}

	int time = 0;
	for(int v = 0; v < V; ++v) {
		if(vs[v].tag == 'w') DFSUtil(v, time);
	}
}

void GraphAL::DFSUtil(int v, int& time) 
{
	vs[v].d = ++time;
	vs[v].tag = 'g';
	cout << char(v+'m') << " ";
	//visit all neighbors
	for(list<AdjElem>::const_iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
		int u = it->vertex;
		//cout << "Edge ("<<v<<", "<<u<<") is ";
		if(vs[u].tag == 'w') {
			//	cout<<"tree edge"<<endl;
			vs[u].parent = v;
			DFSUtil(u, time);
		} else {
			//	if(vs[u].tag == 'g') cout << "back edge"<<endl;
			//	else if(isAncestor(u, v)) cout << "forward edge"<<endl;
			//	else cout << "cross edge"<<endl;
		}
	}
	vs[v].tag = 'b';
	vs[v].f = ++time;
}

void GraphAL::BFS(int v) { //BSF from vertex index v
	vs[v].dist = 0;
	vs[v].parent = -1;
	vs[v].visited = true;

	deque<int> q;
	q.push_back(v);
	while(!q.empty()) {
		v = q.front(); q.pop_front();
		cout << v << " ";
		//push unvisited neighbor nodes in queue
		for(list<AdjElem>::const_iterator it = adj[v].begin(); it != adj[v].end(); ++it) {
			int u = it->vertex;
			if(vs[u].visited) continue;
			vs[u].visited = true;
			vs[u].dist = vs[v].dist + 1;
			vs[u].parent = v; //parent index
			q.push_back(u);
		}
	}
	cout << endl;
	//print shorted paths
	for(int k = 0; k < V; ++k) {
		cout<<" vertex " << k << " distance from source = " << vs[k].dist << 
			" parent = " << vs[k].parent << endl;
	}
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
			int u = it->vertex;
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
