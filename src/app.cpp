#include <fmt/core.h>
#include <memory>

#include "app.hpp"
#include "portaudio.h"
#include "processor.hpp"
#include "processor/empty.hpp"

static int process(const void *input, void *output, unsigned long bufferSize, const PaStreamCallbackTimeInfo *timeInfo,
                   PaStreamCallbackFlags statusFlags, void *userData) {
    // Processor *processor = (Processor *)userData;
    return g_app->m_processor->processMethod(input, output, bufferSize, timeInfo, statusFlags);
    // return paContinue;
}

App::App(int argc, char **argv) {
    // setup audio stream
    PaError err = Pa_Initialize();

    const PaHostApiInfo *api_info = Pa_GetHostApiInfo(Pa_HostApiTypeIdToHostApiIndex(paALSA));

    m_inputParams.device = api_info->defaultInputDevice;
    m_inputParams.channelCount = 2;
    m_inputParams.sampleFormat = paFloat32 | paNonInterleaved;
    m_inputParams.suggestedLatency = Pa_GetDeviceInfo(m_inputParams.device)->defaultLowInputLatency;
    m_inputParams.hostApiSpecificStreamInfo = NULL;

    m_outputParams.device = api_info->defaultOutputDevice;
    m_outputParams.channelCount = 2;
    m_outputParams.sampleFormat = paFloat32 | paNonInterleaved;
    m_outputParams.suggestedLatency = Pa_GetDeviceInfo(m_outputParams.device)->defaultLowOutputLatency;
    m_outputParams.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(&m_stream, &m_inputParams, &m_outputParams, SAMPLE_RATE, BUFFER_SIZE, 0, process, &m_processor);
}

App::~App() {
    stopStream();
    Pa_Terminate();
}

void App::startStream() {
    Pa_StartStream(m_stream);
    m_isStreamActive = true;
}

void App::stopStream() {
    Pa_StopStream(m_stream);
    m_isStreamActive = false;
}

void App::changeProcessor(std::unique_ptr<Processor> newProcessor) {
    stopStream();
    m_processor.swap(newProcessor);
    // startStream();
}
