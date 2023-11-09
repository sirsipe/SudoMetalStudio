#pragma once

#include <cstddef>

class RingBuffer
{
public:

    /// @brief Constructor. Allocates the underlying buffer to the heap.
    /// @param lCapasity Capasity of the buffer
    RingBuffer(const size_t lCapasity) : 
        mpaBuffer(nullptr),
        mlCapasity(lCapasity),
        mlCurrentIndex(0),
        mfZero(0)
    {
        if (mlCapasity)
        {   
            mpaBuffer = new float[mlCapasity]; 
            Clear();
        }
    }

    /// @brief Destructor; deletes the underlying buffer.
    ~RingBuffer()
    {
        if (mpaBuffer)
        {
            delete[] mpaBuffer;
            mpaBuffer = nullptr;
        }
    }

    /// @brief Sets the buffer to all zeros.
    void Clear()
    {
        if (mpaBuffer)
        {
            for(size_t i = 0; i < mlCapasity; i++)
            {
                mpaBuffer[i] = mfZero;
            }
        }
    }

    /// @brief Store array to the buffer.
    /// @param paSamples First element of the array which values are copied to the buffer
    /// @param lCount Amount of elements in the array
    void Push(const float* paSamples, const size_t lCount)
    {
        if (!mpaBuffer || !paSamples)
            return;

        for(size_t i = 0; i < lCount; i++)
        {
            mpaBuffer[mlCurrentIndex] = paSamples[i];
            mlCurrentIndex++;
            
            if (mlCurrentIndex == mlCapasity)
                mlCurrentIndex = 0;
        }
    }

    /// @brief Capacity of the buffer
    /// @return Capacity of the buffer
    constexpr size_t Capasity() const
    {
        return mlCapasity;
    }

    /// @brief Accessor for the buffer
    /// @param lIndex zero = last pushed value. Larger the index, older the value. Asking over capasity returns zero.
    /// @return constant reference to the buffer value; zero if
    const float& operator[](const size_t lIndex) const
    {

        if (!mpaBuffer || lIndex >= mlCapasity) 
            return mfZero;
        
        if (lIndex > mlCurrentIndex)
            return mpaBuffer[mlCurrentIndex + mlCapasity - lIndex];

        return mpaBuffer[mlCurrentIndex - lIndex];
    }
    

private:
    // Hide default constructor
    RingBuffer();

private:

    const float mfZero;
    const size_t mlCapasity;
    float* mpaBuffer;
    size_t mlCurrentIndex;

};
