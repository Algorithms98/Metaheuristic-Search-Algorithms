#include <iostream>
#include "SelectAlgo.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;


    enum alg_list{SP=1};
    enum method{Dynamic=1, BruteForce, Genetic, Simulated};

    Algorithm* algorithm = SelectAlgo::Technique(SP);

    //algorithm->Select(Dynamic)->Execute();
  //  algorithm->Select(BruteForce)->Execute();
  //  algorithm->Select(Genetic)->Execute();
    //algorithm->Select(Simulated)->Execute();

  for(int i = Genetic; i <= Simulated; i++){
      algorithm->Select(i)->Execute();
  }

    return 0;
}
