//
// Created by PRINCE NDHLOVU on 11/26/20.
//

#ifndef CODE_SIMULATEDANNEALINGALGO_H
#define CODE_SIMULATEDANNEALINGALGO_H

#include "FileLoader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>
#include "math.h"
#include <random>
#include <stdlib.h>
#include <chrono>


class SimulatedAnnealingAlgo {
private:
    FileLoader graph;
    int temperature;
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    chrono::duration<double> time;
    pair<int, vector<int> > globalMinima;
    pair<int, vector<int> > localMinima;
    vector< pair<int, vector<int> > > neighbours;

public:
    SimulatedAnnealingAlgo();
    void HamiltonianCircuit();
    void makeNeighbours();
    void bestMinima();
    int bestFitness(vector<int>&);
    pair<int, vector<int> > setSearchSpace();


};


#endif //CODE_SIMULATEDANNEALINGALGO_H
