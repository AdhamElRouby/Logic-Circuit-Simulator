#ifndef SIMULATION
#define SIMULATION

#include "../sources/Event.cpp"
#include "../sources/Gate.cpp"
#include <queue>

struct EventComparator {
    bool operator()(Event *lhs, Event *rhs) const {
        return lhs->getTime() > rhs->getTime();
    }
};

class Simulation {
  private:
    priority_queue<Event *, vector<Event *>, EventComparator> eventQueue;
    vector<Gate *> gates;
    void simulate(const string &filename); // helper function for run - runs the
                                           // event-driven simulation
    void refreshGateOutputs(int currTime); // helper function for simulate
    // helping function to parse the .v file
    string trimLeadingSpaces(const string &line);
    bool isWhitespace(const string &line);
    string getFirstWord(const string &line);
    vector<string> extractInputs(const string &line);
    string removeFirstTwoWords(const string &line);

    void readVFile(const string &filename);

    // helping functions to parse the .stim file
    int extractTimestamp(const std::string &line);
    string extractInputName(const string &line);
    int extractNewValue(const string &line);
    void readStimFile(const string &filename);

  public:
    Simulation(); // constructor

    void run(const string &filename1,
             const string &filename2); // starts the simulation
};

#endif
