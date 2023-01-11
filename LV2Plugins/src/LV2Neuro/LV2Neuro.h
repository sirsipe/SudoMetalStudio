#pragma once

#include "../common/LV2Entry.h"
#include "../common/ConstSizeFloatBuffer.h"

#ifndef DSP_BUFFER_MEMORY
#define DSP_BUFFER_MEMORY 480000    //can fit 10s with 48kHz sample rate 
#endif

/* class definition */
class LV2Neuro 
{
public:
    LV2Neuro(const double sample_rate);
    void connectPort (const uint32_t port, void* data_location);
    void activate ();
    void deactivate ();

    void run (const uint32_t sample_count);

private:
    float* mpfAudio_in_buffer;
    float* mpfAudio_learn_buffer;
    float* mpfAudio_out_buffer;
    float* mpfLevelValue;
    double mdSample_rate;

    ConstSizeFloatBuffer<DSP_BUFFER_MEMORY> moBufferMemory;
};

EXPORT_PLUGIN_DESCRIPTOR(LV2Neuro, "https://github.com/sirsipe/SudoMetalStudio/LV2Plugins/LV2Neuro")