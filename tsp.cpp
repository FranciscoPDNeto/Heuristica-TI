#include <iostream>
#include <limits>
#include "tsp.h"

namespace TI {


void TSP::nearestNeighbor(const int& srcId,
	std::vector<int>& tour, double& totalCost, int& remainingNodes) {

  if (remainingNodes == 0) {
    double cost = graph.adjMatrix.at(std::make_pair(TSP::firstNodeId, srcId));
    totalCost += cost;
    tour.push_back(1);

    return;
  }
  double minCost = std::numeric_limits<double>::max();
  int nodeIdMinCost = 0;
  for (int i = 1; i <= graph.numberNodes; ++i) {
    if (!graph.visited[i-1]) {
      auto edgeIt = graph.adjMatrix.find(std::make_pair(srcId, i));
      if (edgeIt == graph.adjMatrix.end()) {
        edgeIt = graph.adjMatrix.find(std::make_pair(i, srcId));
        if (edgeIt == graph.adjMatrix.end())
          continue;
      }

      double cost = edgeIt->second;
      if (cost < minCost) {
        minCost = cost;
        nodeIdMinCost = i;
      }
    }
  }
  graph.visited[nodeIdMinCost-1] = true;
  tour.push_back(nodeIdMinCost);
  --remainingNodes;
  totalCost += minCost;

  nearestNeighbor(nodeIdMinCost, tour, totalCost, remainingNodes);
}

}
