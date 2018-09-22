#include <vector>
#include "Graph.h"

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

  /**
   * \brief Heuristica multi-vizinhança.
   * 
   * \param tour Caminho feito da solução ótima local que será preenchido.
   * \param totalCost Custo total da solução ótima local que será preenchido.
   * \param cities Lista contendo as cidades.                                                                             
   */
  void variableNeighborhoodDescent(std::vector<int>& tour,
    double& totalCost, std::vector<int> cities);

  int calculateTourCost(const std::vector<int>& tour);
  
private:
  Graph graph;
  int firstNodeId;
};


}
