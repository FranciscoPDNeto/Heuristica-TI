#include <stdio>
#include <stdlib>

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
  
  const std::string name;
  file >> name;

  return 0;
}
