
#include "SMSSwitch.h"

SMSSwitch::SMSSwitch (const double sample_rate) :
    mpfAudio_in_buffer(nullptr),
    mpfAudio_out_buffer(nullptr),
    mpfEnableValue(nullptr)
{
    
}

void SMSSwitch::connectPort (const uint32_t port, void* data_location)
{
    switch (port)
    {
    case 0:
        mpfAudio_in_buffer = static_cast<float*>(data_location);
        break;
    case 1:
        mpfAudio_out_buffer = static_cast<float*>(data_location);
        break;
    case 2:
        mpfEnableValue = static_cast<float*>(data_location);
        break;
    }

}

void SMSSwitch::activate ()
{

}

void SMSSwitch::deactivate ()
{

}

void SMSSwitch::run (const uint32_t sample_count)
{
    // Check connection validity.
    if (!mpfAudio_out_buffer || !mpfAudio_in_buffer || !mpfEnableValue) 
        return;


    for (uint32_t i = 0; i < sample_count; ++i)
    {
        if (*mpfEnableValue)
            mpfAudio_out_buffer[i] = mpfAudio_in_buffer[i];
        else
            mpfAudio_out_buffer[i] = 0;
    }


}

