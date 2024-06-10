#include "empty.hpp"
#include "../gui.hpp"

EmptyProcessor::EmptyProcessor() {}
EmptyProcessor::~EmptyProcessor() {}

void EmptyProcessor::processMethod(in_channels const &in, out_channels const &out) {
    memcpy(out[0].begin(), in[0].begin(), in.frames.size() * sizeof(float));
    memcpy(out[1].begin(), in[1].begin(), in.frames.size() * sizeof(float));
}

void EmptyProcessor::render() { ImGui::Text("empty"); }
