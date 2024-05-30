#pragma once

#include "app.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include "imgui_sugar.hpp"
#include "implot/implot.h"
#include <GLFW/glfw3.h>
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
