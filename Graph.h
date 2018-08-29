#include <vector>

namespace TI {


struct Edge {
	int src, dest;
};

public class Graph {
public:
	Graph(const std::vector<Edge>& edges, int numNodes);

	~Graph() {
		delete[] adjacentList;
	}
	
private:
	std::vector<int> *adjacentList;
};

	
} // namespace TI