#include <cstring>
#include <fmt/core.h>

#include "app.hpp"
#include "gui.hpp"
#include "processor/lv2.hpp"

Gui::Gui() {
    glfwSetErrorCallback(
        [](int error, const char *description) { fmt::print(stderr, "GLFW error {}: {}", error, description); });

    if (!glfwInit())
        exit(1);

    m_window = glfwCreateWindow(1280, 720, "Plugin Torture", nullptr, nullptr);

    if (m_window == nullptr)
        exit(1);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;
    ImPlot::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL2_Init();
}

Gui::~Gui() {
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Gui::render() {
    static App *app = g_app.get();
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiStyle &style = ImGui::GetStyle();
        style.WindowBorderSize = 0.0f;

        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(display_w, display_h));

        with_Window("Plugin Torture", NULL, ImGuiWindowFlags_NoDecoration) {
            if (app->m_processor != nullptr) {
                if (app->m_isStreamActive) {
                    if (ImGui::Button("STOP STREAM"))
                        app->stopStream();
                } else if (ImGui::Button("START STREAM"))
                    app->startStream();
            }

            if (ImGui::Button("LV2")) {
                app->changeProcessor(std::make_shared<LV2Processor>());
            }
            ImGui::SameLine();
            if (ImGui::Button("Empty")) {
                app->changeProcessor(std::make_shared<EmptyProcessor>());
            }

            if (app->m_processor != nullptr)
                app->m_processor->render();

            if (app->m_isStreamActive)
                if (ImPlot::BeginPlot("input", ImVec2(-1, -1))) {
                    ImPlot::SetupAxes("time", "amplitude");
                    ImPlot::SetupAxesLimits(0, BUFFER_SIZE, -2, 2, ImPlotCond_Always);
                    ImPlot::PlotLine("left", app->m_processor->m_outputBuffer[0], BUFFER_SIZE);
                    ImPlot::PlotLine("right", app->m_processor->m_outputBuffer[1], BUFFER_SIZE);
                    ImPlot::EndPlot();
                }
        }

        ImGui::Render();
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(m_window);
        glfwSwapBuffers(m_window);
    };
}