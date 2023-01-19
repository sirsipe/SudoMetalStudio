#pragma once

#include "../common/LV2Entry.h"
#include "../common/IIRHighPassFilter.h"
#include "../common/IIRLowPassFilter.h"

/* class definition */
class SMSNorthernPerkele 
{
public:
    SMSNorthernPerkele(const double sample_rate);
    void connectPort (const uint32_t port, void* data_location);
    void activate ();
    void deactivate ();

    void run (const uint32_t sample_count);

private:    
    float* mpfAudio_in_buffer;
    float* mpfAudio_out_buffer;

    float* mpfEnableValue;
    float* mpfDriveValue;
    float* mpfVolumeValue;
    float* mpfLowPassValue;
    float* mpfHighPassValue;
    float* mpfLowPassGainValue;
    float* mpfHighPassGainValue;
    double mdSample_rate;
    IIRHighPassFilter mHighPassFilter;
    IIRLowPassFilter mLowPassFilter;
    
};

EXPORT_PLUGIN_DESCRIPTOR(SMSNorthernPerkele, "https://github.com/sirsipe/SudoMetalStudio/LV2Plugins/SMSNorthernPerkele")