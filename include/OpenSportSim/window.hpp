#ifndef __OPENSPORTSIM_WINDOW_HPP
#define __OPENSPORTSIM_WINDOW_HPP
#include "graphics.hpp"
#include <OpenSportSim/graphics.hpp>
#include <concepts>

namespace OpenSportSim {
    template <typename T>
    concept Window = requires(T window) {
        { window.hide() } -> std::same_as<void>;
        { window.show() } -> std::same_as<void>;
        { window.requestFocus() } -> std::same_as<void>;
        { window.close() } -> std::same_as<void>;
        { window.poll() } -> std::same_as<void>;
        { window.swap() } -> std::same_as<void>;
        { window.shouldClose() } -> std::same_as<bool>;
    };

    class GLFWHandle {
    public:
        GLFWHandle(const char *);
        virtual ~GLFWHandle();
        void *raw() const noexcept;
        bool isOpen() const noexcept;
    protected:
        void createWindow();
        void *window = nullptr;
    };

    class AgnosticWindow {
    public:
        AgnosticWindow(const char *);
        ~AgnosticWindow();
        void hide() const noexcept;
        void show() const noexcept;
        void requestFocus() const noexcept;
        void close() const noexcept;
        void poll() noexcept;
        void swap() noexcept;
        bool shouldClose() const noexcept;
        GLFWHandle *getHandle() const noexcept;
    private:
        GraphicsRenderer *renderer = nullptr;
        GLFWHandle *handle = nullptr;
    };
}

#endif
