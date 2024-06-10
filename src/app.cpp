#include <fmt/core.h>
#include <memory>

#include "app.hpp"
#include "processor.hpp"

Stream::Stream() : cycfi::q::audio_stream(2, 2, SAMPLE_RATE, BUFFER_SIZE) {}
void Stream::process(in_channels const &in, out_channels const &out) {
    if (g_app->m_processor != nullptr) {
        g_app->m_processor->process(in, out);
    }
}

App::App(int argc, char **argv) {}

App::~App() { stopStream(); }

void App::startStream() {
    m_stream.start();
    m_isStreamActive = true;
}

void App::stopStream() {
    m_stream.stop();
    m_isStreamActive = false;
}

void App::changeProcessor(std::unique_ptr<Processor> newProcessor) {
    stopStream();
    m_processor.swap(newProcessor);
}
