//
// Created by PRINCE NDHLOVU on 11/26/20.
//

#include "SimulatedAnnealingAlgo.h"

SimulatedAnnealingAlgo::SimulatedAnnealingAlgo() {
    graph.loadData();
    graph.loadCosts();
    temperature = graph.getCosts().size() * 5;

}

void SimulatedAnnealingAlgo::HamiltonianCircuit() {

    cout << "Simulated Annealing Algorithms" << endl;

    start = chrono::high_resolution_clock::now();

    localMinima = setSearchSpace();
    globalMinima = localMinima;

    for(int learningRate = temperature; learningRate > 0; learningRate--){

        makeNeighbours();
        bestMinima();
    }
    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<std::chrono::duration<double>>(end - start);


    cout << "Total distance " << globalMinima.first << endl;
    for(int i = 0; i < globalMinima.second.size();i++){
        cout << globalMinima.second[i] << " ->";
    }
    cout << "Execution time: " << time.count() << endl;

}

void SimulatedAnnealingAlgo::makeNeighbours() {

    vector<int> firstChild, secondChild, firstParent, secondParent;
    int limit = 0.25 * graph.getCosts().size();
    random_device seed;
    mt19937 randy(seed());
    uniform_int_distribution<int> range(1, graph.getCosts().size() - limit);
    int mini = range(randy);
    int maxi = mini + limit -1;
    firstParent = localMinima.second;

    for(int i = 0; i < firstParent.size(); i++){
        firstChild.push_back(0);
        secondChild.push_back(0);
    }

    while(neighbours.size() < temperature ){
        int firstChil = 1;
        int secondChil = 1;
        secondParent = setSearchSpace().second;

        for(int i = 1; i < firstParent.size(); i++){
            bool first = false;
            bool second = false;
            for(int k = mini; k <= maxi; k++){
                if(firstParent[i] == secondParent[k]){
                    first = true;
                }
                if(firstParent[k] == secondParent[i] ){
                    second = true;
                }
            }
            if(mini == firstChil){
                firstChil = firstChil + maxi - mini + 1;
            }
            if(secondChil == mini){
                secondChil = secondChil + maxi - mini + 1;
            }
            if(!first){
                secondChild[secondChil++] = firstParent[i];
            }
            if(!second){
                firstChild[firstChil++] = secondParent[i];
            }
        }
        for(int i = 0; i <= maxi - mini; i++){
            firstChild[i+mini] = firstParent[mini+i];
            secondChild[i+mini] = secondParent[mini+i];
        }
        neighbours.push_back(make_pair(bestFitness(firstChild), firstChild));
        if(neighbours.size() < temperature){
            neighbours.push_back(make_pair(bestFitness(secondChild), secondChild));
        }

    }
}

void SimulatedAnnealingAlgo::bestMinima() {

    localMinima = neighbours[0];

    for(int i = 0; i < neighbours.size(); i++){
        if(localMinima.first > neighbours[i].first){
            localMinima = neighbours[i];
        }
    }
    if(globalMinima > localMinima){

        globalMinima = localMinima;

    }

}

int SimulatedAnnealingAlgo::bestFitness(vector<int>& space) {

    int x = 0;

    for(int i = 0; i < space.size() -1; i++){
        x = x + graph.getCosts()[space[i]][space[i+1]];
    }
    return x;

}

pair<int, vector<int> > SimulatedAnnealingAlgo::setSearchSpace() {

    pair<int, vector<int> >  space;

    for(int i = 0; i < graph.getCosts().size(); i++){
        space.second.push_back(i);
    }
    space.second.push_back(0);
    random_shuffle(space.second.begin() +1, space.second.end()-1);
    space.first = bestFitness(space.second);
    return space;

}
