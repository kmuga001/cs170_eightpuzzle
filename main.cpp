#include <iostream>
#include <string>
#include <vector>
//#include "state.h"
using namespace std;

void displayGridState(vector <vector<int> > state);

int main() {
    /*
    First introduce problem and explain how to input
    Second - Get input and put it into vector --> initial state
    Third - Display Grid
    Fourth - Create an object (Node - Status) (need to create a struct - h file)
    */
    vector< vector<int> > initial_state;
    vector<int> row_1;
    vector<int> row_2;
    vector<int> row_3; 
    cout << "Welcome to the 8-Puzzle Solver: " << endl;
    //cout << "Type 1 to use a default puzzle, or 2 to enter your own puzzle" << endl;
    
    for(int i = 0; i < 9; i++) {
        int val = 0;
        cout << "Enter a number for your puzzle, please use 0 to represent a blank space: ";
        cin >> val;
        cout << endl;
        if(i < 3) {
            row_1.push_back(val);
        } else if(i < 6){
            row_2.push_back(val);
        } else {
            row_3.push_back(val);
        }
    }

    initial_state.push_back(row_1);
    initial_state.push_back(row_2);
    initial_state.push_back(row_3);
    
    displayGridState(initial_state);
    

    return 0;
}


//displaying the current puzzle state based on whatever is inputted (may need to replace with object)
void displayGridState(vector <vector<int> > state) {
    
    for(int i = 0; i < state.size(); i++){
        for(int j = 0; j < state[i].size(); j++){
            cout << " " << state[i].at(j);
        }
        cout << endl;
    }

}
