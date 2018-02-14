#pragma once

#include <chrono>

namespace user {

    /**
     * Encapsulate Arduino delay function typesafe
     * @method delay
     * @param  ms    [description]
     */
    void delay(std::chrono::milliseconds ms);


    void hibernate(std::chrono::microseconds us);
}
