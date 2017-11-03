#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
#include "Cell.h"

using namespace std;

// Variables
const int N = 10;
vector<int> x = { 20,80,20,60,20,60,80,10,40,10};
vector<int> s = { 100,90,50,45,40,35,20,15,10,5 };
vector<int> p;

const int NORESET = 0;
const int RESET = 1;

vector<vector<Cell>> solutions(x.size(),vector<Cell>(s.size(),Cell()));

// functions
int Recursive_ProcessData(int day, int rday);
int Dynamic_ProcessData(int day, int rday);
void Traceback(int day, int rday, int increment);

int main() {
    int result = Recursive_ProcessData(0, 0);
    cout << result<<endl;

    int rows = N;
    int cols = N;
    //initialize vector
    cout << "Initial Partial Vector" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << solutions[i][j].dataProcessed << " ";
        }
        cout << endl;
    }

    result = Dynamic_ProcessData(0, 0);
    cout << result << endl;
    cout << "Final Partial Vector" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << solutions[i][j].dataProcessed << " ";
        }
        cout << endl;
    }
    //Traceback
    cout << "Traceback" << endl;
    Traceback(0, 0, 0);
    /*
    for (int i = 0; i < days_result.size(); i++) {
        cout << days_result[i] << " " ;
    }
    */
}

int Recursive_ProcessData(int day, int rday) {
    int option[2]; // cost of the two options
    int most_processed;
    int today = min(x.at(day), s.at(rday)); // getting the amount to be processed on current day

    // return if at last day in the cycle
    if (day == x.size() - 1) {
        return min(x.at(day), s.at(rday));
    }

    // Call recursion  on both cases whether system is reset or not reset
    option[NORESET] = Recursive_ProcessData(day + 1, rday + 1) + today;
    option[RESET] = Recursive_ProcessData(day + 1, 0);

    // return the case that processes the most data
    most_processed = option[NORESET];
    if (option[RESET] > most_processed){
        most_processed = option[RESET];
    }

    return most_processed;

}

int Dynamic_ProcessData(int day, int rday) {
    if (solutions[day][rday].dataProcessed > -1)
        return solutions[day][rday].dataProcessed;

    int option[2]; // cost of the two options
    int most_processed;
    int today = min(x.at(day), s.at(rday)); // getting the amount to be processed on current day

    // return if at last day in the cycle
    if (day == x.size() - 1) {
        most_processed = min(x.at(day), s.at(rday));
        solutions[day][rday].dataProcessed = most_processed;
        return most_processed;
    }

    // Call recursion  on both cases whether system is reset or not reset
    option[NORESET] = Dynamic_ProcessData(day + 1, rday + 1) + today;
    option[RESET] = Dynamic_ProcessData(day + 1, 0);

    // return the case that processes the most data
    most_processed = option[NORESET];
    solutions[day][rday].child = &solutions[day + 1][rday + 1];

    if (option[RESET] > most_processed) {
        most_processed = option[RESET];
        solutions[day][rday].child = &solutions[day + 1][0];
    }

    solutions[day][rday].dataProcessed = most_processed;

    return most_processed;

}

// Print out the optimized results of each days output
void Traceback(int day, int rday, int increment) {
    //start at the cell with the final solution
    Cell currentcell = solutions[0][0];
    int final = solutions[0][0].dataProcessed;

    //Create vector to hold each days step
    vector<int> steps;

    //Follow each child pointer  
    while (currentcell.child != nullptr) {
        Cell temp = *currentcell.child;
        //put the difference between the total data processed and the child day
        steps.push_back(currentcell.dataProcessed - temp.dataProcessed);
        currentcell = *currentcell.child;
    }
    // add the final days data processed
    steps.push_back(currentcell.dataProcessed);
    // output total amount of data processed
    cout << final << endl;
    // output each days data processed
    for (int i = 0; i < steps.size(); i++) {
        cout << steps.at(i) << " ";
    }

}

