
#include "SMS440Hz.h"
#include <math.h>

SMS440Hz::SMS440Hz (const double sample_rate) :
    mpfAudio_out_buffer(nullptr),
    mpfLevelValue(nullptr),
    mdSample_rate(sample_rate),
    mdPhase(0),
    mdPhaseStep(440.0 / mdSample_rate)
{

}

void SMS440Hz::connectPort (const uint32_t port, void* data_location)
{

    switch (port)
    {
    case 0:
        mpfAudio_out_buffer = static_cast<float*>(data_location);
        break;
    case 1:
        mpfEnableValue = static_cast<float*>(data_location);
        break;
    case 2:
        mpfLevelValue = static_cast<float*>(data_location);
        break;
    default:
        break;
    }

}

void SMS440Hz::activate ()
{
    mdPhase = 0;
}

void SMS440Hz::deactivate ()
{

}

void SMS440Hz::run (const uint32_t sample_count)
{
    // Check connection validity.
    if (!mpfAudio_out_buffer || !mpfEnableValue || !mpfLevelValue) 
        return;


    for (uint32_t i = 0; i < sample_count; ++i)
    {
        if (*mpfEnableValue)
        {
            mpfAudio_out_buffer[i] = sin(2.0 * M_PI * mdPhase) * *mpfLevelValue;
            mdPhase += mdPhaseStep;
        }
        else
            mpfAudio_out_buffer[i] = 0;
    }
}

