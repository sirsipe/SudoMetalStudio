
#include "REPLACE_ME.h"
#include <math.h>

/// @brief Constructor initializes all pointers to null
/// @param sample_rate Sample rate to use
REPLACE_ME::REPLACE_ME (const double sample_rate) :
    mdSampleRate(sample_rate),
    mpfAudio_in_buffer(nullptr),
    mpfAudio_out_buffer(nullptr),
    mpfEnableValue(nullptr)
{
    
}

/// @brief Plugin host application passes the buffer on port connection for each port decribed in the .ttl file
/// @param port Port index in the .ttl file
/// @param data_location pointer to the buffer of the port.
void REPLACE_ME::connectPort (const uint32_t port, void* data_location)
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

/// @brief Plugin is activated
void REPLACE_ME::activate ()
{

}

/// @brief Plugin is deactivated
void REPLACE_ME::deactivate ()
{

}

/// @brief This is the DSP function. It must be fast and thus not allowed to e.g. allocate memory.
/// @param sample_count 
void REPLACE_ME::run (const uint32_t sample_count)
{
    // Check connection validity.
    if (!mpfAudio_out_buffer || !mpfAudio_in_buffer || !mpfEnableValue) 
        return;


    // Simply pass the signal from input buffer to output
    // buffer in case the enable is non-zero. Else pass 0 for output.
    for (uint32_t i = 0; i < sample_count; ++i)
    {
        if (*mpfEnableValue)
            mpfAudio_out_buffer[i] = mpfAudio_in_buffer[i];
        else
            mpfAudio_out_buffer[i] = 0;
    }


}

