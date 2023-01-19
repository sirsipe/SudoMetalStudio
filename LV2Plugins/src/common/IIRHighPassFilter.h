#pragma once
#include <math.h>


class IIRHighPassFilter
{
public:
    IIRHighPassFilter(double dSample_rate) :
        mfSamplingTime(1.0f / dSample_rate),
        mpfCutoffFreq(nullptr),
        mfPreviousRes(0.f),
        mfPreviousInput(0.f)
    {
        
    }

    void LinkCutOffFreq(float* pfCutOffFreq)
    {
        mpfCutoffFreq = pfCutOffFreq;
    }

    float Process(float input)
    {
        if (!mpfCutoffFreq) return input;
        
        float RC = 1.0f / (2 * M_PI * *mpfCutoffFreq);
        float a = RC / (mfSamplingTime + RC);

        float fNext = a * (mfPreviousRes + input - mfPreviousInput);

        mfPreviousInput = input;
        mfPreviousRes = fNext;
       
        return fNext;
    }

private:

    float mfSamplingTime;
    float RC;
    float* mpfCutoffFreq;
    float mfPreviousRes;
    float mfPreviousInput;
};