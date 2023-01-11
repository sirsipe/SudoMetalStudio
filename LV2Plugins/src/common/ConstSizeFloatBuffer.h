#pragma once

template<long MEMSIZE>
class ConstSizeFloatBuffer
{
public:
    ConstSizeFloatBuffer() : 
        miPosition(0)
    {

    }

    void Clear()
    {
        miPosition = 0;
        for(int i = 0; i < MEMSIZE; i++)
            mArray[i] = 0.0f;
    }

    void Push(const float* data, const uint32_t iLen)
    {
        for (uint32_t i = 0; i < iLen; i++)
        {
            mArray[miPosition] = data[i];
            miPosition++;
            if (miPosition >= MEMSIZE)
                miPosition = 0;
        }

    }

    const float ReadPrevious(uint32_t iSamplesToPast)
    {

         if (iSamplesToPast >= MEMSIZE)
            return 0;      

        int32_t iPos = (int64_t)miPosition - (int64_t)(iSamplesToPast);
        while(iPos < 0)
            iPos += MEMSIZE;

        return mArray[iPos];
    }

private:
    float mArray[MEMSIZE] = { 0.0f };
    uint32_t miPosition;
};
