
#include "SMSWhiteNoise.h"


SMSWhiteNoise::SMSWhiteNoise (const double sample_rate) :
    mpfAudio_out_buffer(nullptr),
    mpfEnableValue(nullptr),
    mpfLevelValue(nullptr),
    mdSample_rate(sample_rate),
    gen(rd()),
    dis(-1.0f, 1.0f)
{

}

void SMSWhiteNoise::connectPort(const uint32_t port, void* data_location)
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

void SMSWhiteNoise::activate ()
{
   
}

void SMSWhiteNoise::deactivate ()
{

}

void SMSWhiteNoise::run (const uint32_t sample_count)
{
    // Check connection validity.
    if (!sample_count || !mpfAudio_out_buffer || !mpfEnableValue || !mpfLevelValue) 
        return;

    for (uint32_t i = 0; i < sample_count; i++)
    {
        if (*mpfEnableValue) // Check enabled.
        {
          mpfAudio_out_buffer[i] = dis(gen) * *mpfLevelValue;
        }    
    }
}

