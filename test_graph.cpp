#include "graph.h"

void testGraph(int argc, char* argv[])
{
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
	vector<int> vbfs = g.BFS(3);
	for(unsigned k = 0; k < vbfs.size(); ++k) {
		cout << char(vbfs[k]+'m') << " ";
	}
	cout << endl;

	cout << "DFS of graph g: ";
	vector<int> dfs = g.DFS(true);
	for(unsigned k = 0; k < dfs.size(); ++k) {
		cout << char(dfs[k]+'m') << " ";
	}
	cout << endl;
	cout << "DFS of graph g: ";
	vector<int> dfs2 = g.DFS2(true);
	for(unsigned k = 0; k < dfs2.size(); ++k) {
		cout << char(dfs2[k]+'m') << " ";
	}
	cout << endl;

	cout << "Topo sort of graph g: ";
	vector<int> ts = g.TopoSort();
	for(vector<int>::const_iterator it = ts.begin(); it != ts.end(); ++it) {
		cout << char(*it+'m') << " ";
	}
	cout << endl;
	
	cout << "SCC of graph g: ";
	vector<vector<int> > scc = g.findSCC();
	for(unsigned i = 0; i < scc.size(); ++i) {
		cout << "(";
		for(unsigned j = 0; j < scc[i].size(); ++j) {
			cout << char(scc[i][j]+'m') << " ";
		}
		cout << ") ";
	}
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
