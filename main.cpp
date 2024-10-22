#include "./sources/Simulation.cpp"

int main() {

    Simulation sim;

    sim.run("./tests/test1/test1.v", "./tests/test1/test1.stim");

    return 0;
}
