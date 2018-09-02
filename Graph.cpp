#include "Graph.h"

namespace TI {


Graph::Graph(const std::vector<Node>& nodes, const int& numNodes, 
  const std::string& edgeDistanceMethod) {
	
  numberNodes = numNodes;
  visited = new bool [numNodes];
  /*
  adjMatrix = new int* [numNodes];

  for (int i = 0; i < numNodes; ++i) {
    adjMatrix[i] = new int [numNodes];
  }
  */
  
  //std::vector<Edge> edges;
  for (int i = 0; i < numNodes - 1; ++i) {
    for (int j = i+1; j < numNodes; ++j) {
      Edge edge(nodes[i], nodes[j], edgeDistanceMethod);
      addEdge(edge);
      //edges.push_back(edge);
    }
  }
}

void Graph::addEdge(const Edge& edge) {
  adjMatrix[std::make_pair(edge.src, edge.dest)] = edge.cost;
}


}
