
#include "SMSAmateurDelay.h"

SMSAmateurDelay::SMSAmateurDelay (const double sample_rate) :
    mpfAudio_in_buffer(nullptr),
    mpfAudio_out_buffer(nullptr),
    mpfLevelValue(nullptr),
    mpfDelayValue(nullptr),
    mpfDecayValue(nullptr), 
    mdSample_rate(sample_rate)
{

}

void SMSAmateurDelay::connectPort (const uint32_t port, void* data_location)
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
    case 3:
        mpfLevelValue = static_cast<float*>(data_location);
        break;
    case 4:
        mpfDelayValue = static_cast<float*>(data_location);
        break;
    case 5:
        mpfDecayValue = static_cast<float*>(data_location);
        break;
    default:
        break;
    }

}

void SMSAmateurDelay::activate ()
{
    moBufferMemory.Clear();
}

void SMSAmateurDelay::deactivate ()
{

}

void SMSAmateurDelay::run (const uint32_t sample_count)
{
    // Check connection validity.
    if (!sample_count || !mpfAudio_in_buffer || !mpfAudio_out_buffer 
        || !mpfEnableValue || !mpfLevelValue || !mpfDelayValue|| !mpfDecayValue) 
        return;

    // Delay is given in seconds, so calculate 
    // corresponding sample gap based on sample rate.
    uint32_t delayGap = mdSample_rate * *mpfDelayValue;
    
    for (uint32_t i = 0; i < sample_count; i++)
    {
        // Pass the dry signal
        mpfAudio_out_buffer[i] = mpfAudio_in_buffer[i]; 
        
        if (*mpfEnableValue) // Check enabled.
        {
            // Add delay with 10 step decay from the buffer.
            float decay =  *mpfDecayValue;
            for (uint32_t j = 0; j < 10; j++)
            {
                mpfAudio_out_buffer[i] += *mpfLevelValue * decay * moBufferMemory.ReadPrevious(delayGap * (j + 1) - i);     
                decay *= decay;
            }
        }    
    }

    // Store new samples to the buffer.
    moBufferMemory.Push(mpfAudio_in_buffer, sample_count);
}

