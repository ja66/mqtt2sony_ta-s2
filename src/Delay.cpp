#include <Esp.h>
#include <Arduino.h>

#include "Delay.hpp"

namespace user {

    void delay(std::chrono::milliseconds ms) {
        ::delay(static_cast<uint32_t>(ms.count()));
    }

    void hibernate(std::chrono::microseconds us) {
        ::delay(100); // rumors tell this is needed to get into deep sleep
        ESP.deepSleep(static_cast<uint32_t>(us.count()));
    }
}
