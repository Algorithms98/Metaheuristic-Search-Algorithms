//
// Created by PRINCE NDHLOVU on 11/26/20.
//


#include "GeneticAlgo.h"

GeneticAlgo::~GeneticAlgo() {}

GeneticAlgo::GeneticAlgo() {
    graph.loadData();
    graph.loadCosts();
    crossingRate = 0;
    mutationRate = 0;
    selectionRate = 0;
    lastGeneration = 0;
    typeSelection = 0;
    typeCrossing = 0;
    typeMutation = 0;
    mutationValue = 0;

}

void GeneticAlgo::HamiltonianCircuit() {
    cout << "Genetic Algorithm " << endl;

    start = chrono::high_resolution_clock::now();

    initializeSelection(1,30);  //
    initializeGeneration(100);
    initializeCrossOver(0,50);
    initializeMutations(3,1,6);
    setPopulation(5);
     selecting_num = oldPopulation.size() * (selectionRate / 100);
     crossing_num = oldPopulation.size() * (crossingRate / 100);

    int selecting_nums = 1;
    int crossing_nums = 0;

//    cout << "Selection num: " << selecting_num << endl;
//    cout << "Crossing num: " << crossing_num << endl;

    for(mutationValue = 0; mutationValue < lastGeneration; mutationValue++){
        selection(selecting_nums);
        crossOver(crossing_nums);
        switchMutations();
        mutate(1);
        bestPath();
        oldPopulation = newPopulation;
        if(newPopulation.size() > 0){
            newPopulation.clear();
        }


    }

    cout << "Total distance: " << population.first << endl;
    for(int i = 0; i < population.second.size(); i++){
        cout << population.second[i] +1 << " -> ";
    }

}

void GeneticAlgo::initializeGeneration(int gen) {

    lastGeneration = gen;
}

void GeneticAlgo::initializeMutations(int mut, int swap, int per) {

    typeMutation = mut;
    mutationValue = swap;
    mutationRate = per;
}

void GeneticAlgo::initializeSelection(int sel, int per) {

    typeSelection = sel;
    selectionRate =  per;

}

void GeneticAlgo::initializeCrossOver(int cross, int per) {

    typeCrossing = cross;
    crossingRate = per;
}

void GeneticAlgo::setPopulation(int popu) {

    vector<int> temp;

    int length = graph.getCosts().size();

    for(int i = 0; i < length; i++ ){
        temp.push_back(i);
    }

    for(int i = 0; i < length * popu;i++) {

       std::random_shuffle(temp.begin()+1, temp.end()-1);
        oldPopulation.push_back(make_pair(bestFitness(temp), temp));
    }

        population = oldPopulation[0];
        bestPath();
        mutationRate = mutationRate / 100;

}

void GeneticAlgo::selection(int types) {

    switch (types){
        case 0:
         //   cout << "Elite selection \n";
            selectElite(selecting_num);
            break;
        case 1:
         //   cout << "Roulette selection \n";
            selectRoulette(selecting_num);
            break;
        default:
           cout << "invalid input try 1 or 0 \n";

    }
}

void GeneticAlgo::crossOver(int types) {

    switch (types){
        case 0:
           // cout << "single crossover \n";
            singleCrossOver(crossing_num);
            break;
        case 1:
          //  cout << "multi crossover \n";
            multiCrossOver(crossing_num);
            break;
        default:
            cout << "invalid input try 1 or 0 \n";

    }
}

void GeneticAlgo::selectElite(int num) {

    vector<pair<double, vector<int> > > temp = oldPopulation ;
    sort(temp.begin(), temp.end());
    for(int i = 0;i < num; i++){
        newPopulation.push_back(temp[i]);
    }
}

void GeneticAlgo::selectRoulette(int num) {

    vector<int> temp;
    int sum = 0, val = 0;


    for(int i = 0; i < oldPopulation.size(); i++){
        sum = sum + bestFitness(oldPopulation[i].second);
    }

    for(int i = 0; i < oldPopulation.size();i++){
        int tem = oldPopulation[i].first / sum;
        val = val + tem;
        temp.push_back(val);
    }

    int j = 0;
    while(num > newPopulation.size()){

        random_device seed;
        default_random_engine randi(seed());
        uniform_real_distribution<double> distri(0,1);
        double var = distri(randi);
        if(var > temp[j]){
            newPopulation.push_back(oldPopulation[j]);
        }
        j++;
        if(j == temp.size()){
            j = 0;
        }


    }

}

