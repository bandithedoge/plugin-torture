#pragma once

#define SAMPLE_RATE 44100.f
#define BUFFER_SIZE 256

#include <lilv/lilvmm.hpp>
#include <memory>
#include <portaudio.h>

#include "processor/empty.hpp"

class App {
  public:
    App(int argc, char **argv);
    ~App();

    void stopStream();
    void startStream();
    void changeProcessor(std::unique_ptr<Processor> newProcessor);

    float m_inputBuffer[2][BUFFER_SIZE];
    float m_outputBuffer[2][BUFFER_SIZE];
    std::unique_ptr<Processor> m_processor = nullptr;
    bool m_isStreamActive = false;

  private:
    PaStream *m_stream;
    Lilv::World m_lilvWorld;
    PaStreamParameters m_inputParams, m_outputParams;
};

inline std::unique_ptr<App> g_app;
