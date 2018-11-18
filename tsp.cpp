#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include "tsp.h"

namespace {


template<typename T>
std::vector<T> slice(const std::vector<T>& v, int m, int n) {
  auto first = v.cbegin() + m;
  auto last = v.cbegin() + n + 1;
  
  std::vector<T> vec(first, last);
  return vec;
}


int getRandomNumber(const int& min, const int& max) {
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

  return dist(rng);
}


void getAllPermutations(
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


void printSet(const std::vector<int>& vec) {
  for (const int& e : vec) {
    std::cout << e << ", ";
  }
  std::cout << std::endl;
}


std::vector<int> solutionPertubation(const std::vector<int>& solution,
  std::set<std::vector<int>>& searchMemory) {
  
  std::vector<int> newSolution = solution;
  // Solução que será atualizada caso não tenha nenhum vizinho imediato
  // disponível.
  std::vector<int> auxSolution = solution;
  bool criteria = true;
  while (criteria) {
    for (std::size_t i = 1; i < auxSolution.size() - 1; ++i) {
      for (std::size_t j = i + 1; j < auxSolution.size(); ++j) {
        newSolution = opt2Swap(auxSolution, i, j);
        if (searchMemory.find(newSolution) == searchMemory.end()) {
          searchMemory.insert(newSolution);
          return newSolution;
        }
      }
    }
    if (criteria)
      auxSolution = opt2Swap(auxSolution, 1, 2);
  }
  
  searchMemory.insert(newSolution);
  return newSolution;
}


} // namespace ''

namespace TI {


void TSP::nearestNeighbor(const int& srcId,
	std::vector<int>& tour, double& totalCost, int& remainingNodes) {
  
  // Caso não tenha mais nós, volta para a cidade inicial e acaba a viagem.
  if (remainingNodes == 0) {
    const double cost = calculateCost(TSP::firstNodeId, srcId);
    // double cost = graph.adjMatrix.at(std::make_pair(TSP::firstNodeId, srcId));
    totalCost += cost;
    tour.push_back(1);
    return;
  }

  double minCost = std::numeric_limits<double>::max();
  int nodeIdMinCost = 0;
  for (int i = 1; i <= graph.numberNodes; ++i) {
    if (!graph.visited[i-1]) {
      const double cost = calculateCost(i, srcId);
      if (cost < minCost) {
        minCost = cost;
        nodeIdMinCost = i;
      }
    }
  }
  // Já passou por todos os nós.
  if (nodeIdMinCost == 0)
    return;
    
  assert(nodeIdMinCost != 0);
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

int TSP::twoOPT(std::vector<int>& tour) {
  
  int bestCost = calculateTourCost(tour);
  std::vector<int> newTour = tour;
  for (int i = 1; i < tour.size() - 1; ++i) {
    for (int j = i + 1; j < tour.size(); ++j) {
        newTour = opt2Swap(tour, i, j);
        
        int newDistance = calculateTourCost(newTour);
        if (newDistance < bestCost) {
          // tour = newTour;
          return twoOPT(newTour);
        }
        
    }
  }
  tour = newTour;
  return bestCost;
}

int TSP::threeOPT(std::vector<int>& tour) {
  std::vector<int> newTour = tour;
  int bestCost = calculateTourCost(tour);
  for (int i = 1; i < tour.size() - 2; ++i) {
    for (int j = i + 1; j < tour.size() - 1; ++j) {
      for (int k = j + 1; k < tour.size(); ++k) {
        newTour = opt3Swap(tour, i, j, k);
        
        int newDistance = calculateTourCost(newTour);
        if (newDistance < bestCost) {
          return threeOPT(newTour);
        }
      }
    }
  }
  tour = newTour;
  return bestCost;
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

int TSP::calculateCost(const int& city1, const int& city2) {
  auto edgeIt = graph.adjMatrix.find(std::make_pair(city1, city2));
  if (edgeIt == graph.adjMatrix.end()) {
    // Como é um grafo não direcionado, então pode estar registrado
    // o par contrário.
    edgeIt = graph.adjMatrix.find(std::make_pair(city2, city1));
    if (edgeIt == graph.adjMatrix.end()) {
      std::cout << "City1: " << city1 << " City2: " << city2 << std::endl;
      assert(false);
    }
  }

  return edgeIt->second;
}

int TSP::calculateTourCost(const std::vector<int>& tour) {
  double cost = 0.0;
  for (int i = 0; i < tour.size() - 1; ++i) {
    int j = i + 1;
    
    cost += calculateCost(tour[i], tour[j]);
  }

  cost += calculateCost(tour.back(), tour[0]);;

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

void TSP::tabuSearch(std::vector<int>& tour, double& totalCost, 
  const std::vector<int>& cities, const int& iterations) {
  
  int numberCities = cities.size();
  //Trie::TrieNode* tabuList = Trie::getNode(numberCities);
  std::set<std::vector<int>> tabuList;
  variableNeighborhoodDescent(tour, totalCost, cities);

  int i = 0;
  std::vector<int> auxTour = tour;
  while(i < iterations) {
    for (i = 0; i < iterations; ++i) {
      double newCost = getBestNeighbor(auxTour, cities, tabuList);
      if (newCost < totalCost) {
        totalCost = newCost;
        tour = auxTour;
        break;
      }
    }
  }
}

void TSP::iteratedLocalSearch(std::vector<int>& tour, double& totalCost,
  const std::vector<int>& cities, const int& iterations) {
  
  const std::size_t numberCities = cities.size();
  std::set<std::vector<int>> searchMemory;
  variableNeighborhoodDescent(tour, totalCost, cities);
  searchMemory.insert(tour);

  int i = 0;
  while (i < iterations) {
    for (i = 0; i < iterations; ++i) {
      // Retira o ultimo elemento que é o retorno para a primeira cidade.
      tour.pop_back();
      
      std::vector<int> newSolution = solutionPertubation(tour, searchMemory);
      newSolution.push_back(newSolution.front());
      tour.push_back(tour.front());
      double totalNewCost = getBestNeighbor(newSolution, cities, searchMemory);
      
      // Critério de aceitação forte, apenas se tiver melhora na solução.
      if (totalNewCost < totalCost) {
        totalCost = totalNewCost;
        tour = newSolution;
      }
    }
  }
}

void TSP::greedyRandomizedAdaptative(std::vector<int>& tour, double& totalCost,
  const std::vector<int>& cities, const int& iterations, const float& alpha) {

  int i = 0;
  variableNeighborhoodDescent(tour, totalCost, cities);
  std::vector<int> auxTour = tour;
  for (i = 0; i < iterations; ++i) {
    greedyRandomizedConstruction(alpha, auxTour, cities);
    // variableNeighborhoodDescent(tour, totalCost, cities);
    
    const double newCost = twoOPT(auxTour);
    if (newCost < totalCost) {
      totalCost = newCost;
      tour = auxTour;
    }
    
    
  }

}

void TSP::greedyRandomizedConstruction(const float& alpha, std::vector<int>& tour,
  const std::vector<int>& cities) {
  int counterRestrictCandidateList = 0;
  int selectedCandidate;
  std::vector<int> candidateSet = cities;
  candidateSet.reserve(cities.size());
  std::vector<int> restrictCandidateList;

  std::vector<int> partialSolution;
  partialSolution.reserve(cities.size()+1);
  partialSolution.push_back(candidateSet.at(0));
  candidateSet.erase(candidateSet.begin());

  while (partialSolution.size() < cities.size()) {
    double cMin = std::numeric_limits<double>::max();
    double cMax = std::numeric_limits<double>::min();
    
    for (const int& candidate : candidateSet) {
      double cost = calculateCost(partialSolution.back(), candidate);

      if (cost > cMax)
        cMax = cost;
      
      if (cost < cMin)
        cMin = cost;
    }
    
    const double costThreshold = cMin + alpha*(cMax - cMin);

    restrictCandidateList.clear();
    for (const int& candidate : candidateSet) {
      double cost = calculateCost(partialSolution.back(), candidate);
      if (cost <= costThreshold) {
        restrictCandidateList.push_back(candidate);
      }
    }
    
    const int selectedCandidate = 
      restrictCandidateList[getRandomNumber(0, restrictCandidateList.size()-1)];
      
    partialSolution.push_back(selectedCandidate);
    candidateSet.erase(
      std::remove(candidateSet.begin(), candidateSet.end(), selectedCandidate), candidateSet.end());
    
  }

  // partialSolution.push_back(partialSolution.front());
  
  tour = partialSolution;
}

}
