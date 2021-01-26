//
// Created by PRINCE NDHLOVU on 11/26/20.
//

#include "TSP.h"

TSP::TSP() {

}

TSP* TSP::Select(int num) {
    algo = num;
    return this;
}

void TSP::Execute() {



    begin = chrono::high_resolution_clock::now();

//    switch(algo){
//        case 1:
//            HamiltonianCircuit pathObj;
//            pathObj.Dynamic();
//            break;
//        case 2:
//            HamiltonianCircuit pathObj;
//            pathObj.BruteForce();
//            break;
//        case 3:
//            GeneticAlgo obj;
//            obj.HamiltonianCircuit();
//            break;
//        case 4:
//            SimulatedAnnealingAlgo obje;
//            obje.HamiltonianCircuit();
//            break;
//        default:
//            cout << "Not a valid int \n";
//            break;
//    }

    if(algo == 1){
        HamiltonianCircuit pathObj;
        pathObj.Dynamic();
    }else if(algo == 2){
        HamiltonianCircuit pathObj;
        pathObj.BruteForce();
    }else if(algo == 3){
        GeneticAlgo obj;
        obj.HamiltonianCircuit();
    }else if(algo == 4){
        SimulatedAnnealingAlgo obje;
        obje.HamiltonianCircuit();
    }else{
        cout << "Not a valid int \n";
    }

    end = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<std::chrono::duration<double>>(end - begin);
    cout << "Execution time: " << time.count() << endl;
    cout << endl;

}
