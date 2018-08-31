#include "Graph.h"

namespace TI {


Graph::Graph(const std::vector<Node>& nodes, const int& numNodes, 
  const std::string& edgeDistanceMethod) {
	
  //adjacentList = new std::vector<int>[numNodes];
  
  std::vector<Edge> edges;
  for (int i = 0; i < nodes.size() - 1; ++i) {
    for (int j = i+1; j < nodes.size(); ++j) {
      Edge edge(nodes[i], nodes[j], edgeDistanceMethod);

      edges.push_back(edge);
    }
  }
  /*
	for (Edge edge : edges) {
		adjacentList[edge.src].push_back(edge.dest);
	}
	
	for (int i = 0; i < edges.size(); ++i) {
		int src = edges.
	}*/
}


}
