#pragma once
#include "../Base/macros.hpp"
#include "../Util/Time/Time.h"
#include <iostream>
#include <random>
#include <iomanip>

namespace Anvil{

    class ANV_API UuID{
    public:
        UuID();

        std::string GetUUID()
        {
            return m_uuid;
        }

    private:
        std::string m_uuid;
    };
    
}