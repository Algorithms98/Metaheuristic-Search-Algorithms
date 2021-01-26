//
// Created by PRINCE NDHLOVU on 11/26/20.
//

#include "SelectAlgo.h"

SelectAlgo::SelectAlgo() = default;

SelectAlgo::~SelectAlgo() = default;

Algorithm* SelectAlgo::Technique(int num) {
    Algorithm * algo = nullptr;

    switch(num){
        case 1:
            algo = new TSP();
            return algo;
        default:
            cout << "Invalid argument passed in Technique for SelectAlgo, returned null ptr \n";
            return nullptr;

    }

}
