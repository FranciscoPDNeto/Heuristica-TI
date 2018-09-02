#include <algorithm>
#include <fstream>
#include <iostream>
#include "tsp.h"

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "A quantidade de argumentos está incorreta, é preciso do nome"
      "do arquivo com as informações do problema." << std::endl;

    return -1;
  }

  const std::string filename(argv[1]);

  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "O arquivo não pode ser aberto." << std::endl;

    return -1;
  }

  // Ignora as três primeiras linhas que trazem informações irrelevantes para
  // a resolução do problema, serve apenas para identificação.
  std::string ignore;
  for (int i = 0; i < 3; ++i) {
    getline(file, ignore);
  }
  
  std::string key;
  std::string twoPoints;
  int nodeLength;
  file >> key >> twoPoints >> nodeLength;
  
  std::string edgeDistanceMethod;
  file >> key >> twoPoints >> edgeDistanceMethod;
  
  // Linha contendo o identificador que as coordenadas vão começar a serem lidas.
  getline(file, ignore);
  getline(file, ignore);

  std::vector<TI::Node> nodes;
  for (int i = 0; i < nodeLength; ++i) {
    TI::Node node;
    
    file >> node.id >> node.x >> node.y;
    nodes.push_back(node);
  }

  TI::Graph graph(nodes, nodeLength, edgeDistanceMethod);

  std::vector<int> tour;
  tour.push_back(1);
  graph.visited[0] = true;
  int remainingNodes = nodeLength - 1;
  double totalCost = 0.0;
  int firstNodeId = 1;
  TI::TSP tsp(graph, firstNodeId);
  tsp.nearestNeighbor(firstNodeId, tour, totalCost, remainingNodes);
  
  for (int id : tour) {
    std::cout << id << std::endl;
  }
  std::cout << "Total cost: " << totalCost << std::endl;
  file.close();
  return 0;
}
