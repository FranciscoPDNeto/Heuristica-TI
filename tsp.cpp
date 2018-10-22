#include <algorithm>
#include <iostream>
#include <limits>
#include "tsp.h"

namespace {


template<typename T>
std::vector<T> slice(const std::vector<T>& v, int m, int n) {
  auto first = v.cbegin() + m;
  auto last = v.cbegin() + n + 1;
  
  std::vector<T> vec(first, last);
  return vec;
}


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

std::vector<int> opt2Swap(std::vector<int> tour, int i, int j) {
  std::vector<int> newTour;
  newTour.reserve(tour.size());

  std::vector<int> subSetTour = slice<int>(tour, 0, i-1);
  for (int city : subSetTour) {
    newTour.push_back(city);
  }

  subSetTour = slice<int>(tour, i, j);
  for (int k = subSetTour.size()-1; k >=0; --k) {
    newTour.push_back(subSetTour.at(k));
  }

  subSetTour = slice<int>(tour, j+1, tour.size()-1);
  for (int city : subSetTour) {
    newTour.push_back(city);
  }
 
  return newTour;
}


std::vector<int> opt3Swap(std::vector<int> tour, int i, int j, int k) {
  std::vector<int> newTour;
  newTour.reserve(tour.size());

  std::vector<int> subSetTour = slice<int>(tour, 0, i-1);
  for (int city : subSetTour) {
    newTour.push_back(city);
  }

  subSetTour = slice<int>(tour, i, j);
  for (int count = subSetTour.size()-1; count >=0; --count) {
    newTour.push_back(subSetTour.at(count));
  }

  subSetTour = slice<int>(tour, j+1, k);
  for (int count = subSetTour.size()-1; count >=0; --count) {
    newTour.push_back(subSetTour.at(count));
  }

  subSetTour = slice<int>(tour, k+1, tour.size()-1);
  for (int city : subSetTour) {
    newTour.push_back(city);
  }

  return newTour;
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

std::vector<std::vector<int>> TSP::getNeighborhood2OPT(std::vector<int> tour) {
  std::vector<std::vector<int>> neighborhood;

  for (int i = 1; i < tour.size() - 1; ++i) {
    for (int j = i + 1; j < tour.size(); ++j) {
        neighborhood.push_back(opt2Swap(tour, i, j));
    }
  }

  return neighborhood;
}

std::vector<std::vector<int>> TSP::getNeighborhood3OPT(std::vector<int> tour) {
  std::vector<std::vector<int>> neighborhood;

  for (int i = 1; i < tour.size() - 2; ++i) {
    for (int j = i + 1; j < tour.size() - 1; ++j) {
      for (int k = j + 1; k < tour.size(); ++k) {
        neighborhood.push_back(opt3Swap(tour, i, j, k));
      }
    }
  }

  return neighborhood;
}

void TSP::twoOPT(std::vector<int>& tour) {
  std::vector<int> tourChanged = tour;
  int bestCost = calculateTourCost(tour);
  for (int i = 1; i < tour.size() - 1; ++i) {
    for (int j = i + 1; j < tour.size(); ++j) {
        std::vector<int> newTour = opt2Swap(tour, i, j);
        
        int newDistance = calculateTourCost(newTour);
        if (newDistance < bestCost) {
          tourChanged = newTour;
          bestCost = newDistance;
        }
        
    }
  }

  tour = tourChanged;
}

void TSP::threeOPT(std::vector<int>& tour) {
  std::vector<int> tourChanged = tour;
  int bestCost = calculateTourCost(tour);
  for (int i = 1; i < tour.size() - 2; ++i) {
    for (int j = i + 1; j < tour.size() - 1; ++j) {
      for (int k = j + 1; k < tour.size(); ++k) {
        std::vector<int> newTour = opt3Swap(tour, i, j, k);
        
        int newDistance = calculateTourCost(newTour);
        if (newDistance < bestCost) {
          tourChanged = newTour;
          bestCost = newDistance;
        }
      }
    }
  }

  tour = tourChanged;
}

void TSP::variableNeighborhoodDescent(std::vector<int>& tour,
  double& totalCost, std::vector<int> cities) {

  int numCities = cities.size() - 1;
  this->nearestNeighbor(1, tour, totalCost, numCities);
  
  // Retira o ultimo elemento que é o retorno para a primeira cidade.
  tour.pop_back();
  /*
  std::vector<int> bestNeighborTwoOpt = tour; 
  twoOPT(bestNeighborTwoOpt);
  std::vector<int> bestNeighborThreeOpt = tour; 
  threeOPT(bestNeighborThreeOpt);

  if (calculateTourCost(bestNeighborTwoOpt) < calculateTourCost(bestNeighborThreeOpt))
    tour = bestNeighborTwoOpt;
  else
    tour = bestNeighborThreeOpt;
  */
  
  std::vector<std::vector<int>> neighborhood = getNeighborhood2OPT(tour);

  while(true) {
    int i;
    for(i = 0; i < neighborhood.size(); ++i) {
      int neighborCost = calculateTourCost(neighborhood[i]);

      if (neighborCost < totalCost) {
        totalCost = neighborCost;
        tour = neighborhood[i];
        neighborhood = getNeighborhood2OPT(tour);
        break;
      }
    }
    if (i == neighborhood.size())
      break;
  }

  tour.push_back(tour.front());
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

double TSP::getBestNeighbor(std::vector<int>& tour, 
  const std::vector<int> cities, 
  std::set<std::vector<int>>& tabuList) {

  int numCities = cities.size() - 1;
  
  // Retira o ultimo elemento que é o retorno para a primeira cidade.
  tour.pop_back();
  
  std::vector<std::vector<int>> neighborhood = getNeighborhood2OPT(tour);
  double totalCost = std::numeric_limits<double>::max();
  while(true) {
    int i;
    for(i = 0; i < neighborhood.size(); ++i) {
      int neighborCost = calculateTourCost(neighborhood[i]);

      if (neighborCost < totalCost && tabuList.find(neighborhood[i]) == tabuList.end()) {
        totalCost = neighborCost;
        tour = neighborhood[i];
        tabuList.insert(neighborhood[i]);
        // Trie::insert(tabuList, neighborhood[i]);
        neighborhood = getNeighborhood2OPT(tour);
        break;
      }
    }
    if (i == neighborhood.size())
      break;
  }

  tour.push_back(tour.front());
  
  return totalCost;
}

void TSP::tabuSearch(std::vector<int>& tour, double& totalCost, const std::vector<int> cities) {
  int numberCities = cities.size();
  //Trie::TrieNode* tabuList = Trie::getNode(numberCities);
  std::set<std::vector<int>> tabuList;
  variableNeighborhoodDescent(tour, totalCost, cities);

  int i = 0;
  std::vector<int> auxTour = tour;
  while(i < 100) {
    for (i = 0; i < 100; ++i) {
      double newCost = getBestNeighbor(auxTour, cities, tabuList);
      if (newCost < totalCost) {
        totalCost = newCost;
        tour = auxTour;
        break;
      }
    }
  }
}


}
