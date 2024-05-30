#pragma once

#include "../processor.hpp"

class EmptyProcessor : public Processor {
  public:
    EmptyProcessor();
    ~EmptyProcessor();

    int processMethod(const void *input, void *output, unsigned long bufferSize,
                      const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags) override;
    void render() override;
};
