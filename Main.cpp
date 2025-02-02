#include <ctime>
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
  int nodeLength;
  std::getline(file, key, ':');
  file >> nodeLength;
  
  std::string edgeDistanceMethod;
  std::getline(file, key, ':');
  file >> edgeDistanceMethod;
  
  // Linha contendo o identificador que as coordenadas vão começar a serem lidas.
  getline(file, ignore);
  getline(file, ignore);

  std::vector<TI::Node> nodes;
  std::vector<int> cities;
  for (int i = 0; i < nodeLength; ++i) {
    TI::Node node;
    
    file >> node.id >> node.x >> node.y;
    cities.push_back(node.id);
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

  std::clock_t start = std::clock();
  double duration;
  tsp.iteratedLocalSearch(tour, totalCost, cities, 300);
  duration = (double)(std::clock() - start) / CLOCKS_PER_SEC;
  std::cout << duration << " second" << std::endl;
  /*
  // Aqui mostra o caminho feito pelo viajante.
  for (int id : tour) {
    std::cout << id << std::endl;
  }
  */
  std::cout << "Total cost: " << totalCost << std::endl;
  file.close();
  return 0;
}
