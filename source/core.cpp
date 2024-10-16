#include <OpenSportSim/core.hpp>
#include <OpenSportSim/window.hpp>

OpenSportSim::Engine::Engine() = default;
OpenSportSim::Engine::~Engine() = default;
void OpenSportSim::Engine::tick() {}
bool OpenSportSim::Engine::running() { return this->r; }
void OpenSportSim::Engine::stop() { this->r = false; }
template<OpenSportSim::Window Win>
OpenSportSim::ClientEngine<Win>::ClientEngine(const Win& win) : window(win) {
    this->window.show();
}
template<OpenSportSim::Window Win>
OpenSportSim::ClientEngine<Win>::~ClientEngine() {}
template<OpenSportSim::Window Win>
void OpenSportSim::ClientEngine<Win>::tick() {
    if (this->window.shouldClose()) this->stop();
}

template class OpenSportSim::ClientEngine<OpenSportSim::AgnosticWindow>;
