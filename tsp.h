#include <vector>
#include <set>
#include "Graph.h"
#include "Trie.h"

namespace TI {


class TSP {
public:

  TSP(const Graph& graph, const int& firstNodeId) : graph(graph), firstNodeId(firstNodeId){
  };

  /**
   * \brief Heuristica do vizinho mais perto.
   * 
   * \param srcId Id da cidade onde o viajante se encontra.
   * \param tour Caminho feito até então pelo viajante.
   * \param totalCost Custo total até o momento.
   * \param remainingNodes Ids das cidades que ainda falta o viajante visitar.
   */
  void nearestNeighbor(const int& srcId, std::vector<int>& tour, 
    double& totalCost, int& remainingNodes);

  std::vector<std::vector<int>> getNeighborhood2OPT(std::vector<int> tour);

  std::vector<std::vector<int>> getNeighborhood3OPT(std::vector<int> tour);

  int twoOPT(std::vector<int>& tour);

  int threeOPT(std::vector<int>& tour);

  /**
   * \brief Heuristica multi-vizinhança.
   * 
   * \param tour Caminho feito da solução ótima local que será preenchido.
   * \param totalCost Custo total da solução ótima local que será preenchido.
   * \param cities Lista contendo as cidades.                                                                             
   */
  void variableNeighborhoodDescent(std::vector<int>& tour,
    double& totalCost, std::vector<int> cities);

  int calculateCost(const int& city1, const int& city2);

  int calculateTourCost(const std::vector<int>& tour);

  double getBestNeighbor(std::vector<int>& tour, 
    const std::vector<int> cities, 
    std::set<std::vector<int>>& tabuList);

  void tabuSearch(std::vector<int>& tour, double& totalCost, 
    const std::vector<int>& cities, const int& iterations);

  /**
   * \brief Heuristica de Busca Local Iterada, onde é aplicado busca local, e 
   * a solução encontrada é perturbada, começando a busca local novamente,
   * até se terminar as iterações.
   *
   * \param tour Caminho feito da solução ótima local que será preenchido
   * \param totalCost Custo total da solução ótima local.
   * \oaram cities Lista contendo as cidades.
   * \param iterations Número de iterações que é o critério de parada do
   * melhoramento da solução.
   */
  void iteratedLocalSearch(std::vector<int>& tour, double& totalCost,
    const std::vector<int>& cities, const int& iterations);

  void greedyRandomizedAdaptative(std::vector<int>& tour, double& totalCost, 
    const std::vector<int>& cities, const int& iterations, const float& alpha);

  void greedyRandomizedConstruction(const float& alpha, std::vector<int>& tour,
    const std::vector<int>& cities);
  
private:
  Graph graph;
  int firstNodeId;
};


}
