#pragma once

#include "../common/LV2Entry.h"

/* class definition */
class SMS440Hz 
{
public:
    SMS440Hz(const double sample_rate);
    void connectPort (const uint32_t port, void* data_location);
    void activate ();
    void deactivate ();

    void run (const uint32_t sample_count);

private:    
    float* mpfAudio_out_buffer;

    float* mpfEnableValue;
    float* mpfLevelValue;

    const double mdSample_rate;
    const double mdPhaseStep;
    double mdPhase;
};

EXPORT_PLUGIN_DESCRIPTOR(SMS440Hz, "https://github.com/sirsipe/SudoMetalStudio/LV2Plugins/SMS440Hz")