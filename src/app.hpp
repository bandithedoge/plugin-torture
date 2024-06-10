#pragma once

#include <memory>
#include <q_io/audio_stream.hpp>

#include "processor.hpp"

class Stream : public cycfi::q::audio_stream {
  public:
    Stream();
    void process(in_channels const &in, out_channels const &out) override;
};

class App {
  public:
    App(int argc, char **argv);
    ~App();

    void stopStream();
    void startStream();
    void changeProcessor(std::unique_ptr<Processor> newProcessor);

    std::unique_ptr<Processor> m_processor = nullptr;
    bool m_isStreamActive = false;

  private:
    Stream m_stream;
};

inline std::unique_ptr<App> g_app;
