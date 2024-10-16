#include <OpenSportSim/window.hpp>
#include <OpenSportSim/core.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    OpenSportSim::AgnosticWindow window("Client");
    OpenSportSim::ClientEngine<OpenSportSim::AgnosticWindow> engine(window);
    std::cout << "Hello User" << std::endl;
    while(engine.running()) {
        engine.tick();
        window.poll();
    }
    return 0;
}
