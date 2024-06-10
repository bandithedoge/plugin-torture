#include <fmt/core.h>

#include "main.hpp"
#include "processor.hpp"

Processor::Processor() {}

Processor::~Processor() {}

void Processor::process(in_channels const &in, out_channels const &out) {
    memcpy(m_inputBuffer[0], in[0].begin(), BUFFER_SIZE * sizeof(float));
    memcpy(m_inputBuffer[1], in[1].begin(), BUFFER_SIZE * sizeof(float));
    processMethod(in, out);
    memcpy(m_outputBuffer[0], out[0].begin(), BUFFER_SIZE * sizeof(float));
    memcpy(m_outputBuffer[1], out[1].begin(), BUFFER_SIZE * sizeof(float));
}

void Processor::processMethod(in_channels const &in, out_channels const &out) {}

void Processor::render(){};
