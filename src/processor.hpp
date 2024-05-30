#pragma once

#include <portaudio.h>

#include "globals.hpp"

struct Channels {
    float *left;
    float *right;
};

class Processor {
  public:
    Processor();
    ~Processor();

    virtual int processMethod(const void *input, void *output, unsigned long bufferSize,
                              const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags);
    virtual void render();

    float m_inputBuffer[2][BUFFER_SIZE];
    float m_outputBuffer[2][BUFFER_SIZE];
};
