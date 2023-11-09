#pragma once

#include "../common/LV2Entry.h"
#include "../common/RingBuffer.h"

/* class definition */
class SMSStereoDelay 
{
public:
    SMSStereoDelay(const double sample_rate);
    void connectPort (const uint32_t port, void* data_location);
    void activate ();
    void deactivate ();

    void run (const uint32_t sample_count);

private:    
    float* mpfAudio_in_buffer;
    float* mpfAudio_out_buffer_l;
    float* mpfAudio_out_buffer_r;

    float* mpfEnableValue;
    float* mpfLevelValue;
    float* mpfDelayLValue;
    float* mpfDelayRValue;
    float* mpfDecayValue;
    float* mpfDecayCount;
    
    double mdSample_rate;

    RingBuffer moRingBuffer;
};

EXPORT_PLUGIN_DESCRIPTOR(SMSStereoDelay, "https://github.com/sirsipe/SudoMetalStudio/LV2Plugins/SMSStereoDelay")