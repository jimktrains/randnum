#include <iostream>
#include <random>
#include <string>
#include <chrono>

int main(int argc, char **argv)
{
  if (argc < 2) { return -1; }

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);

  
  if (("normal" == std::string(argv[1])) || 
      ("gaussian" == std::string(argv[1])))
  {
  
    if (argc < 4) { return -2; }
    double mu = std::stod(argv[2]);
    double sigma =  std::stod(argv[3]);
    std::normal_distribution<double> distribution(mu, sigma);
    std::cout << distribution(generator) << std::endl;
  }
  else if("uniform-real" == std::string(argv[1]))
  {
    if (argc < 4) { return -2; }
    double begin = std::stod(argv[2]);
    double end =  std::stod(argv[3]);
    std::uniform_real_distribution<double> distribution (begin, end);
    std::cout << distribution(generator) << std::endl;
  }
  else if("uniform-int" == std::string(argv[1]))
  {
    if (argc < 4) { return -2; }
    int begin = std::stoi(argv[2]);
    int end =  std::stoi(argv[3]);
    std::uniform_int_distribution<int> distribution (begin, end);
    std::cout << distribution(generator) << std::endl;
  }

  return 0;
}
