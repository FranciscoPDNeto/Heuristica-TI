A heuristica escolhida para ser implementada e usada foi a heuristica do vizinho mais próximo.
Basicamente é selecionado a cidade em que o viajante começa, escolhi o 1 mesmo para simplificação e
consistencia no resultado, mas poderia ser um nó arbitrário. 
A partir dele, verifica qual a cidade mais próxima de onde ele se encontra, indo para ela. Esse comportamento se segue, visitando a cidade apenas uma única vez, até que se volte para a primeira cidade que se iniciou a trajetória.

Para compilar o código execute:
	g++ -std=c++11 Main.cpp tsp.cpp Graph.cpp

E para executar o código:
	./a.out <Nome_do_arquivo.tsp>