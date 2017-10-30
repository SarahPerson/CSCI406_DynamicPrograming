#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

// Variables
vector<int> x = { 10,1,7,7 };
vector<int> s = { 8,4,2,1 };
vector<int> p;
stack<bool> resetDays;
int t = 0;
const int NORESET = 0;
const int RESET = 1;

// functions
int ProcessData(int day, int rday);
void PrintStack(stack<bool> stk);

int main() {
    int result = ProcessData(0, 0);
    cout << result<<endl;

}

int ProcessData(int day, int rday) {
    int option[2]; // cost of the two options
    int most_processed;
    int today = min(x.at(day), s.at(rday)); // getting the amount to be processed on current day

    // return if at last day in the cycle
    if (day == x.size() - 1) {
        return min(x.at(day), s.at(rday));
    }

    // Call recursion  on both cases whether system is reset or not reset
    option[NORESET] = ProcessData(day + 1, rday + 1) + today;
    option[RESET] = ProcessData(day + 1, 0);

    // return the case that processes the most data
    most_processed = option[NORESET];
    if (option[RESET] > most_processed){
        most_processed = option[RESET];
    }

    return most_processed;

}

