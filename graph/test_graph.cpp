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
	//cout << "Vertices are " << endl;
	//h.printVertices();

	cout << "DFS of graph h: ";
	dfs = h.DFS2();
	for(unsigned k = 0; k < dfs.size(); ++k) {
		cout << char(dfs[k]+'a') << " ";
	}
	cout << endl;
	//cout << "Vertices are " << endl;
	//h.printVertices();

	cout << "SCC of graph h: ";
	scc = h.SCC();
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

	vector<Edge> MST;
	cout << "MST Kruskal's algorithm: " << endl;
	MST = hh.MSTKruskal();
	for(unsigned k = 0; k < MST.size(); ++k) 
		cout << MST[k] << " ";
	cout << endl;

	cout << "MST Prim's algorithm: " << endl;
	MST = hh.MSTPrim();
	for(unsigned k = 0; k < MST.size(); ++k) 
		cout << MST[k] << " ";
	cout << endl;

	/*	int p = 3, v = 9;
	cout << " number of paths between " << p << " and " << v << " is " << g.countPaths(p,v) << endl;
	vector<vector<int> > ret = g.findPaths(p, v);
	cout << " number of paths between " << p << " and " << v << " is " << ret.size() << endl;
	for(unsigned int k = 0; k < ret.size(); ++k) {
	cout << "  Path " << k << ": ";
	for(unsigned int j = 0; j < ret[k].size(); ++j) cout << ret[k][j] << " ";
	cout << endl;
	}
	*/

	vector<bool> ap; //articulation points
	vector<Edge> bridge; //bridges
	//graphs from http://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
	GraphAL g1(5);
	g1.addEdge(1, 0); g1.addEdge(0, 2); g1.addEdge(2, 1); g1.addEdge(0, 3);	g1.addEdge(3, 4);

	GraphAL g2(4);
	g2.addEdge(0, 1); g2.addEdge(1, 2);	g2.addEdge(2, 3);

	GraphAL g3(7);
	g3.addEdge(0, 1); g3.addEdge(1, 2);	g3.addEdge(2, 0); g3.addEdge(1, 3); 
	g3.addEdge(1, 4); g3.addEdge(1, 6); g3.addEdge(3, 5); g3.addEdge(4, 5); 
	ap = g1.AP();
	cout << "Articulation points in g1: ";
	for(unsigned k = 0; k < ap.size(); ++k) 
		if(ap[k]) cout << k << " ";
	cout << endl;

	ap = g2.AP();
	cout << "Articulation points in g2: ";
	for(unsigned k = 0; k < ap.size(); ++k) 
		if(ap[k]) cout << k << " ";
	cout << endl;

	ap = g3.AP();
	cout << "Articulation points in g3: ";
	for(unsigned k = 0; k < ap.size(); ++k) 
		if(ap[k]) cout << k << " ";
	cout << endl;

	bridge = g1.Bridge();
	cout << "Bridges in g1: ";
	for(unsigned k = 0; k < bridge.size(); ++k) 
		cout << bridge[k] << " ";
	cout << endl;

	bridge = g2.Bridge();
	cout << "Bridges in g2: ";
	for(unsigned k = 0; k < bridge.size(); ++k) 
		cout << bridge[k] << " ";
	cout << endl;

	bridge = g3.Bridge();
	cout << "Bridges in g3: ";
	for(unsigned k = 0; k < bridge.size(); ++k) 
		cout << bridge[k] << " ";
	cout << endl;

	cout << endl;

	///Single-source minimum path problem
	//graph from CLRS P652 Fig 24.4
	GraphAL gs(5, DIRECTED);
	gs.addEdge(0,1,6); gs.addEdge(0,3,7);
	gs.addEdge(1,2,5); gs.addEdge(1,3,8); gs.addEdge(1,4,-4);
	gs.addEdge(2,1,-2);
	gs.addEdge(3,2,-3); gs.addEdge(3,4,9);
	gs.addEdge(4,0,2); gs.addEdge(4,2,7);

	cout << "Running Bellman-ford algorithm on graph gs ..." << endl;
	bool tag = gs.BellmanFord(0);
	if(tag) cout << "Graph has no negative cycle." << endl;
	else cout << "Graph has negative cycle!" << endl;
	gs.printVertices();

	//graph from CLRS P656 Fig 24.5
	GraphAL gt(6, DIRECTED);
	gt.addEdge(0,1,5); gt.addEdge(0,2,3);
	gt.addEdge(1,2,2); gt.addEdge(1,3,6);
	gt.addEdge(2,3,7); gt.addEdge(2,4,4); gt.addEdge(2,5,2);
	gt.addEdge(3,4,-1); gt.addEdge(3,5,1);
	gt.addEdge(4,5,-2);

	cout << "Running shorted-path algorithm on dag gt ..." << endl;
	gt.SPdag(1);
	gt.printVertices();
	
	//graph from CLRS P659 Fig 24.6
	GraphAL gr(5, DIRECTED);
	gr.addEdge(0,1,10); gr.addEdge(0,3,5);
	gr.addEdge(1,2,1); gr.addEdge(1,3,2);
	gr.addEdge(2,4,4); 
	gr.addEdge(3,1,3); gr.addEdge(3,2,9); gr.addEdge(3,4,2);
	gr.addEdge(4,0,7); gr.addEdge(4,2,6);

	cout << "Running Dijkstra's algorithm on dag gr ..." << endl;
	gr.Dijkstra(0);
	gr.printVertices();
	
	///All-pairs shorted paths
	//graph from CLRS P690 Fig 25.1
	GraphAM gu(5, DIRECTED);
	gu.addEdge(0,1,3); gu.addEdge(0,2,8); gu.addEdge(0,4,-4);
	gu.addEdge(1,3,1); gu.addEdge(1,4,7);
	gu.addEdge(2,1,4); 
	gu.addEdge(3,0,2); gu.addEdge(3,2,-5);
	gu.addEdge(4,3,6);
	cout << gu << endl;

	cout << "Running all-pairs shortest paths algorithm (slow) on graph gu ... " << endl;
	gu.AllPairsSPSlow();
	cout << "Shorted path weight matrix is : " << endl;
	gu.printSPWT();

	gu.AllPairsSPFast();
	cout << "Shorted path weight matrix is : " << endl;
	gu.printSPWT();

	cout << "Running Floyd-Warshall's all-pairs shortest paths algorithm on graph gu ... " << endl;
	gu.AllPairsSPFW();
	cout << "Shorted path weight matrix is : " << endl;
	gu.printSPWT();
	cout << "Shorted path predecessor matrix is : " << endl;
	gu.printSPPR();
	
	GraphAL ggg(4);
	ggg.addEdge(0,1);ggg.addEdge(0,2);ggg.addEdge(0,3);
	ggg.addEdge(1,3);ggg.addEdge(2,3);ggg.addEdge(1,2);

	int i = 0, j = 3;
	
	cout << "Number of paths between " << i << " and " << j << " is " << ggg.CountPaths(i, j) << endl;
	vector<vector<int> > paths = ggg.FindPaths(i, j);
	cout << paths << endl;	
}
