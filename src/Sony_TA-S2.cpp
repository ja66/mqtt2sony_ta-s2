
#include "Sony_TA-S2.hpp"

#include <Arduino.h>
#include <IRsend.h>

namespace sony {

    namespace {
        using Payload   = uint64_t;
    }


    IRsend &getIRSend()
    {
        constexpr uint16_t IR_PIN = 4;
        static IRsend irSender(IR_PIN);
        return irSender;
    }

    namespace rm_s1 {
        template<uint16_t NumBits>
        struct GenericIRCommand {
            void operator()(uint64_t Command) const {
                static constexpr uint16_t repeatCount  = 2;
                Serial.print("GenericIRCommand: 0x");
                Serial.println(static_cast<uint32_t>(Command), HEX);
                getIRSend().sendSony(Command, NumBits, repeatCount);
            }
        };

        using IRCommand = GenericIRCommand<11>;

        void sendIr(uint64_t value) {
            rm_s1::IRCommand{}(value);
        }
    } // end namespace rm_s1

    const char * getTopic() {
        static const char * svTopic = "sony/ta-s2/remote";
        return svTopic;
    }


    void forwardTopic(const char * topic, const char * payload, size_t len) {
        const Payload value = static_cast<Payload>(String(payload).toInt());
        rm_s1::sendIr(value);
    }


}
