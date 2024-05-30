#include <fmt/core.h>

#include "gui.hpp"
#include "processor.hpp"

Processor::Processor() {}
Processor::~Processor() {}

int Processor::processMethod(const void *input, void *output, unsigned long bufferSize,
                             const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags) {
    return paContinue;
};

void Processor::render(){};
