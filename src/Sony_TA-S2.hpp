#pragma once

#include <IRsend.h>
#include <map>
#include <WString.h>
#include <functional>

namespace sony {
    using Payload   = uint64_t;

    /**
     * Get global instance of IRSend
     * @return IRSend reference
     */
    IRsend & getIRSend();

    const char * getTopic();

    /**
     * Invoked by asyncMqtt, it has to match the signature
     * @param topic ascii string
     * @param payload (zero terminated?) string
     * @len   the number of characters in the (zero terminated?) payload
     */
    void forwardTopic(const char * topic, const char * payload, size_t len);

}

