#pragma once

#include <lilv/lilvmm.hpp>
#include <map>

#include "../processor.hpp"

class LV2Processor : public Processor {
  public:
    LV2Processor();
    ~LV2Processor();

    void processMethod(in_channels const &in, out_channels const &out) override;
    void render() override;

  private:
    void searchPlugins();
    void loadPlugin(const char *uri);

    std::map<const char *, const char *> getInstalledPlugins();

    Lilv::Instance m_instance = nullptr;
    Lilv::World m_world;
    Lilv::Plugin m_plugin = nullptr;

    float m_inputBuffer[2][BUFFER_SIZE];
    float m_outputBuffer[2][BUFFER_SIZE];
};
