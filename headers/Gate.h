#ifndef GATE
#define GATE

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Gate {
  private:
    string operationType; // and,or,not.......
    vector<string> inputs;
    string output;
    int delay;

  public:
    Gate(string type, vector<string> i, string o,
         int d); // operatinType,inputs,output,delay //when you construct a gate
                 // please make a vector of the inputs names
    int evaluate();  // function to calcualte the current output of the gate
    int getOutput(); // getter for the output
    string getOutputName(); // getter for the output name
    int getDelay();         // getter for the delay
};

#endif
