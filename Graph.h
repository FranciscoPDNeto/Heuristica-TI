#include <cassert>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <utility>

namespace TI {



struct Node {
  int id, x, y;
};


struct Edge {
  int src, dest, cost;

  Edge(const Node& nodeSrc, const Node& nodeDest, const std::string& edgeDistanceMethod) {
  	src = nodeSrc.id;
    dest = nodeDest.id;

    int xd = nodeSrc.x - nodeDest.x;
    int yd = nodeSrc.y - nodeDest.y;
    if(edgeDistanceMethod.compare("EUC_2D")) {  

      cost = (int) std::round(std::sqrt(std::pow(xd, 2) + std::pow(xd, 2)));
    } else if(edgeDistanceMethod.compare("ATT")) {
      
      double rif = (std::sqrt((std::pow(xd, 2) + std::pow(xd, 2))/10.0));
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

	std::map<std::pair<int, int>, int> adjMatrix;
  int numberNodes;
  bool *visited;
private:
	
};

	
} // namespace TI
