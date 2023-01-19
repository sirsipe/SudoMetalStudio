#pragma once

#include "lv2.h"
#include "lv2/ui/ui.h"

namespace LV2Entry
{
    template<class DSP>
    static LV2_Handle instantiate (const struct LV2_Descriptor* descriptor, double sample_rate, const char *bundle_path, const LV2_Feature *const *features)
    {
        DSP* m = new DSP(sample_rate);
        return m;
    }

    template<class DSP>
    static void connect_port (LV2_Handle instance, uint32_t port, void *data_location)
    {
        DSP* m = static_cast<DSP*>(instance);
        if (m) m->connectPort (port, data_location);
    }

    template<class DSP>
    static void activate (LV2_Handle instance)
    {
        DSP* m = static_cast<DSP*>(instance);
        if (m) m->activate ();
    }

    template<class DSP>
    static void run (LV2_Handle instance, uint32_t sample_count)
    {
        DSP* m = static_cast<DSP*>(instance);
        if (m) m->run (sample_count);
    }

    template<class DSP>
    static void deactivate (LV2_Handle instance)
    {
        DSP* m = static_cast<DSP*>(instance);
        if (m) m->deactivate ();
    }

    template<class DSP>
    static void cleanup (LV2_Handle instance)
    {
        DSP* m = static_cast<DSP*>(instance);
        if (m) delete m;
    }

    static const void* extension_data (const char *uri)
    {
        return nullptr;
    }
/*
    template<class UI>
    static LV2_Handle UIinstantiate (const struct LV2_Descriptor* descriptor, const char* plugin_uri, 
            const char* bundle_path, LV2UI_Write_Function write_function, LV2UI_Controller controller, 
            LV2UI_Widget *widget, const LV2_Feature *const *features)
    {
        UI* m = new UI(write_function, controller, widget);
        return m;
    }

    template<class UI>
    static LV2_Handle UIcleanup (LV2UI_Handle ui)
    {
        UI* m = static_cast<UI*>(ui);
        if (m) delete m;
    }
    
    template<class UI>
    static void UIport_event(LV2UI_Handle ui, uint32_t port_index, 
        uint32_t buffer_size,  uint32_t format, const void *buffer)
    {
        UI* m = static_cast<UI*>(ui);
        if (m) m ->port_event(port_index, buffer_size, format, buffer);
    }

    static const void* UIextension_data (const char *uri)
    {
        return nullptr;
    }*/
}

#define EXPORT_PLUGIN_DESCRIPTOR(classname, uri) \
static LV2_Descriptor const descriptor = \
{ \
    uri, \
    LV2Entry::instantiate<classname>, \
    LV2Entry::connect_port<classname>, \
    LV2Entry::activate<classname>, \
    LV2Entry::run<classname>, \
    LV2Entry::deactivate<classname>, \
    LV2Entry::cleanup<classname>, \
    LV2Entry::extension_data \
}; \
\
extern "C" LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor (uint32_t index)  \
{ \
    if (index == 0) return &descriptor; \
    else return nullptr; \
}

/*
#define EXPORT_PLUGIN_UI_DESCRIPTOR(classname, uri) \
static LV2UI_Descriptor const uiDescriptior = \
{ \
    uri, \
    LV2Entry::UIinstantiate<classname>, \
    LV2Entry::UIcleanup<classname>, \
    LV2Entry::UIport_event<classname>, \
    LV2Entry::UIextension_data \
} \
\
extern "C" LV2_SYMBOL_EXPORT const LV2UI_Descriptor* lv2ui_descriptor (uint32_t index) \
{ \
    if (index == 0) return &uiDescriptior; \
    else return nullptr; \
}
*/