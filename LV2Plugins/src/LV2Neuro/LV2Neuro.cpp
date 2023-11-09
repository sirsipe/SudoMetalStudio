#include "LV2Neuro.h"

LV2Neuro::LV2Neuro (const double sample_rate) :
    mpfAudio_in_buffer(nullptr),
    mpfAudio_learn_buffer(nullptr),
    mpfAudio_out_buffer(nullptr),
    mpfLevelValue(nullptr),
    mdSample_rate(sample_rate)
{

}

void LV2Neuro::connectPort (const uint32_t port, void* data_location)
{

    switch (port)
    {
    case 0:
        mpfAudio_in_buffer = static_cast<float*>(data_location);
        break;
    case 1:
        mpfAudio_learn_buffer = static_cast<float*>(data_location);
        break;
    case 2:
        mpfAudio_out_buffer = static_cast<float*>(data_location);
        break;
    case 3:
        mpfLevelValue = static_cast<float*>(data_location);
        break;
    
    default:
        break;
    }

}

void LV2Neuro::activate ()
{
    moBufferMemory.Clear();
}

void LV2Neuro::deactivate ()
{

}

void LV2Neuro::run (const uint32_t sample_count)
{
    if (!sample_count || !mpfAudio_in_buffer || !mpfAudio_out_buffer || !mpfLevelValue) return;

}

