#include <cassert>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <utility>

namespace TI {



struct Node {
  int id;
  double x, y;
};


struct Edge {
  int src, dest;
  double cost;

  Edge(const Node& nodeSrc, const Node& nodeDest, const std::string& edgeDistanceMethod) {
  	src = nodeSrc.id;
    dest = nodeDest.id;

    double xd = nodeSrc.x - nodeDest.x;
    double yd = nodeSrc.y - nodeDest.y;
    if(edgeDistanceMethod == "EUC_2D") {
      cost = std::round(std::sqrt(std::pow(xd, 2) + std::pow(yd, 2)));
    } else if(edgeDistanceMethod == "ATT") {
      
      double rif = (std::sqrt((std::pow(xd, 2) + std::pow(yd, 2))/10.0));
      double tif = std::round(rif);
      cost = tif < rif ? tif + 1 : tif;
    }
  }

};

class Graph {
public:
	Graph(const std::vector<Node>& nodes, const int& numNodes, 
    const std::string& edgeDistanceMethod);

	~Graph() {
		delete visited;
	};

  void addEdge(const Edge& edge);

	std::map<std::pair<int, int>, double> adjMatrix;
  int numberNodes;
  bool *visited;
	
};

	
} // namespace TI
