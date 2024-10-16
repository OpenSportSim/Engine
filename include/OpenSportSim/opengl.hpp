#ifndef __OPENSPORTSIM_OPENGL
#define __OPENSPORTSIM_OPENGL
#include "graphics.hpp"
#include <OpenSportSim/window.hpp>
#include <OpenSportSim/graphics.hpp>
#include <cstddef>

namespace OpenSportSim::OpenGL {
    class GLFWHandle: public OpenSportSim::GLFWHandle {
    public:
        GLFWHandle(const char *);
        virtual ~GLFWHandle() = default;
    };
    class Buffer: public OpenSportSim::GraphicsBuffer {
    public:
        Buffer(unsigned int);
        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;
        virtual ~Buffer();
        virtual void store(void *, size_t);
    private:
        unsigned int id;
    };
    class Renderer: public OpenSportSim::GraphicsRenderer {
    public:
        Renderer();
        virtual ~Renderer();
        virtual GraphicsBuffer* createBuffers(size_t);
    private:
        unsigned int *rawBufferCache = nullptr;
        size_t rawBufferCacheSize = 0;
    };
}

#endif
