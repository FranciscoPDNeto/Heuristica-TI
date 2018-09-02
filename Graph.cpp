#include <iostream>
#include "Graph.h"

namespace TI {


Graph::Graph(const std::vector<Node>& nodes, const int& numNodes, 
  const std::string& edgeDistanceMethod) {
	
  numberNodes = numNodes;
  visited = new bool [numNodes];
  for (int i = 0; i < numberNodes; ++i) {
    visited[i] = false;
  }
  
  for (int i = 0; i < numNodes - 1; ++i) {
    for (int j = i+1; j < numNodes; ++j) {
      Edge edge(nodes[i], nodes[j], edgeDistanceMethod);
      
      addEdge(edge);
    }
  }
}

void Graph::addEdge(const Edge& edge) {
  adjMatrix[std::make_pair(edge.src, edge.dest)] = edge.cost;
}


}
