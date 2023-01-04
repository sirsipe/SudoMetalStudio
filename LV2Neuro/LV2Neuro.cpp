/* include libs */
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include "lv2.h"

/* class definition */
class LV2Neuro 
{
private:
    float* audio_in_ptr;
    float* audio_learn_ptr;
    float* audio_out_ptr;
    float* level_ptr;
    double rate;

public:
    LV2Neuro (const double sample_rate);
    void connectPort (const uint32_t port, void* data_location);
    void activate ();
    void run (const uint32_t sample_count);
};

LV2Neuro::LV2Neuro (const double sample_rate) :
    audio_in_ptr (nullptr),
    audio_learn_ptr (nullptr),
    audio_out_ptr (nullptr),
    level_ptr (nullptr),
    rate (sample_rate)
{

}

void LV2Neuro::connectPort (const uint32_t port, void* data_location)
{
    switch (port)
    {
    case 0:
        audio_in_ptr = (float*) data_location;
        break;
    case 1:
        audio_learn_ptr = (float*) data_location;
        break;
    case 2:
        audio_out_ptr = (float*) data_location;
        break;
    case 3:
        level_ptr = (float*) data_location;
        break;
    
    default:
        break;
    }
}

void LV2Neuro::activate ()
{
    
}

void LV2Neuro::run (const uint32_t sample_count)
{
    if (!(audio_in_ptr) || (!audio_out_ptr) || (!level_ptr)) return;

    for (uint32_t i = 0; i < sample_count; ++i)
    {
        audio_out_ptr[i] = audio_in_ptr[i] * *level_ptr;
    }
}

/* internal core methods */
static LV2_Handle instantiate (const struct LV2_Descriptor *descriptor, double sample_rate, const char *bundle_path, const LV2_Feature *const *features)
{
    LV2Neuro* m = new LV2Neuro (sample_rate);
    return m;
}

static void connect_port (LV2_Handle instance, uint32_t port, void *data_location)
{
    LV2Neuro* m = (LV2Neuro*) instance;
    if (m) m->connectPort (port, data_location);
}

static void activate (LV2_Handle instance)
{
    LV2Neuro* m = (LV2Neuro*) instance;
    if (m) m->activate ();
}

static void run (LV2_Handle instance, uint32_t sample_count)
{
    LV2Neuro* m = (LV2Neuro*) instance;
    if (m) m->run (sample_count);
}

static void deactivate (LV2_Handle instance)
{
    /* not needed here */
}

static void cleanup (LV2_Handle instance)
{
    LV2Neuro* m = (LV2Neuro*) instance;
    if (m) delete m;
}

static const void* extension_data (const char *uri)
{
    return NULL;
}

/* descriptor */
static LV2_Descriptor const descriptor =
{
    "https://github.com/sirsipe/SudoMetalStudio/LV2Neuro",
    instantiate,
    connect_port,
    activate,
    run,
    deactivate /* or NULL */,
    cleanup,
    extension_data /* or NULL */
};

/* interface */
extern "C" LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor (uint32_t index)
{
    if (index == 0) return &descriptor;
    else return NULL;
}