#ifndef __OPENSPORTSIM_GRAPHICS_HPP
#define __OPENSPORTSIM_GRAPHICS_HPP
#include <cstddef>

namespace OpenSportSim {
    class GraphicsBuffer {
    public:
        GraphicsBuffer() = default;
        GraphicsBuffer(const GraphicsBuffer&) = delete;
        virtual ~GraphicsBuffer() = 0;
        virtual void store(void *, size_t) = 0;
    private:
    };
    class GraphicsRenderer {
    public:
        GraphicsRenderer() = default;
        virtual ~GraphicsRenderer() = 0;
        virtual GraphicsBuffer* createBuffers(size_t) = 0;
    protected:
        void reserve(size_t);
        size_t size;
        size_t len;
        GraphicsBuffer** buffers = nullptr;
    };
}

#endif
