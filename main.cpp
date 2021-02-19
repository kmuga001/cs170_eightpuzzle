#include <iostream>
#include <string>
#include <vector>
#include <queue> 
#include "state.h"
using namespace std;

void displayGridState(vector <vector<int> > state);
State* moveUp_State(State* stateNode);
State* moveDown_State(State* stateNode);
State* moveLeft_State(State* stateNode);
State* moveRight_State(State* stateNode);
vector<int> getZeroPosition(vector <vector<int> > state);
bool meetGoalState(State* stateNode);
State* general_search(State* initialState); //for uniform cost search atm
queue<State*> queueChildren(State* currentNode, queue<State*> nodes_queue);


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

    State* initState = new State(initial_state);
    //cout << initState->getGrid() << endl;
    vector< vector<int> > temp = initState->getGrid();

    State* solutionNode = general_search(initState);
    if(solutionNode->getGrid().size() < 3){
        cout << "FAILURE - NO SOLUTION" << endl;
    } else {
        cout << "YAY - FOUND SOLUTION: " << endl;
        displayGridState(solutionNode->getGrid());
    }


    

    /*checking if player can move
    State* check = moveRight_State(initState);
    cout << endl << endl;
    if(check->rightChild == 0) {
        cout << "no child, so no grid" << endl;
    } else {
        displayGridState((check->rightChild)->getGrid());
    }*/
    

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
    cout << endl;

}


//uniform cost search for now --> because cost for each operation is the same, this is a BFS
//using a queue structure bc we just want a fifo method to check root node first
State* general_search(State* initialState) {
    //following project guideline pseudocode
    queue <State*> nodes_queue;
    nodes_queue.push(initialState); //add initial state of puzzle
    string str = "in progress";
    do{
        if(nodes_queue.empty()){ //failure because queue is empty, no solution found
            string str = "failure";
            break; //leave the do while loop
        }
        State* currentNode = nodes_queue.front();
        displayGridState(currentNode->getGrid());

        if(meetGoalState(currentNode) == true) { //check if currentnode is the answer
            return currentNode;
        } else {
            //nodes_queue = queuefunction(get its children by moving & put it in queue)
            nodes_queue = queueChildren(currentNode, nodes_queue);
            nodes_queue.pop();
        }


    } while(!nodes_queue.empty());


    vector <vector<int> > failedGrid;
    vector<int> failV;
    failV.push_back(0); //then, in main function, i can check the vector size and see that it failed - no solution
    State* failedState = new State(failedGrid);
    
    return failedState;
}


//expand to children part of general search
/*first: get each child node from 4 movement functions
second: check if each child is not null, if it is, then don't add to queue
third: return queue of nodes
*/
queue<State*> queueChildren(State* currentNode, queue<State*> nodes_queue){
    currentNode = moveUp_State(currentNode);
    currentNode = moveDown_State(currentNode);
    currentNode = moveLeft_State(currentNode);
    currentNode = moveRight_State(currentNode);

    
    if(currentNode->upChild != 0){
        nodes_queue.push(currentNode->upChild);
    }

    
    if(currentNode->downChild != 0){
        nodes_queue.push(currentNode->downChild);
    }

    
    if(currentNode->leftChild != 0){
        nodes_queue.push(currentNode->leftChild);
    }

    
    if(currentNode->rightChild != 0){
        nodes_queue.push(currentNode->rightChild);
    }

    return nodes_queue;

}


bool meetGoalState(State* stateNode) {
    //first create a goal grid to compare stateNode to it
    vector< vector<int> > stateGrid = stateNode->getGrid();

    vector <vector<int> > goalGrid;
    vector<int> row_1;
    vector<int> row_2;
    vector<int> row_3; 
    row_1.push_back(1);
    row_1.push_back(2);
    row_1.push_back(3);
    row_2.push_back(4);
    row_2.push_back(5);
    row_2.push_back(6);
    row_3.push_back(7);
    row_3.push_back(8);
    row_3.push_back(0);
    goalGrid.push_back(row_1);
    goalGrid.push_back(row_2);
    goalGrid.push_back(row_3);

    for(int i = 0; i < goalGrid.size(); i++){
        for(int j = 0; j < goalGrid[i].size(); j++){
            if(stateGrid[i][j] != goalGrid[i][j]){
                return false;
            }
        }
    }

    return true;


}



vector<int> getZeroPosition(vector <vector<int> > state) {
    vector<int> ind;
    for(int i = 0; i < state.size(); i++){
        for(int j = 0; j < state[i].size(); ++j){
            if(state[i][j] == 0){
                ind.push_back(i);
                ind.push_back(j);
                
                return ind;
            }
        }
    }
    
    ind.push_back(10);
    ind.push_back(10);
    return ind;
}