void GeneticAlgo::singleCrossOver(int num) {

    vector<int> firstChild, secondChild;

  //  cout << "Old population in Single CrossOver: " << oldPopulation[0].second.size() << endl;

    random_device seed;
    mt19937 randy(seed());
    uniform_int_distribution<int> range(0, oldPopulation.size() - 1);
    int mid = (oldPopulation[0].second.size() / 2) - 1;


    for(int i = 0; i < oldPopulation[0].second.size(); i++){
        firstChild.push_back(0);
        secondChild.push_back(0);
    }

    int iter = 0;

    while(iter < num){

        int firstParent = range(randy);
        int secondParent = range(randy);
        int firstChil = 1;
        int secondChil = 1;

        for(int i = 1; i<= mid; i++ ){
            firstChild[firstChil++] = oldPopulation[firstParent].second[i];
            secondChild[secondChil++] = oldPopulation[secondParent].second[i];
        }
        for(int j = 1; j < oldPopulation[0].second.size()-1; j++){
            bool first = false;
            bool second = false;
            for(int k = 0; k <= mid; k++ ){
                if(oldPopulation[firstParent].second[j] == secondChild[k]){
                    first = true;
                }
                if(oldPopulation[secondParent].second[j] == firstChild[k]){
                    second = true;
                }
            }
            if(!first){
                secondChild[secondChil++] = oldPopulation[firstParent].second[j];
            }
            if(!second){
                firstChild[firstChil++] = oldPopulation[secondParent].second[j];
            }

        }
        newPopulation.push_back(make_pair(bestFitness(firstChild), firstChild));
        iter = iter + 1;

        if(num > iter ){
            newPopulation.push_back(make_pair(bestFitness(secondChild), secondChild));
            iter++;
        }
    }

}

void GeneticAlgo::multiCrossOver(int num) {

    vector<int> firstChild, secondChild;
    int crossings = graph.loadData().size() * 0.25 ;

    random_device seed;
    mt19937 randy(seed());
    uniform_int_distribution<int> range(0, oldPopulation.size() - 1);
    uniform_int_distribution<int> rangeChromosome(1, graph.loadData().size() - crossings);

    for(int i = 0; i < oldPopulation[0].second.size(); i++){
        firstChild.push_back(0);
        secondChild.push_back(0);
    }

    int iter = 0;
    int begins = rangeChromosome(randy);
    int ends = begins + crossings - 1  ;

    while(iter < num){

        int firstParent = range(randy);
        int secondParent = range(randy);
        int firstChil = 1;
        int secondChil = 1;

        for(int j = 1; j < oldPopulation[0].second.size()-1; j++) {
            bool first = false;
            bool second = false;
            for (int k = begins; k <= ends; k++) {
                if (oldPopulation[firstParent].second[j] == secondChild[k]) {
                    first = true;
                }
                if (oldPopulation[secondParent].second[j] == firstChild[k]) {
                    second = true;
                }
            }

            if(firstChil == begins){
                firstChil = 1 + firstChil + ends - begins;
            }
            if(secondChil == begins){
                secondChil = 1 + secondChil + ends - begins;
            }
            if(!first){
                secondChild[secondChil++] = oldPopulation[firstParent].second[j];
            }
            if(!second){
                firstChild[firstChil++] = oldPopulation[secondParent].second[j];
            }

        }

        for(int i = 0; i<= ends - begins; i++ ){
            firstChild[begins +i] = oldPopulation[firstParent].second[begins +i];
            secondChild[begins +i] = oldPopulation[secondParent].second[begins +i];
        }

        newPopulation.push_back(make_pair(bestFitness(firstChild), firstChild));
        iter = iter + 1;

        if(num > iter ){
            newPopulation.push_back(make_pair(bestFitness(secondChild), secondChild));
            iter++;
        }
    }
}

void GeneticAlgo::bestPath() {

    pair<double, vector<int> > best = oldPopulation[0];

    for(int j = 1; j < oldPopulation.size(); j++){
        if(best.first > oldPopulation[j].first){
            best = oldPopulation[j];
        }
    }

   if(population.first > best.first){
       population = best;
     //  end = chrono::high_resolution_clock::now();
//       cout << "Shortest distance " << population.first << endl;
//       for(int i = 0; i < population.second.size(); i++){
//           cout << population.second[i] + 1 << " ->";
//       }
//       cout << "Time: ";
//       chrono::duration<double> time_t = chrono::duration_cast<chrono::duration<double> >(end - start);
//       cout << time_t.count() << endl;

   }
}

int GeneticAlgo::bestFitness(vector<int> route) {
    int total = 0;
    for(int i = 0; i < route.size()-1; i++){
        total = total + graph.getCosts()[route[i]][route[i+1]];
    }

    return total;
}

void GeneticAlgo::switchMutations() {

    int num = mutationRate * oldPopulation.size();
    random_device seed;
    default_random_engine randi(seed());
    uniform_real_distribution<double> distribute(0, oldPopulation.size()) ;
    uniform_int_distribution<int> range(1, oldPopulation[0].second.size()-2) ;


    while(num > 0){

        int randomy = distribute(randi);
        for(int i = 0; i < mutationValue; i++){
            int one = range(randi);
            int two = range(randi);
            int temp  = newPopulation[randomy].second[one];
            newPopulation[randomy].second[one] = newPopulation[randomy].second[two];
            newPopulation[randomy].second[two] = temp;

        }
        num--;

    }
}

void GeneticAlgo::mutate(int num) {

    switch (num){
        case 1:
            //cout << "Switching Mutations \n";
            switchMutations();
    }
}




