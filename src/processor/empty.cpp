#include "portaudio.h"
#include <cstring>

#include "../gui.hpp"
#include "empty.hpp"

EmptyProcessor::EmptyProcessor() {}
EmptyProcessor::~EmptyProcessor() {}

int EmptyProcessor::processMethod(const void *input, void *output, unsigned long bufferSize,
                                  const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags) {

    Channels *in = (Channels *)input;
    memcpy(m_inputBuffer[0], in->left, BUFFER_SIZE * sizeof(float));
    memcpy(m_inputBuffer[1], in->right, BUFFER_SIZE * sizeof(float));

    memcpy(m_outputBuffer[0], m_inputBuffer[0], BUFFER_SIZE * sizeof(float));
    memcpy(m_outputBuffer[1], m_inputBuffer[1], BUFFER_SIZE * sizeof(float));

    Channels *out = (Channels *)output;
    memcpy(out->left, m_outputBuffer[0], BUFFER_SIZE * sizeof(float));
    memcpy(out->right, m_outputBuffer[1], BUFFER_SIZE * sizeof(float));

    return paContinue;
}

void EmptyProcessor::render() { ImGui::Text("empty"); }
