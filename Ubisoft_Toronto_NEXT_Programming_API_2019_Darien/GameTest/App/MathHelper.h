#pragma once



const float EPSILON = 0.000001f;


template <class T> void Clamp(T &value, T min, T max)
{
    if (value > max)
    {
        value = max;
    }
    if (value < min)
    {
        value = min;
    }


}


