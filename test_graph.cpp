#include "graph.h"

void testGraph(int argc, char* argv[])
{
	vector<int> dfs, bfs, ts; //ts: topological sort
	vector<vector<int> > scc; //strongly connected components

	//graph from CLRS P615 Fig 22.8
	GraphAL g(14, DIRECTED);
	g.addEdge(0,4); g.addEdge(0,5); g.addEdge(0,11);
	g.addEdge(1,2); g.addEdge(1,4); g.addEdge(1,8);
	g.addEdge(2,5);	g.addEdge(2,6); g.addEdge(2,9);
	g.addEdge(3,2); g.addEdge(3,6); g.addEdge(3,13);
	g.addEdge(4,7);
	g.addEdge(5,8); g.addEdge(5,12);
	g.addEdge(6,5);
	g.addEdge(8,7);
	g.addEdge(9,10);g.addEdge(9,11);
	g.addEdge(10,13);
	g.addEdge(12,9);

	cout << "BFS of graph g: ";
	bfs = g.BFS(3);
	for(unsigned k = 0; k < bfs.size(); ++k) {
		cout << char(bfs[k]+'m') << " ";
	}
	cout << endl;

	cout << "DFS of graph g: ";
	dfs = g.DFS();
	for(unsigned k = 0; k < dfs.size(); ++k) {
		cout << char(dfs[k]+'m') << " ";
	}
	cout << endl;

	cout << "DFS of graph g: ";
	dfs = g.DFS2();
	for(unsigned k = 0; k < dfs.size(); ++k) {
		cout << char(dfs[k]+'m') << " ";
	}
	cout << endl;
	
	cout << "Topological sort of graph g: ";
	ts = g.TopoSort();
	for(unsigned k = 0; k < ts.size(); ++k) {
		cout << char(ts[k]+'m') << " ";
	}
	cout << endl;

	//graph from CLRS P616 Fig 22.9	
	GraphAL h(8, DIRECTED);
	h.addEdge(0, 1);
	h.addEdge(1, 2); h.addEdge(1, 4); h.addEdge(1, 5);
	h.addEdge(2, 3); h.addEdge(2, 6);
	h.addEdge(3, 2); h.addEdge(3, 7);
	h.addEdge(4, 0); h.addEdge(4, 5);
	h.addEdge(5, 6);
	h.addEdge(6, 5); h.addEdge(6, 7);
	h.addEdge(7, 7);
	
	cout << "DFS of graph h: ";
	dfs = h.DFS();
	for(unsigned k = 0; k < dfs.size(); ++k) {
		cout << char(dfs[k]+'a') << " ";
	}
	cout << endl;
	cout << "Vertices are " << endl;
	h.printVertices();

	cout << "DFS of graph h: ";
	dfs = h.DFS2();
	for(unsigned k = 0; k < dfs.size(); ++k) {
		cout << char(dfs[k]+'a') << " ";
	}
	cout << endl;
	cout << "Vertices are " << endl;
	h.printVertices();

	cout << "SCC of graph h: ";
	scc = h.findSCC();
	for(unsigned i = 0; i < scc.size(); ++i) {
		cout << "(";
		for(unsigned j = 0; j < scc[i].size(); ++j) {
			cout << char(scc[i][j]+'a') << " ";
		}
		cout << ") ";
	}
	cout << endl;

	//graph from CLRS P625 Fig 23.1
	GraphAL hh(9, UNDIRECTED);
	hh.addEdge(0, 1, 4); hh.addEdge(0, 7, 8);
	hh.addEdge(1, 2, 8); hh.addEdge(1, 7, 11);
	hh.addEdge(2, 3, 7); hh.addEdge(2, 5, 4); hh.addEdge(2, 8, 2);
	hh.addEdge(3, 4, 9); hh.addEdge(3, 5, 14);
	hh.addEdge(4, 5, 10);
	hh.addEdge(5, 6, 2);
	hh.addEdge(6, 7, 1); hh.addEdge(6, 8, 6);
	hh.addEdge(7, 8, 7);
	cout << hh << endl;
	vector<Edge> MSTedges = hh.MSTKruskal();
	for(unsigned k = 0; k < MSTedges.size(); ++k) 
		cout << MSTedges[k] << " ";
	cout << endl;

	int p = 3, v = 9;
	cout << " number of paths between " << p << " and " << v << " is " << g.countPaths(p,v) << endl;
	vector<vector<int> > ret = g.findPaths(p, v);
	cout << " number of paths between " << p << " and " << v << " is " << ret.size() << endl;
	for(unsigned int k = 0; k < ret.size(); ++k) {
		cout << "  Path " << k << ": ";
		for(unsigned int j = 0; j < ret[k].size(); ++j) cout << ret[k][j] << " ";
		cout << endl;
	}
}
