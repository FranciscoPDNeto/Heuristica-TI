#include "Graph.h"

namespace TI {


Graph(const std::vector<Edge>& edges, int numNodes) {
	adjacentList = new std::vector<int>[numNodes];

	for (Edge edge : edges) {
		adjacentList[edge.src].push_back(edge.dest);
	}
	/*
	for (int i = 0; i < edges.size(); ++i) {
		int src = edges.
	}*/
}


}