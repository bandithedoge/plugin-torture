#include <algorithm>
#include <fmt/core.h>

#include "../app.hpp"
#include "../gui.hpp"
#include "lv2.hpp"

LV2Processor::LV2Processor() { m_world.load_all(); }
LV2Processor::~LV2Processor() {}

void LV2Processor::loadPlugin(const char *uri) {
    fmt::println("loading plugin with uri {}", uri);

    g_app.get()->stopStream();

    if (m_instance != nullptr)
        m_instance.deactivate();

    Lilv::Plugins plugins = m_world.get_all_plugins();
    m_plugin = plugins.get_by_uri(m_world.new_uri(uri));
    m_instance = Lilv::Instance(m_plugin, SAMPLE_RATE);
    m_instance.activate();
    m_instance.connect_port(
        lilv_port_get_index(m_plugin, m_plugin.get_port_by_symbol(m_world.new_string("lv2_audio_in_1"))),
        m_inputBuffer[0]);
    m_instance.connect_port(
        lilv_port_get_index(m_plugin, m_plugin.get_port_by_symbol(m_world.new_string("lv2_audio_in_2"))),
        m_inputBuffer[1]);
    m_instance.connect_port(
        lilv_port_get_index(m_plugin, m_plugin.get_port_by_symbol(m_world.new_string("lv2_audio_out_1"))),
        m_outputBuffer[0]);
    m_instance.connect_port(
        lilv_port_get_index(m_plugin, m_plugin.get_port_by_symbol(m_world.new_string("lv2_audio_out_2"))),
        m_outputBuffer[1]);

    g_app.get()->startStream();
}

int LV2Processor::processMethod(const void *input, void *output, unsigned long bufferSize,
                                const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags) {
    Channels *in = (Channels *)input;
    memcpy(m_inputBuffer[0], in->left, BUFFER_SIZE * sizeof(float));
    memcpy(m_inputBuffer[1], in->right, BUFFER_SIZE * sizeof(float));

    if (m_instance != nullptr)
        m_instance.run(bufferSize);

    Channels *out = (Channels *)output;
    memcpy(out->left, m_inputBuffer[0], BUFFER_SIZE * sizeof(float));
    memcpy(out->right, m_outputBuffer[1], BUFFER_SIZE * sizeof(float));

    return paContinue;
}

void LV2Processor::render() {
    if (ImGui::Button("Load plugin"))
        ImGui::OpenPopup("Load plugin");

    if (m_plugin != nullptr) {
        with_Table("plugin", 3) {
            ImGui::TableSetupColumn("name");
            ImGui::TableSetupColumn("uri");
            ImGui::TableSetupColumn("author");
            ImGui::TableHeadersRow();

            ImGui::TableNextColumn();
            ImGui::Text("%s", m_plugin.get_name().as_string());
            ImGui::TableNextColumn();
            ImGui::Text("%s", m_plugin.get_uri().as_string());
            ImGui::TableNextColumn();
            ImGui::Text("%s", m_plugin.get_author_name().as_string());
        }
    }

    with_Popup("Load plugin", ImGuiWindowFlags_NoMove) {
        static std::map<const char *, const char *> plugins = getInstalledPlugins();
        static std::map<const char *, const char *> pluginsFiltered = plugins;
        static char buf[128];

        ImGui::InputText("Search", buf, 128, ImGuiInputTextFlags_CallbackEdit,
                         [](ImGuiInputTextCallbackData *data) -> int {
                             if (!strcmp("", buf))
                                 pluginsFiltered = plugins;
                             else {
                                 pluginsFiltered.clear();
                                 for (auto [uri, name] : plugins) {
                                     std::string n(name);
                                     std::string q(buf);
                                     std::transform(n.begin(), n.end(), n.begin(), ::tolower);
                                     std::transform(q.begin(), q.end(), q.begin(), ::tolower);
                                     if (n.contains(q))
                                         pluginsFiltered[uri] = name;
                                 }
                             }
                             return 0;
                         });
        for (auto [uri, name] : pluginsFiltered) {
            if (ImGui::Button(name))
                loadPlugin(uri);
        }
    }
}

std::map<const char *, const char *> LV2Processor::getInstalledPlugins() {
    Lilv::Plugins plugins = m_world.get_all_plugins();
    std::map<const char *, const char *> result;

    LILV_FOREACH(plugins, i, plugins) {
        Lilv::Plugin p = plugins.get(i);
        result[p.get_uri().as_string()] = p.get_name().as_string();
    }
    return result;
}
