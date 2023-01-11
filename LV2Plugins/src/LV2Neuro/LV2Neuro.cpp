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

    uint32_t delayGap = mdSample_rate * *mpfLevelValue; // Delay 0-1s
    
    for (uint32_t i = 0; i < sample_count; i++)
    {
        mpfAudio_out_buffer[i] = 0.5 * mpfAudio_in_buffer[i];
        for (uint32_t j = 1; j <= 10; j++)
        {
            float multp = 0.25 / j;
            mpfAudio_out_buffer[i] += multp * moBufferMemory.ReadPrevious(delayGap * j - i);
            
        }
        
    }

    // Store new samples to the buffer.
    moBufferMemory.Push(mpfAudio_in_buffer, sample_count);
}

