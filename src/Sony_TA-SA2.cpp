
#include "Sony_TA-SA2.hpp"

#include <Arduino.h>
#include <IRsend.h>

#include <utility/util.h>
#include <utility>

namespace sony
{

const Topics_t & getTopics() {
    static Topics_t topics{
        std::make_pair("sony.ta-sa2.power"  , sendPower),
        std::make_pair("sony.ta-sa2.volume" , sendVolume),
        std::make_pair("sony.ta-sa2.input"  , sendInput)
    };
    return topics;
}

IRsend &getIRSend()
{
    constexpr uint16_t IR_PIN = 2;
    static IRsend irSender(IR_PIN);
    return irSender;
}

namespace bits
{

constexpr uint16_t repeatCount  = 3;

/**
 * A Sony command is defined as:
 * 12-bit version, 7 command bits, 5 address bits.
 * 15-bit version, 7 command bits, 8 address bits.
 * 20-bit version, 7 command bits, 5 address bits, 8 extended bits.
 */
template<uint16_t NumBits, uint16_t Command, uint16_t Address>
struct GenericIRCommand {
    static constexpr uint64_t commandBits   = 7;
    static constexpr uint64_t address       = Address;
    static constexpr uint64_t command       = 0xF7 & (Command << (NumBits-7));

    void send(uint64_t offset) {
        const auto payload = (command+offset) | address;
        getIRSend().sendSony(payload, NumBits, bits::repeatCount);
    }

    void send() {
        send(0);
    }
};

template<uint16_t Command>
using IRCommand = GenericIRCommand<12, Command, 16>;
using PowerOff  = IRCommand<21>;
using VolumeUp  = IRCommand<18>;
using VolumeDn  = IRCommand<19>;


Payload asPayload(const uint8_t *p)
{
    Payload result = htonl(*reinterpret_cast<const uint32_t *>(p));
    result <<= 32;
    result |= htonl(*reinterpret_cast<const uint32_t *>(p + 4));
}
}

    /*
     *
Publish received
  topic: sony.ta-sa2.power
  qos: 1
  dup: 0
  retain: 0
  len: 1
  index: 0
  total: 1
Publish received.
  topic: sony.ta-sa2.power
  qos: 1
  dup: 0
  retain: 0
  len: 1
  index: 0
  total: 1
Publish received.
  topic: sony.ta-sa2.input
  qos: 1
  dup: 0
  retain: 0
  len: 2
  index: 0
  total: 2
Publish received.
  topic: sony.ta-sa2.input
  qos: 1
  dup: 0
  retain: 0
  len: 5
  index: 0
  total: 5
Publish received.
  topic: sony.ta-sa2.volume
  qos: 1
  dup: 0
  retain: 0
  len: 2
  index: 0
  total: 2
     */
void forwardTopic(const char * topic, const char * payload, size_t len) {
    static const auto end = getTopics().end();
    auto iter = getTopics().find(topic);
    if(iter == end) {
        Serial.print("ERROR: Topic not found: ");
        Serial.println(topic);
        return;
    }
    auto & fn = iter->second;
    fn(payload, len);

}


void sendPower(const char * p, size_t len) {
    Serial.print("Power: 0x");
    Serial.println(p[0], HEX);

    bits::PowerOff    irCommand;
    irCommand.send();
}

void sendInput(const char * p, size_t len) {
    const String input(*reinterpret_cast<const uint8_t *>(p), HEX);
    Serial.print("Input:");
    Serial.println(input);

    if(memcmp(p, "Tuner", len) == 0) {

    } else if(memcmp(p, "CD", len) == 0) {

    } else if(memcmp(p, "Aux", len) == 0) {

    } else if(memcmp(p, "Phono", len) == 0) {

    }
}

void sendVolume(const char * p, size_t len) {
    const String input(*reinterpret_cast<const uint32_t*>(p), HEX);
    Serial.print("Volume: 0x");
    Serial.println(input);
}

}