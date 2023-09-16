#pragma once

#include "../common/LV2Entry.h"

/* class definition */
class SMSSwitch 
{
public:
    SMSSwitch(const double sample_rate);
    void connectPort (const uint32_t port, void* data_location);
    void activate ();
    void deactivate ();

    void run (const uint32_t sample_count);

private:
    float* mpfAudio_in_buffer;    
    float* mpfAudio_out_buffer;
    float* mpfEnableValue;
};

EXPORT_PLUGIN_DESCRIPTOR(SMSSwitch, "https://github.com/sirsipe/SudoMetalStudio/LV2Plugins/SMSSwitch")