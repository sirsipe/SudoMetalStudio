#pragma once

#include "../common/LV2Entry.h"
#include <random>

/* class definition */
class SMSWhiteNoise 
{
public:
    SMSWhiteNoise(const double sample_rate);
    void connectPort (const uint32_t port, void* data_location);
    void activate ();
    void deactivate ();

    void run (const uint32_t sample_count);

private:    
    float* mpfAudio_out_buffer;
    float* mpfEnableValue;
    float* mpfLevelValue;
    double mdSample_rate;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> dis;
};

EXPORT_PLUGIN_DESCRIPTOR(SMSWhiteNoise, "https://github.com/sirsipe/SudoMetalStudio/LV2Plugins/SMSWhiteNoise")