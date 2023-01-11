#pragma once

#include "../common/LV2Entry.h"

/* class definition */
class LV2Neuro 
{
public:
    LV2Neuro(const double sample_rate);
    void connectPort (const uint32_t port, void* data_location);
    void activate ();
    
    void run (const uint32_t sample_count);

private:
    float* mpfAudio_in_buffer;
    float* mpfAudio_learn_buffer;
    float* mpfAudio_out_buffer;
    float* mpfLevelValue;
    double mdSample_rate;
};

EXPORT_PLUGIN_DESCRIPTOR(LV2Neuro, "https://github.com/sirsipe/SudoMetalStudio/LV2Plugins/LV2Neuro")