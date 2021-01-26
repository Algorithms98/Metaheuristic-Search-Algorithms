//
// Created by PRINCE NDHLOVU on 11/26/20.
//

#include "FileLoader.h"

FileLoader::FileLoader() = default;

//reading in the positions.txt file
unordered_map<int, vector<int> > FileLoader::loadData() {

   // ifstream positionFile("/Users/princendhlovu/Desktop/lab-3-dynamic-programming-Algorithms98/Data/Graph/positions.txt");
    ifstream positionFile("/Users/princendhlovu/Desktop/lab-4-heuristic-search-Algorithms98/Data/Graph/positions.txt");

    if(!positionFile.is_open()){
        cout << "Could not open position file in FileLoader.cpp \n";
        return position_nodes;
    }
    vector<int> data, temp_data;
    string line, temp;

    while(!positionFile.eof()){

        getline(positionFile, line);
        stringstream ss(line);

        while(ss){
            if(!getline(ss, temp, ',')){
                break;
            }
            int put = stoi(temp);
            data.push_back(put);
        }

        for(int j = 1; j < 4; j++){
            temp_data.push_back(data[j]);
        }

        position_nodes.insert(make_pair(data[0]-1, temp_data));
        // position_nodes[data[0]-1] = temp_data;
        temp_data.clear();
        data.clear();
    }
    positionFile.close();
    return position_nodes;
}

void FileLoader::loadCosts() {

    for(int i =0; i < position_nodes.size(); i++){
        costs.push_back(vector<int>(position_nodes.size(), 0));
    }

    for(int j = 0; j < position_nodes.size(); j++){
        for(int k = 0; k < position_nodes.size(); k++){
            costs[j][k] = distanceX(j,k);
            costs[k][j] = distanceX(k,j);

        }
    }
}

int FileLoader::distanceX(int start, int stop) {

    int tempX = 0;

    tempX += pow((position_nodes[start].at(0) - position_nodes[stop].at(0)), 2);
    tempX += pow((position_nodes[start].at(1) - position_nodes[stop].at(1)), 2);
    tempX += pow((position_nodes[start].at(2) - position_nodes[stop].at(2)), 2);

    return sqrt(tempX);

}

vector <vector<int>> FileLoader::getCosts() {
    return costs;
}
