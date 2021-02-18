#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class State {
    private:
        vector< vector<int>> gridState;
        State* upChild;
        State* downChild;
        State* leftChild;
        State* rightChild;

    public:
        State(vector<vector <int>> gState);
        //State(); --> not sure if needed yet
};

#endif