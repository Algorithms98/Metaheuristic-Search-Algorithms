//
// Created by PRINCE NDHLOVU on 12/5/20.
//

#include "HamiltonianCircuit.h"

HamiltonianCircuit::HamiltonianCircuit() {
    FileLoader obj;
    map_nodes = obj.loadData();
    LoadGraph();
    DisplayGraph();
    CountPaths();
    pathSum = 1;
    shortPath = 0;
}

HamiltonianCircuit::~HamiltonianCircuit() = default;

void HamiltonianCircuit::BruteForce() {

    vector<int> path;
    int recursiveCalls = 0;
    vector<bool> seen(map_nodes.size(), false);
    seen[0] = true;
    BruteForceRecursive(path, recursiveCalls, seen,0,0 );
    FindDistance();
    DisplayShortestPath();

    cout << "Number of function calls: " << recursiveCalls << endl;
}

void HamiltonianCircuit::Dynamic() {

    int dynamicCalls = 0;

    vector<int> id;

    for(int i = 0; i < map_nodes.size(); i++){
        id.push_back(i);
    }

    pair<int, vector<int> > path = DynamicRecursive(id, dynamicCalls, 0,0,0);

    cout << "Route found using Dynamic Programming \n";

    for(int j = path.second.size()-1; j >0; j-- ){
        cout << path.second[j] + 1 <<" -> ";

    }

    cout << endl;
    cout << "Total distance: " << path.first << endl;
    cout << "Number of function calls: " << dynamicCalls << endl;

}

void HamiltonianCircuit::BruteForceRecursive(vector<int> path, int&  calls, vector<bool> seen, int start, int idx) {

    calls++;
    path.push_back(idx);
    seen[idx] = true;

    if(Visited(seen)){
        path.push_back(start);
        totalPaths.push_back(path);
        path.pop_back();
        return;
    }

    for(int i = 0; i < seen.size(); i++){
        if(seen[i] == false){
            if(totalPaths.size() == pathSum){
                return;
            }
            BruteForceRecursive(path,calls, seen, start,i);
            path.pop_back();
        }
    }
}

pair<int, vector<int> > HamiltonianCircuit::DynamicRecursive(vector<int> path, int & calls, int start, int link, int idx) {
    calls++;

    vector<int> track;
    pair<int, vector<int> > currPath;
    int curr_dist;
    int distance = INT_MAX;
    path.erase(path.begin() + idx);

    if(path.size() == 1){
        track.push_back(link);
        track.push_back(path[0]);
        currPath = make_pair(totalCost[link][path[0]] + totalCost[path[0]][start], track );
        return currPath;
    }

    for(int i = 0; i < path.size(); i++){
        currPath = DynamicRecursive(path, calls, start, path[i], i);
        curr_dist = totalCost[link][path[i]] + currPath.first;

        if(curr_dist < distance){
            distance = curr_dist;
            currPath.second.push_back(path[i]);
            track = currPath.second;
        }

    }
    return make_pair(distance, track);
}

void HamiltonianCircuit::DisplayShortestPath() {

    cout << "Route found using Naive BruteForce:  \n";

    for(int i = 0; i < totalPaths[shortPath].size()-1; i++ ){
        cout << totalPaths[shortPath][i] + 1 << " ";
        if(i != totalPaths[shortPath].size()-2){
            cout << "-> ";
        }
    }
    cout << endl;
    cout << "Total distance: " << sqrt(totalPaths[shortPath][totalPaths[shortPath].size() - 1]) << endl;

}

bool HamiltonianCircuit::Visited(vector<bool> & seen) {

    for(int i = 0; i < seen.size(); i++ ){
        if(seen[i] == false){
            return false;
        }
    }
    return true;
}

double HamiltonianCircuit::CalculateDistances(int first, int second) {

    double total = 0;

    total += pow((map_nodes[first].at(0) - map_nodes[second].at(0)), 2);
    total += pow((map_nodes[first].at(1) - map_nodes[second].at(1)), 2);
    total += pow((map_nodes[first].at(2) - map_nodes[second].at(2)), 2);
    total = sqrt(total);

    return total;
}

void HamiltonianCircuit::DisplayGraph() {

    cout << "Displaying the graph values \n";

    for(int i = 0; i < map_nodes.size();i++){
        for(int j = 0; j < map_nodes.size(); j++){
            cout << totalCost[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void HamiltonianCircuit::CountPaths() {

    pathSum = 1;
    for(int j = map_nodes.size() - 1; j > 0; j--){
        pathSum = pathSum * j;
    }

    pathSum = pathSum / 2;
}

void HamiltonianCircuit::LoadGraph() {

    for(int j = 0; j < map_nodes.size(); j++){
        totalCost.push_back(vector<int>(map_nodes.size(), 0));
    }

    for(int j = 0 ; j < map_nodes.size(); j++){
        for(int k = j; k < map_nodes.size(); k++){
            totalCost[j][k] = CalculateDistances(j,k);
            totalCost[k][j] = CalculateDistances(j,k);

        }
    }
}

void HamiltonianCircuit::FindDistance() {

    double temp = 0.0;
    shortPath = 0;

    for(int j = 0; j < totalPaths.size(); j++){

        for(int k = 0; k < totalPaths[k].size(); k++){
            temp += CalculateDistances(totalPaths[j][k], totalPaths[j][k+1]);
        }
        totalPaths[j].push_back(temp);

        if(totalPaths[j][totalPaths[j].size() - 1] < totalPaths[shortPath][totalPaths[shortPath].size() - 1]){
            shortPath = j;
        }
        temp = 0.0;
    }
}