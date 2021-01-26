//
// Created by PRINCE NDHLOVU on 11/26/20.
//

#ifndef CODE_GENETICALGO_H
#define CODE_GENETICALGO_H

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

using namespace std;




class GeneticAlgo {
private:
    double crossingRate;
    double mutationRate;
    double selectionRate;
    int lastGeneration;
    int typeSelection;
    int typeCrossing;
    int typeMutation;
    int selecting_num;
    int crossing_num;
    vector<pair<double, vector<int> > > oldPopulation ;
    vector<pair<double, vector<int> > >  newPopulation;
    pair<double, vector<int> > population;
    int mutationValue;
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;

public:
    GeneticAlgo();
    ~GeneticAlgo();
    void initializeCrossOver(int,int);
    void initializeSelection(int,int);
    void mutate(int);
    void crossOver(int);
    void HamiltonianCircuit();
    void selection(int);
    void bestPath();
    void initializeMutations(int,int,int);
    void selectRoulette(int);
    void selectElite(int);
    void singleCrossOver(int);
    void initializeGeneration(int);
    void multiCrossOver(int);
    int bestFitness(vector<int> route);
    void switchMutations();
    void setPopulation(int);

    FileLoader graph;

};


#endif //CODE_GENETICALGO_H
