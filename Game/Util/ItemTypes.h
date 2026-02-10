#pragma once
#include <cstdint>

namespace Wanted
{
    enum class EItemType : uint8_t
    {
        SpeedUp,
        PowerUp,
        RangeUp
    };

    struct IItemReceiver
    {
        virtual ~IItemReceiver() = default;
        virtual void ApplyItem(EItemType type, float value) = 0;
    };
}