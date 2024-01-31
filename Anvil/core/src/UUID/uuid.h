#include "../Base/macros.hpp"

#include <iostream>
#include <random>
#include <iomanip>

namespace Anvil{

    class ANV_API UuID{
        public:
        UuID() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 15);

            const char* hexDigits = "0123456789abcdef";
            std::string uuid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
            int index = 0;

            for (char& c : uuid) {
                if (c == 'x') {
                    int randomValue = dis(gen);
                    c = hexDigits[randomValue];
                } else if (c == 'y') {
                    int randomValue = dis(gen) & 0x3 | 0x8; // To ensure the 'y' character is '4' or '5'
                    c = hexDigits[randomValue];
                }
                index++;
            }

            m_uuid = uuid;
        }

        std::string GetUUID()
        {
            return m_uuid;
        }

        private:
        std::string m_uuid;
    };
    
}