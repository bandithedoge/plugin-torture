#include <fmt/core.h>
#include <memory>
#include <portaudio.h>
#include <unistd.h>

#include "app.hpp"

#define IMGUI_IMPLEMENTATION
#include "gui.hpp"

int main(int argc, char **argv) {
    g_app = std::make_unique<App>(argc, argv);
    g_gui = std::make_unique<Gui>();

    g_gui.get()->render();

    return 0;
}
