#ifndef SIMULATION
#define SIMULATION

#include <queue>
#include "../sources/Gate.cpp"
#include "../headers/Event.h"

struct EventComparator {
    bool operator()(Event* lhs, Event* rhs) const {
        return lhs->getTime() > rhs->getTime(); 
    }
};

class Simulation {
    private:
        priority_queue<Event*, vector<Event*>, EventComparator> eventQueue; 
        vector<Gate*> gates;

    public:
        Simulation() {};

        // helping function to parse the .v file
        string trimLeadingSpaces(const string& line);
        bool isWhitespace(const string& line);
        string getFirstWord(const string& line);
        vector<string> extractInputs(const string& line);
        string removeFirstTwoWords(const string& line);

        void readVFile(const string& filename);
        void readStimFile(const string& filename);    
};



#endif
