
#include "SMSNorthernPerkele.h"
#include <math.h>


SMSNorthernPerkele::SMSNorthernPerkele (const double sample_rate) :
    mpfAudio_in_buffer(nullptr),
    mpfAudio_out_buffer(nullptr),
    mpfEnableValue(nullptr),
    mpfDriveValue(nullptr),
    mpfVolumeValue(nullptr),
    mpfHighPassValue(nullptr),
    mpfLowPassValue(nullptr),
    mpfHighPassGainValue(nullptr),
    mpfLowPassGainValue(nullptr),
    mdSample_rate(sample_rate),
    mLowPassFilter(sample_rate),
    mHighPassFilter(sample_rate)
{

}

void SMSNorthernPerkele::connectPort (const uint32_t port, void* data_location)
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
        mpfDriveValue = static_cast<float*>(data_location);
        break;
    case 4:
        mpfVolumeValue = static_cast<float*>(data_location);
        break;
    case 5:
        mpfLowPassValue = static_cast<float*>(data_location);
        mLowPassFilter.LinkCutOffFreq(mpfLowPassValue);
        break;
    case 6:
        mpfLowPassGainValue = static_cast<float*>(data_location);
        break;
    case 7:
        mpfHighPassValue = static_cast<float*>(data_location);
        mHighPassFilter.LinkCutOffFreq(mpfHighPassValue);
        break;
    case 8:
        mpfHighPassGainValue = static_cast<float*>(data_location);
        break;
    default:
        break;
    }

}

void SMSNorthernPerkele::activate ()
{
    
}

void SMSNorthernPerkele::deactivate ()
{

}

void SMSNorthernPerkele::run (const uint32_t sample_count)
{
    // Check connection validity.
    if (!sample_count || !mpfAudio_in_buffer || !mpfAudio_out_buffer 
        || !mpfEnableValue || !mpfDriveValue || !mpfVolumeValue) 
        return;

    for (uint32_t i = 0; i < sample_count; i++)
    {
        
        if (*mpfEnableValue)
        {
            float val = mpfAudio_in_buffer[i];

            // Apply highpass
            val = *mpfHighPassGainValue * mHighPassFilter.Process(val) + (1-*mpfHighPassGainValue) * val;
            
            // Apply satan
            val = tanh(*mpfDriveValue * val);

            // Apply lowpass
            val = *mpfLowPassGainValue * mLowPassFilter.Process(val) + (1-*mpfLowPassGainValue) * val;

            // Scale with volume
            mpfAudio_out_buffer[i] = val * *mpfVolumeValue; 
            
        }    
        else // Pass the dry signal
            mpfAudio_out_buffer[i] = mpfAudio_in_buffer[i]; 
        
    }

}

