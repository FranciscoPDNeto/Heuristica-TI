#include <vector>
#include "Graph.h"

namespace TI {


class TSP {
public:

  TSP(const Graph& graph, const int& firstNodeId) : graph(graph), firstNodeId(firstNodeId){
  };
  
  void nearestNeighbor(const int& srcId, std::vector<int>& tour, 
    int& totalCost, int& remainingNodes);

  
private:
  Graph graph;
  int firstNodeId;
};


}
