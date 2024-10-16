#ifndef __OPENSPORTSIM_CORE_HPP
#define __OPENSPORTSIM_CORE_HPP
#include <OpenSportSim/window.hpp>
#include <cwchar>

namespace OpenSportSim {
    class Engine {
    public:
        Engine();
        virtual ~Engine() = 0;
        virtual void tick();
        bool running();
        void stop();
    private:
        bool r = true;
    };
    template<Window Win>
    class ClientEngine: public Engine {
    public:
        ClientEngine(const Win& w);
        ~ClientEngine();
        virtual void tick();
    private:
        const Win& window;
    };
}

#endif
