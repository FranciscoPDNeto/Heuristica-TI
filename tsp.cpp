#include <algorithm>
#include <iostream>
#include <limits>
#include "tsp.h"

namespace {


std::vector<std::vector<int>> getAllPermutations(
  std::vector<std::vector<int>>& allPermutations, std::vector<int> nodes) {
  
  std::sort(nodes.begin(), nodes.end());
  do {
    allPermutations.push_back(nodes);
  } while(std::next_permutation(nodes.begin(), nodes.end()));
}


std::vector<std::vector<int>> getNeighborhood(std::vector<int> tour) {
  std::vector<std::vector<int>> neighborhood;

  std::vector<int> tourChanged;
  for (int i = 0; i < tour.size() - 2; ++i) {
    tourChanged = tour;
    std::swap(tourChanged[i], tourChanged[i+1]);
    neighborhood.push_back(tourChanged);
    for (int j = i + 1; j < tour.size() - 1; ++j) {
        std::swap(tourChanged[j], tourChanged[j+1]);
        neighborhood.push_back(tourChanged);
    }
  }

  return neighborhood;
}


} // namespace ''

namespace TI {


void TSP::nearestNeighbor(const int& srcId,
	std::vector<int>& tour, double& totalCost, int& remainingNodes) {

  // Caso não tenha mais nós, volta para a cidade inicial e acaba a viagem.
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
        // Como é um grafo não direcionado, então pode estar registrado
        // o par contrário.
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

void TSP::variableNeighborhoodDescent(std::vector<int>& tour,
  double& totalCost, std::vector<int> cities) {
  //std::vector<std::vector<int>> allPermutations;
  // getAllPermutations(allPermutations, cities);
  int numCities = cities.size() - 1;
  this->nearestNeighbor(1, tour, totalCost, numCities);
  
  // for (int i = 0; i < allPermutations.size(); ++i) {
  // Retira o ultimo elemento que é o retorno para a primeira cidade.
  tour.pop_back();
  std::vector<std::vector<int>> neighbohood = getNeighborhood(tour);

  while(true) {
    int i;
    for(i = 0; i < neighbohood.size(); ++i) {
      double neighborCost = calculateTourCost(neighbohood[i]);

      if (neighborCost < totalCost) {
        totalCost = neighborCost;
        tour = neighbohood[i];
        neighbohood = getNeighborhood(tour);
        break;
      }
    }
    if (i == neighbohood.size())
      break;
  }

  tour.push_back(tour.front());
  // }
  
}

int TSP::calculateTourCost(const std::vector<int>& tour) {
  double cost = 0.0;
  for (int i = 0; i < tour.size() - 1; ++i) {
    int j = i + 1;
    auto edgeIt = graph.adjMatrix.find(std::make_pair(tour[i], tour[j]));
    if (edgeIt == graph.adjMatrix.end()) {
      // Como é um grafo não direcionado, então pode estar registrado
      // o par contrário.
      edgeIt = graph.adjMatrix.find(std::make_pair(tour[j], tour[i]));
      if (edgeIt == graph.adjMatrix.end())
        assert(false);
    }
    
    cost += edgeIt->second;
  }

  // Recupera o custo do retorno da última cidade para a primeira cidade.
  auto edgeIt = graph.adjMatrix.find(std::make_pair(tour.back(), tour[0]));
  if (edgeIt == graph.adjMatrix.end()) {
    // Como é um grafo não direcionado, então pode estar registrado
    // o par contrário.
    edgeIt = graph.adjMatrix.find(std::make_pair(tour[0], tour.back()));
    
    if (edgeIt == graph.adjMatrix.end())
      assert(false);
    
  }

  cost += edgeIt->second;

  return cost;
}

}
