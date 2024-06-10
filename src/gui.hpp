#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_sugar.hpp>
#include <implot/implot.h>
#include <memory>

class Gui {
  public:
    Gui();
    ~Gui();
    void render();

  private:
    GLFWwindow *m_window;
};

inline std::unique_ptr<Gui> g_gui;
