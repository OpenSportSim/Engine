#include <glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <OpenSportSim/opengl.hpp>

OpenSportSim::OpenGL::Buffer::Buffer(unsigned int id) {
    this->id = id;
}

OpenSportSim::OpenGL::Buffer::~Buffer() {}

void OpenSportSim::OpenGL::Buffer::store(void *data, size_t len) {

}

OpenSportSim::OpenGL::Renderer::Renderer() {
    gladLoadGL();
    this->reserve(16);
}
OpenSportSim::OpenGL::Renderer::~Renderer() {
    if (this->rawBufferCache != nullptr) free(this->rawBufferCache);
    if (this->buffers == nullptr) return;
    auto end = this->buffers + this->rawBufferCacheSize;
    // Free buffers
    free(this->buffers);
}

OpenSportSim::GraphicsBuffer* OpenSportSim::OpenGL::Renderer::createBuffers(std::size_t count) {
    if (this->rawBufferCache == nullptr) {
        this->rawBufferCache = static_cast<unsigned int*>(malloc(count + sizeof(unsigned int)));
        this->rawBufferCacheSize = count;
    } else if (this->rawBufferCacheSize <= count) {
        this->rawBufferCache = static_cast<unsigned int*>(realloc(this->rawBufferCache, count + sizeof(unsigned int)));
        this->rawBufferCacheSize = count;
    }
    OpenSportSim::GraphicsBuffer* buffers = static_cast<OpenSportSim::GraphicsBuffer*>(malloc(count * sizeof(OpenSportSim::GraphicsBuffer)));
    glGenBuffers(count, this->rawBufferCache);
    unsigned int *buffersRaw = this->rawBufferCache;
    const unsigned int *buffersRawEnd = this->rawBufferCache + count;
    const auto combined = this->len + count;
    if (combined >= this->size) this->reserve(1 + combined - this->size);
    while (buffersRaw < buffersRawEnd) {
        auto buffer = new OpenSportSim::OpenGL::Buffer(*buffersRaw);
        auto index = this->len++;
    }
    return buffers;
}

void OpenSportSim::GraphicsRenderer::reserve(size_t extension) {
    if (extension == 0) return;
    const auto newSize = extension + this->size;
    const auto sizeOf = sizeof(OpenSportSim::GraphicsBuffer**);
    if (this->buffers == nullptr) this->buffers = (OpenSportSim::GraphicsBuffer**)malloc(sizeOf * newSize);
    else this->buffers = (OpenSportSim::GraphicsBuffer**)realloc((void*)this->buffers, sizeOf * newSize);
    this->size = newSize;
}
