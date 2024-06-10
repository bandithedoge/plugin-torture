#pragma once

#include <q/support/audio_stream.hpp>

#include "../processor.hpp"

class EmptyProcessor : public Processor {
  public:
    EmptyProcessor();
    ~EmptyProcessor();

    void processMethod(in_channels const &in, out_channels const &out) override;
    void render() override;
};
