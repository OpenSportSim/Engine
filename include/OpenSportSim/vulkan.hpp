#ifndef __OPENSPORTSIM_VULKAN_HPP
#define __OPENSPORTSIM_VULKAN_HPP
#include <OpenSportSim/window.hpp>

namespace OpenSportSim::Vulkan {
    class GLFWHandle: public OpenSportSim::GLFWHandle {
    public:
        GLFWHandle(const char*);
        virtual ~GLFWHandle() = default;
    };
}

#endif
