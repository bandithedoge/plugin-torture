#pragma once

#include "../processor.hpp"
#include <lilv/lilvmm.hpp>
#include <map>

class LV2Processor : public Processor {
  public:
    LV2Processor();
    ~LV2Processor();

    int processMethod(const void *input, void *output, unsigned long bufferSize,
                      const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags) override;
    void render() override;

  private:
    void searchPlugins();
    void loadPlugin(const char *uri);

    std::map<const char*, const char*> getInstalledPlugins();

    Lilv::Instance m_instance = nullptr;
    Lilv::World m_world;
    Lilv::Plugin m_plugin = nullptr;
};
