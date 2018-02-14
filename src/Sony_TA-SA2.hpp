#pragma once

#include <IRsend.h>
#include <map>
#include <WString.h>
#include <functional>

namespace sony {
    using Payload   = uint64_t;
    using SendFn_t  = std::function<void(const char*, size_t)>;
    using Topics_t  = std::map<String, SendFn_t>;


    void sendPower(const char *, size_t len);

    void sendInput(const char * p, size_t len);

    void sendVolume(const char * p, size_t len);

    namespace bits {
        /**
         * Converts a uint8_t array to a Payload
         * @param p pointing to a data area of 8 bytes
         */
        Payload asPayload(const uint8_t *p);
    }

    const Topics_t & getTopics();


    /**
     * Get global instance of IRSend
     * @return IRSend reference
     */
    IRsend & getIRSend();

    /**
     * Send Payload via IR
     * @param Payload
     */
    void sendIr(Payload payload);

    template<typename Callback>
    void subscribe(Callback && callback) {
        for (const auto & t : getTopics())
        {
            std::forward<Callback>(callback)(t.first.c_str());
        }
    }

    void forwardTopic(const char * topic, const char * payload, size_t len);

}

