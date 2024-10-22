#include "../headers/Simulation.h"
#include <fstream>
#include <cctype>
#include <regex> 
#include <sstream>

map<string, int> mp; 

// constructor
Simulation::Simulation() {}

// Function to remove leading spaces
string Simulation::trimLeadingSpaces(const string& line) {
    size_t start = 0;
    while (start < line.length() && isspace(line[start])) {
        ++start;
    }
    return line.substr(start);
}

// Function to check if the line is an empty line
bool Simulation::isWhitespace(const string& line) {
    for (char c : line) {
        if (!isspace(c)) {
            return false;
        }
    }
    return true;
}

// Function that gets the first word
string Simulation::getFirstWord(const string& line) {
    size_t pos = line.find(' ');
    if (pos != string::npos) {
        return line.substr(0, pos);
    }
    return line;
}

// Function to extract the inputs
vector<string> Simulation::extractInputs(const string& line) {
    vector<string> inputs;  // Vector to store extracted inputs
    string inputPart;       // Temporary string to hold inputs
    bool collecting = false; // Flag to start collecting inputs once we reach the '('
    bool firstArgumentIgnored = false; // Flag to ignore the first argument (output)

    for (char c : line) {
        if (c == '(') {
            collecting = true;  // Start collecting when '(' is found
        }
        else if (c == ')') {
            collecting = false; // Stop collecting when ')' is found
            if (!inputPart.empty()) {
                mp[inputPart] = -999;
                inputs.push_back(inputPart);  // Push the final input
            }
            break;  // We've reached the end of the inputs
        }
        else if (collecting) {
            if (c == ',') {
                if (!inputPart.empty()) {
                    if (firstArgumentIgnored) {
                        mp[inputPart] = -999;
                        inputs.push_back(inputPart);  // Store the input when encountering a comma
                    }
                    inputPart.clear();            // Reset for the next input
                    firstArgumentIgnored = true; // After the first comma, start collecting inputs
                }
            }
            else if (!isspace(c)) {  // Skip whitespace within the input part
                inputPart += c;  // Collect the characters for the current input
            }
        }
    }

    return inputs;
}

// Function to remove the first two words
string Simulation::removeFirstTwoWords(const string& line) {
    istringstream iss(line); // Stream to read words
    vector<string> words;
    string word;

    // Read all words from the line into the vector
    while (iss >> word) {
        words.push_back(word);
    }

    // Check if there are at least two words to remove
    if (words.size() > 2) {
        // Reconstruct the line starting from the third word
        ostringstream oss;
        for (size_t i = 2; i < words.size(); ++i) {
            oss << words[i];
            if (i != words.size() - 1) {
                oss << " "; // Add space between words
            }
        }
        return oss.str(); // Return the new line without the first two words
    }
    else {
        return ""; // If there are fewer than two words, return an empty string
    }
}

// Function to read the .v file and populate gates and the map
void Simulation::readVFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    bool isEmptyFile = true;
    vector<string> firstWords;
    vector<string> delays;
    vector<string> outputs;
    vector<vector<string>> inputs;

    while (getline(file, line)) {
        line = trimLeadingSpaces(line);

        if (isWhitespace(line)) {
            continue;
        }

        if (line.find("input") == 0 || line.find("output") == 0 ||
            line.find("wire") == 0 || line.find("module") == 0 ||
            line.find("endmodule") == 0) {
            continue;
        }

        // cout << line << endl;

        string firstWord = getFirstWord(line);
        firstWords.push_back(firstWord);

        // Extract delay using regex and store in delays vector
        regex delayPattern(R"#(\#\((\d+)\))#"); // Regular expression to find delays
        smatch match; // To store matched groups
        if (regex_search(line, match, delayPattern)) {
            if (match.size() > 1) {
                delays.push_back(match[1]); // Store the delay value
            }
        }

        // Store Output
        regex outputPattern(R"#(\(([a-zA-Z0-9]+)\,)#"); // Match output right after '(' before ','
        smatch matchO;
        if (regex_search(line, matchO, outputPattern)) {
            if (matchO.size() > 1) {
                mp[matchO[1]] = -999;
                outputs.push_back(matchO[1]); // Store the output
            }
        }

        // Remove the first two words so we can store the inputs
        line = removeFirstTwoWords(line);
        inputs.push_back(extractInputs(line));

        isEmptyFile = false;
    }

    if (isEmptyFile) {
        cout << "File is empty or contains only whitespace, ignoring..." << endl;
    }

    int size = delays.size();
    for(int i=0; i < size; i++){
        Gate* gate = new Gate(firstWords[i],inputs[i],outputs[i],stoi(delays[i]));
        gates.push_back(gate);
    }


