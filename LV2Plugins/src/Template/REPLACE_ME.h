#pragma once

#define NO_LV2_UI_HEADER
#include "../common/LV2Entry.h"

/* class definition */
class REPLACE_ME 
{
public:
    REPLACE_ME(const double sample_rate);
    void connectPort (const uint32_t port, void* data_location);
    void activate ();
    void deactivate ();

    void run (const uint32_t sample_count);

private:
    float* mpfAudio_in_buffer;    
    float* mpfAudio_out_buffer;
    float* mpfEnableValue;
    double mdSampleRate;
};

EXPORT_PLUGIN_DESCRIPTOR(REPLACE_ME, "https://github.com/sirsipe/SudoMetalStudio/LV2Plugins/MYODP/REPLACE_ME")