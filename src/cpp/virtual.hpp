extern "C"
{
    #include "game/memory.h"
}

template<typename T>
T* toVirtual(const T* segmented)
{
    return (T*) segmented_to_virtual(segmented);
}