/*
    // Print first words
    cout << "First words in the file:" << endl;
    for (const auto& word : firstWords) {
        cout << word << endl;
    }

    // Print delays
    cout << "Delays in the file:" << endl;
    for (const auto& delay : delays) {
        cout << delay << endl; // Print each delay
    }

    // Print outputs
    cout << "Outputs in the file:" << endl;
    for (const auto& output : outputs) {
        cout << output << endl;
    }

    // Print inputs
    cout << "Inputs in the file:" << endl;
    for (int i = 0; i < inputs.size(); i++) {
        for (int j = 0; j < inputs[i].size(); j++) {
            cout << inputs[i][j] << "\t";
        }
        cout << endl;
    }*/

    file.close();
}

//For the .stim file fun#1
//function to extract the timestamps from the .stim file
int Simulation::extractTimestamp(const std::string& line) {
    size_t hashPos = line.find('#');
    if (hashPos == std::string::npos) {
        throw std::invalid_argument("No '#' found in the input string.");
    }

    size_t spacePos = line.find(' ', hashPos);
    if (spacePos == std::string::npos) {
        throw std::invalid_argument("No space found after the '#' character.");
    }

    std::string timestampStr = line.substr(hashPos + 1, spacePos - hashPos - 1);

    int timestamp = std::stoi(timestampStr);

    return timestamp;
}


//For the .stim file fun#2
//function to extract the inputnames from the .stim file
string Simulation::extractInputName(const string& line) {
    size_t firstSpacePos = line.find(' ');
    if (firstSpacePos == string::npos) {
        throw invalid_argument("No space found after the timestamp.");
    }

    size_t equalPos = line.find('=', firstSpacePos);
    if (equalPos == string::npos) {
        throw std::invalid_argument("No '=' found in the input string.");
    }

    string inputName = line.substr(firstSpacePos + 1, equalPos - firstSpacePos - 1);

    return inputName;
}


//For the .stim file fun#3
//function to extract the new input values from the .stim file
int Simulation::extractNewValue(const string& line) {
    size_t equalPos = line.find('=');
    if (equalPos == string::npos) {
        throw invalid_argument("No '=' found in the input string.");
    }

    size_t semicolonPos = line.find(';', equalPos);
    if (semicolonPos == string::npos) {
        throw invalid_argument("No ';' found after the '=' in the input string.");
    }

    string valueStr = line.substr(equalPos + 1, semicolonPos - equalPos - 1);

    int newValue = stoi(valueStr);

    return newValue;
}

void Simulation::readStimFile(const string& filename){

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return ;
        }
        string line;
        vector<int>timestamps;
        vector<string>names;
        vector<int>newvalues;

        while (getline(file, line)) {

            int timestamp = extractTimestamp(line);
            timestamps.push_back(timestamp);

            int newvalue = extractNewValue(line);
            newvalues.push_back(newvalue);

            string name = extractInputName(line);
            names.push_back(name);

        }

        int size=timestamps.size();
        for(int i=0; i < size; i++){
            Event* event= new Event(timestamps[i],names[i],newvalues[i]);
            eventQueue.push(event);
        }
/*
        
        cout << "time stamps in the file:" << endl;
        for (const auto& timestamp1 : timestamps) {
            cout << timestamp1 << endl;
        }
        cout << "intput names in the file:" << endl;
        for (const auto& na : names) {
            cout << na << endl;
        }
        cout << "new value in the file:" << endl;
        for (const auto& nv : newvalues) {
            cout << nv << endl;
        }


*/

    file.close();

}

// Function to refresh the gate outputs
void Simulation::refreshGateOutputs(int currTime) {
    for(auto& gate : gates){
        int newValue = gate->evaluate();
        if(newValue != gate->getOutput()) {
            // If the newValue is different than the current value, create a new event for the output of the gate
            Event* event = new Event(currTime + gate->getDelay(), gate->getOutputName(), newValue);
            eventQueue.push(event);
        }
    }
}

void Simulation::simulate(const string& filename) {
    ofstream fileOut(filename);
    while(!eventQueue.empty()){
        Event* event = eventQueue.top();
        eventQueue.pop();
        int currTime = event->getTime();
        string signalName = event->getName();
        if(mp[signalName] != event->getNewValue()){ // if there is a change in the value of the signal
            mp[signalName] = event->getNewValue(); // update the value
            fileOut << currTime << ", " << signalName << ", " << event->getNewValue() << '\n'; // write the new value in the .sim file  
            refreshGateOutputs(currTime); // refresh the outputs of the gates
        }
    }
}    

void Simulation::run(const string& filename1, const string& filename2) {
    readVFile(filename1);
    readStimFile(filename2);
    simulate("output.sim");
}