State* moveUp_State(State* stateNode) {
    vector<int> ind = getZeroPosition(stateNode->getGrid());
    
    //cout << ind[0] << ", " << ind[1] << endl;
    if(ind[0] == 10 && ind[1] == 10) {
        cout << "Could not find 0" << endl; //is an error, address later
        
    } 

    //cannot move up if 0 is on the top row (which is row = 0)
    if(ind[0] == 0) { //is on the top row, 0 can't move
        cout << "CAN'T MOVE UP" << endl;
        //leave statenode's upchild as null in default because it can't move up
    } else {
        //it can move up and so we can make a new grid and state object
        //use same grid from parameter and copy it over
        //swap 0 with position above
        vector< vector<int> > newMoveGrid = stateNode->getGrid();
        int temp = newMoveGrid[ind[0]][ind[1]]; //0's position
        newMoveGrid[ind[0]][ind[1]] = newMoveGrid[ind[0] - 1][ind[1]];
        newMoveGrid[ind[0] - 1][ind[1]] = temp;

        //create a new State object with this new created grid after making move
        State* upGrid = new State(newMoveGrid);
        stateNode->upChild = upGrid;

    }

    return stateNode;
    
}


State* moveDown_State(State* stateNode) {
    vector<int> ind = getZeroPosition(stateNode->getGrid());
    
    //cout << ind[0] << ", " << ind[1] << endl;
    if(ind[0] == 10 && ind[1] == 10) {
        cout << "Could not find 0" << endl; //is an error, address later
        
    } 

    //cannot move down if 0 is on the bottom row (which is row = 2)
    if(ind[0] == 2) { //is on the bottom row, 0 can't move
        cout << "CAN'T MOVE DOWN" << endl;
        //leave statenode's downchild as null in default because it can't move down
    } else {
        //it can move down and so we can make a new grid and state object
        //use same grid from parameter and copy it over
        //swap 0 with position below
        vector< vector<int> > newMoveGrid = stateNode->getGrid();
        int temp = newMoveGrid[ind[0]][ind[1]]; //0's position
        newMoveGrid[ind[0]][ind[1]] = newMoveGrid[ind[0] + 1][ind[1]];
        newMoveGrid[ind[0] + 1][ind[1]] = temp;

        //create a new State object with this new created grid after making move
        State* downGrid = new State(newMoveGrid);
        stateNode->downChild = downGrid;

    }

    return stateNode;
}

State* moveLeft_State(State* stateNode) {
    vector<int> ind = getZeroPosition(stateNode->getGrid());
    
    //cout << ind[0] << ", " << ind[1] << endl;
    if(ind[0] == 10 && ind[1] == 10) {
        cout << "Could not find 0" << endl; //is an error, address later
        
    } 

    //cannot move left if 0 is on the first column (col = 0)
    if(ind[1] == 0) { //is on the first col, 0 can't move
        cout << "CAN'T MOVE LEFT" << endl;
        //leave statenode's leftchild as null in default because it can't move left
    } else {
        //it can move left and so we can make a new grid and state object
        //use same grid from parameter and copy it over
        //swap 0 with position to the left
        vector< vector<int> > newMoveGrid = stateNode->getGrid();
        int temp = newMoveGrid[ind[0]][ind[1]]; //0's position
        newMoveGrid[ind[0]][ind[1]] = newMoveGrid[ind[0]][ind[1] - 1];
        newMoveGrid[ind[0]][ind[1] - 1] = temp;

        //create a new State object with this new created grid after making move
        State* leftGrid = new State(newMoveGrid);
        stateNode->leftChild = leftGrid;

    }

    return stateNode;
}

State* moveRight_State(State* stateNode) {
    vector<int> ind = getZeroPosition(stateNode->getGrid());
    
    //cout << ind[0] << ", " << ind[1] << endl;
    if(ind[0] == 10 && ind[1] == 10) {
        cout << "Could not find 0" << endl; //is an error, address later
        
    } 

    //cannot move right if 0 is on the third column (col = 2)
    if(ind[1] == 2) { //is on the first col, 0 can't move
        cout << "CAN'T MOVE RIGHT" << endl;
        //leave statenode's rightchild as null in default because it can't move right
    } else {
        //it can move right and so we can make a new grid and state object
        //use same grid from parameter and copy it over
        //swap 0 with position to the right
        vector< vector<int> > newMoveGrid = stateNode->getGrid();
        int temp = newMoveGrid[ind[0]][ind[1]]; //0's position
        newMoveGrid[ind[0]][ind[1]] = newMoveGrid[ind[0]][ind[1] + 1];
        newMoveGrid[ind[0]][ind[1] + 1] = temp;

        //create a new State object with this new created grid after making move
        State* rightGrid = new State(newMoveGrid);
        stateNode->rightChild = rightGrid;

    }

    return stateNode;
}