//
// Created by PRINCE NDHLOVU on 12/5/20.
//

#ifndef CODE_HAMILTONIANCIRCUIT_H
#define CODE_HAMILTONIANCIRCUIT_H

#include <limits.h>
#include "FileLoader.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <unordered_map>

class HamiltonianCircuit {
private:
    int pathSum;
    vector<vector<int> > totalCost;
    vector<vector<int> > totalPaths;
    unordered_map<int, vector<int> > map_nodes;
    int shortPath ;

public:
    HamiltonianCircuit();
    ~HamiltonianCircuit();
    void Dynamic();
    void BruteForce();
    void BruteForceRecursive(vector<int>, int&, vector<bool>, int, int);
    pair<int , vector<int> > DynamicRecursive(vector<int>, int&, int, int, int);
    bool Visited(vector<bool>&);
    void DisplayShortestPath();
    double CalculateDistances(int, int);
    void DisplayGraph();
    void FindDistance();
    void CountPaths();
    void LoadGraph();

};


#endif //CODE_HAMILTONIANCIRCUIT_H
