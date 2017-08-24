#include <iostream>
#include <random>
#include <string>
#include <chrono>

#include "cxxopts.hpp"

template<typename Dice>
void generate_values(Dice dice, unsigned times)
{
  for(int i = 0; i < times; i++)
  {
    std::cout << dice() << std::endl;
  }
}

int main(int argc, char *argv[])
{


  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  bool verbose = false;
  bool gaussian = false;
  bool uniform_real = false;
  bool uniform_int = false;
  unsigned times = 1;
  double mu = 0.0;
  double sigma = 1.0;

  cxxopts::Options options("randnum", "random swiss army knife");
  options.add_options()
    ("g,gaussian"     , "gaussian/normal distribution.", cxxopts::value<bool>(gaussian))
    ("u,uniform-real" , "uniform over the reals (doubles); Defaults between 0 and 1.",cxxopts::value<bool>(uniform_real))
    ("i,uniform-int"  , "uniform over integers(long); Defaults between 0 and 9.",cxxopts::value<bool>(uniform_int))
    ("n,times"        , "number of times to generate random values.", cxxopts::value<unsigned>(times))
    ("m,mu"           , "Mean value for a gaussian. Default 0.", cxxopts::value<double>(mu))
    ("s,sigma"        , "Standard deviation for a gaussian. Default 1.", cxxopts::value<double>(sigma))
    ("t,top"          , "Top of range for uniform.", cxxopts::value<std::string>())
    ("b,bottom"       , "Bottom of range for uniform.", cxxopts::value<std::string>())
    ("seed"           , "Seed for the PRNG", cxxopts::value<unsigned>(seed))
    ("v,verbose"      , "Print additional information, such as the seed", cxxopts::value<bool>(verbose))
    ("h,help"         , "produce help message")
  ;
  options.parse(argc, argv);
  if (verbose)
  {
    std::cout << "Seed: " << seed << std::endl;
  }
  std::mt19937 generator(seed);

  
  if (gaussian)
  {
    std::normal_distribution<double> distribution(mu, sigma);
    generate_values(std::bind(distribution, generator), times);
  }
  else if(uniform_real)
  {
    double top = 1.0;
    double bottom = 0.0;
    if (options.count("top")) { top = std::stod(options["top"].as<std::string>()); }
    if (options.count("bottom")) { bottom = std::stod(options["bottom"].as<std::string>()); }
    std::uniform_real_distribution<double> distribution (bottom, top);
    generate_values(std::bind(distribution, generator), times);
  }
  else if(uniform_int)
  {
    long top = 9;
    long bottom = 0;
    if (options.count("top")) { top = std::stol(options["top"].as<std::string>()); }
    if (options.count("bottom")) { bottom = std::stol(options["bottom"].as<std::string>()); }
    std::uniform_int_distribution<long> distribution (bottom, top);
    generate_values(std::bind(distribution, generator), times);
  }
  else
  {
    std::cout << options.help({""}) << std::endl;
    exit(0);
  }

  return 0;
}
