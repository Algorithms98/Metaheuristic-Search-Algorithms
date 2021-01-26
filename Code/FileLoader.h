//
// Created by PRINCE NDHLOVU on 11/26/20.
//

#ifndef CODE_FILELOADER_H
#define CODE_FILELOADER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;


class FileLoader {

private:
    unordered_map<int, vector<int>> position_nodes;
    vector< vector <int> > costs;

public:
    FileLoader();
    unordered_map<int, vector<int>> loadData();
    vector< vector <int> > getCosts();
    void loadCosts();
    int distanceX(int,int);

};


#endif //CODE_FILELOADER_H
