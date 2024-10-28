#include "./sources/Simulation.cpp"
#include <iostream>

int main() {

    Simulation sim;

    cout << "Welcome to the Logic Circuit Simulator\n";

    string vFile, stimFile;
    cout << "Enter the path to the .v file: ";
    cin >> vFile;
    cout << "Enter the path to the .stim file: ";
    cin >> stimFile;
    sim.run(vFile, stimFile);

    cout << "Simulation complete\n";

    return 0;
}
