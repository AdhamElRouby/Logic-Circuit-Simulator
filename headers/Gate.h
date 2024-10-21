#ifndef GATE
#define GATE
#include <string>
#include <map>
#include <vector>
#include "../headers/Simulation.h"
class Gate {
    private:
    string operationType;  //and,or,not.......
    vector<string> inputs;
    string output;
    int delay;
    public:
    Gate(string type,vector<string> i,string o,int d); //operatinType,inputs,output,delay //when you construct a gate please make a vector of the inputs names
    int evaluate(); //function to calcualte the current output of the gate
    int getOutput(); //getter for the output
};



#endif
