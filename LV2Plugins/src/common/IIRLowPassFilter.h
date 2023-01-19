#pragma once
#include <math.h>

class IIRLowPassFilter
{
public:
    IIRLowPassFilter(double dSample_rate) :
        mfSamplingTime(1.0f / dSample_rate),
        mpfCutoffFreq(nullptr),
        mfPrevious(0.f)
    {
        
    }

    void LinkCutOffFreq(float* pfCutOffFreq)
    {
        mpfCutoffFreq = pfCutOffFreq;
    }

    float Process(float value)
    {
        if (!mpfCutoffFreq) return value;

        float RC = 1.0f / (2 * M_PI * *mpfCutoffFreq);
        float a = mfSamplingTime / (mfSamplingTime + RC);
        float b = RC / (mfSamplingTime + RC);
        
        float res = a * value + b * mfPrevious;
        mfPrevious = res;
        return res;
    }

private:
    float mfSamplingTime;
    float RC;
    float* mpfCutoffFreq;
    float mfPrevious;
};