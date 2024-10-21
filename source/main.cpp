#include <OpenSportSim/window.hpp>
#include <OpenSportSim/core.hpp>

int main(int argc, char *argv[]) {
    OpenSportSim::AgnosticWindow window("Client");
    OpenSportSim::ClientEngine<OpenSportSim::AgnosticWindow> engine(window);
    while(engine.running()) {
        engine.tick();
        window.poll();
    }
    return 0;
}
