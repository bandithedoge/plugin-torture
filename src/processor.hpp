#pragma once

#include <q/support/audio_stream.hpp>

#include "main.hpp"

class Processor : public cycfi::q::audio_stream_base {
  public:
    Processor();
    ~Processor();

    void process(in_channels const &in, out_channels const &out) override;
    virtual void processMethod(in_channels const &in, out_channels const &out);
    virtual void render();

    float m_inputBuffer[2][BUFFER_SIZE];
    float m_outputBuffer[2][BUFFER_SIZE];
};
