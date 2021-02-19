#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class State {
    private:
        vector< vector<int> > gridState;
        /*
        State* upChild;
        State* downChild;
        State* leftChild;
        State* rightChild;*/

    public:
        State* upChild;
        State* downChild;
        State* leftChild;
        State* rightChild;
        int f_n;
        int g_n;
        int h_n;
        State(vector<vector <int> > &gState): gridState(gState){upChild = 0; downChild = 0; leftChild = 0; rightChild = 0; f_n = 0; g_n = 0; h_n = 0;};

        vector< vector<int> > getGrid() { return this->gridState; }
        
        //~State(); --> not sure if need destructor yet
};

#endif