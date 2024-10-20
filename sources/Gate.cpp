#include "../headers/Gate.h"
Gate::Gate(string type,vector<string> i,string o,int d):operationType(type),inputs(i),output(o),delay(d){}
int Gate::evaluate() {  
    // Check if any input is invalid and return invalid 
    for (int i = 0; i < inputs.size(); ++i) {
        if (inputs[i] == "-999") {
            return -999;  // invalid
        }
    }

    // Evaluate based on operationType
    if (operationType == "or") {
        // or: result is true if any input value is true
        bool result = false;
        for (int i = 0; i < inputs.size(); ++i) {
            result = result || mp[inputs[i]];  // update the result one by one from the inputs
        }
        return result;
    }
      else if (operationType == "and") {
        // and: result is true if all inputs are true
        bool result = true;
        for (int i = 0; i < inputs.size(); ++i) {
            result = result && mp[inputs[i]];  // update the result one by one from the inputs
        }
        return result;
    }
    else if (operationType == "not") {
        // not: only valid with one input, result is the inverse of the input
        if (inputs.size() == 1) {
            return !mp[inputs[0]];  // NOT operation
        }
        cout<<"A not gate has more than one input";
        return -999;  // invalid if not a single input
    }
    else if (operationType == "xor") {
        // xor: result is true if an odd number of inputs are true
        bool result = false;
        for (int i = 0; i < inputs.size(); ++i) {
            result = result != mp[inputs[i]];  // update the result one by one from the inputs
        }
        return result;
    }
    else if (operationType == "xnor") {
        // xnor: result is true if an even number of inputs are true (inverse of XOR)
        bool result = false;
        for (int i = 0; i < inputs.size(); ++i) {
            result = result != mp[inputs[i]];  // XOR operation
        }
        return !result;  // XNOR is the inverse of XOR
    }
    else if (operationType == "nand") {
        // nand: result is false if all inputs are true (inverse of AND)
        bool result = true;
        for (int i = 0; i < inputs.size(); ++i) {
            result = result && mp[inputs[i]];  // update the result one by one from the inputs
        }
        return !result;  // NAND is the inverse of AND
    }
    else if (operationType == "nor") {
        // nor: result is true if all inputs are false (inverse of OR)
        bool result = false;
        for (int i = 0; i < inputs.size(); ++i) {
            result = result || mp[inputs[i]];  // OR operation
        }
        return !result;  // NOR is the inverse of OR
    }
    else if (operationType == "buffer") {
        // buffer: simply returns the value of the single input
        if (inputs.size() == 1) {
            return mp[inputs[0]];  // BUFFER just passes the input unchanged
        }
          cout<<"A buffer gate has more than one input";
        return -999;  // invalid if not a single input
    }

    // Return -999 if unsupported operationType is provided
    cout<<"unsupported operation";
    return -999;
}

int Gate::getOutput(){return mp[output];}