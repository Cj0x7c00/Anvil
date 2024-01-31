#include "uuid.h"

Anvil::UuID::UuID(){
    auto t = Time::Profile("UuID()");
    std::random_device rd;
    std::mt19937 gen(rd()); // this may be too slow
    std::uniform_int_distribution<> dis(0, 15);

    const char* hexDigits = "0123456789abcdef";
    std::string uuid = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
    int index = 0;

    for (char& c : uuid) {
        if (c == 'x') {
            int randomValue = dis(gen);
            c = hexDigits[randomValue];
        }
        else if (c == 'y') {
            int randomValue = dis(gen) & 0x3 | 0x8; // To ensure the 'y' character is '4' or '5'
            c = hexDigits[randomValue];
        }
        index++;
    }

    m_uuid = uuid;
}