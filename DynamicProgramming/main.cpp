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
vector<int> x = { 10,1,7,7 };
vector<int> s = { 8,4,2,1 };
vector<int> p;
stack<bool> resetDays;
int t = 0;
const int NORESET = 0;
const int RESET = 1;

vector<vector<Cell>> solutions(x.size(),vector<Cell>(s.size(),Cell()));

// functions
int Recursive_ProcessData(int day, int rday);

int Dynamic_ProcessData(int day, int rday);

int main() {
    int result = Recursive_ProcessData(0, 0);
    cout << result<<endl;

    int rows = x.size();
    int cols = s.size();
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
        return min(x.at(day), s.at(rday));
    }

    // Call recursion  on both cases whether system is reset or not reset
    option[NORESET] = Dynamic_ProcessData(day + 1, rday + 1) + today;
    option[RESET] = Dynamic_ProcessData(day + 1, 0);

    // return the case that processes the most data
    most_processed = option[NORESET];
    if (option[RESET] > most_processed) {
        most_processed = option[RESET];
    }

    solutions[day][rday].dataProcessed = most_processed;

    return most_processed;

}
