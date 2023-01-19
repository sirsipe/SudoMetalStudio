
#include "SMSStereoDelay.h"

SMSStereoDelay::SMSStereoDelay (const double sample_rate) :
    mpfAudio_in_buffer(nullptr),
    mpfAudio_out_buffer_l(nullptr),
    mpfAudio_out_buffer_r(nullptr),
    mpfLevelValue(nullptr),
    mpfDelayLValue(nullptr),
    mpfDelayRValue(nullptr),
    mpfDecayValue(nullptr), 
    mdSample_rate(sample_rate)
{

}

void SMSStereoDelay::connectPort (const uint32_t port, void* data_location)
{

    switch (port)
    {
    case 0:
        mpfAudio_in_buffer = static_cast<float*>(data_location);
        break;
    case 1:
        mpfAudio_out_buffer_l = static_cast<float*>(data_location);
        break;
    case 2:
        mpfAudio_out_buffer_r = static_cast<float*>(data_location);
        break;
    case 3:
        mpfEnableValue = static_cast<float*>(data_location);
        break;
    case 4:
        mpfLevelValue = static_cast<float*>(data_location);
        break;
    case 5:
        mpfDelayLValue = static_cast<float*>(data_location);
        break;
    case 6:
        mpfDelayRValue = static_cast<float*>(data_location);
        break;
    case 7:
        mpfDecayValue = static_cast<float*>(data_location);
        break;
    default:
        break;
    }

}

void SMSStereoDelay::activate ()
{
    moBufferMemory.Clear();
}

void SMSStereoDelay::deactivate ()
{

}

void SMSStereoDelay::run (const uint32_t sample_count)
{
    // Check connection validity.
    if (!sample_count || !mpfAudio_in_buffer || !mpfAudio_out_buffer_l || !mpfAudio_out_buffer_r
        || !mpfEnableValue || !mpfLevelValue || !mpfDelayLValue || !mpfDelayRValue || !mpfDecayValue) 
        return;

    // Delay is given in seconds, so calculate 
    // corresponding sample gap based on sample rate.
    uint32_t delayGap_l = mdSample_rate * *mpfDelayLValue;
    uint32_t delayGap_r = mdSample_rate * *mpfDelayRValue;

    for (uint32_t i = 0; i < sample_count; i++)
    {
        // Pass the dry signal
        mpfAudio_out_buffer_l[i] = mpfAudio_in_buffer[i]; 
        mpfAudio_out_buffer_r[i] = mpfAudio_in_buffer[i]; 

        if (*mpfEnableValue) // Check enabled.
        {
            // Add delay with 10 step decay from the buffer.
            float decay =  *mpfDecayValue;
            for (uint32_t j = 0; j < 10; j++)
            {
            
                mpfAudio_out_buffer_l[i] += *mpfLevelValue * decay * moBufferMemory.ReadPrevious(delayGap_l * (j + 1) - i);     
                mpfAudio_out_buffer_r[i] += *mpfLevelValue * decay * moBufferMemory.ReadPrevious(delayGap_r * (j + 1) - i);     
            
                decay *= decay;
            }
        }    
    }

    // Store new samples to the buffer.
    moBufferMemory.Push(mpfAudio_in_buffer, sample_count);
}

