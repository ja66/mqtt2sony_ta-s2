
#include "Sony_TA-SA2.hpp"

#include <Arduino.h>
#include <IRsend.h>

#include <utility/util.h>
#include <utility>

namespace sony {

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

    namespace rm_s1 {
        template<uint16_t NumBits, uint64_t Command>
        struct GenericIRCommand {

            static constexpr uint16_t repeatCount  = 3;

            void operator()() const {
                getIRSend().sendSony(Command, NumBits, repeatCount);
            }
        };

        template<uint16_t Command>
        using IRCommand  = GenericIRCommand<12, Command>;

        //   KEY_POWER                0x0000000000000A81        #  Was: power
        //   KEY_TAPE                 0x0000000000000C41        #  Was: tape
        //   tape-a-fast-rew          0x0000000000000CC1
        //   tape-a-rew               0x0000000000000EC1
        //   tape-a-fwd               0x00000000000004C1
        //   tape-a-fast-fwd          0x00000000000002C1
        //   tape-a-stop              0x00000000000001C1
        //   tape-a-pause             0x00000000000009C1
        //   tape-a-sync              0x0000000000000FC1
        //   tape-a-rec               0x00000000000006C1
        //   tape-b-fast-rew          0x0000000000000D8E
        //   tape-b-rew               0x000000000000004E
        //   tape-b-fwd               0x000000000000058E
        //   tape-b-fast-fwd          0x000000000000038E
        //   tape-b-stop              0x000000000000018E
        //   tape-b-pause             0x000000000000098E
        //   tape-b-sync              0x0000000000000F8E
        //   tape-b-rec               0x000000000000078E
        //   KEY_CD                   0x0000000000000A41        #  Was: cd
        //   cd-play                  0x00000000000004D1
        //   cd-pause                 0x00000000000009D1
        //   cd-stop                  0x00000000000001D1
        //   cd-time                  0x0000000000000151
        //   cd-skip-rev              0x00000000000000D1
        //   cd-skip-fwd              0x00000000000008D1
        //   cd-continue              0x0000000000000B91
        //   cd-program               0x0000000000000F91
        //   cd-repeat                0x0000000000000351
        //   cd-check                 0x0000000000000B11
        //   cd-clear                 0x0000000000000F11
        //   cd->12                   0x0000000000000E51
        //   cd-1                     0x0000000000000011
        //   cd-2                     0x0000000000000811
        //   cd-3                     0x0000000000000411
        //   cd-4                     0x0000000000000C11
        //   cd-5                     0x0000000000000211
        //   cd-6                     0x0000000000000A11
        //   cd-7                     0x0000000000000611
        //   cd-8                     0x0000000000000E11
        //   cd-9                     0x0000000000000111
        //   cd-10                    0x0000000000000051
        //   cd-11                    0x0000000000000851
        //   cd-12                    0x0000000000000451
        //   KEY_TUNER                0x0000000000000841        #  Was: tuner
        //   tuner-band               0x0000000000000F16
        //   tuner-clear              0x0000000000000056
        //   tuner->12                0x0000000000000656
        //   tuner-1                  0x0000000000000016
        //   tuner-2                  0x0000000000000816
        //   tuner-3                  0x0000000000000416
        //   tuner-4                  0x0000000000000C16
        //   tuner-5                  0x0000000000000216
        //   tuner-6                  0x0000000000000A16
        //   tuner-7                  0x0000000000000616
        //   tuner-8                  0x0000000000000E16
        //   tuner-9                  0x0000000000000116
        //   tuner-10                 0x0000000000000916
        //   tuner-11                 0x0000000000000516
        //   tuner-12                 0x0000000000000D16
        //   eq                       0x0000000000000EE6
        //   KEY_UP                   0x00000000000001E6        #  Was: up
        //   KEY_DOWN                 0x00000000000009E6        #  Was: down
        //   KEY_LEFT                 0x00000000000005E6        #  Was: left
        //   KEY_RIGHT                0x0000000000000DE6        #  Was: right
        //   eq>12                    0x0000000000000629
        //   eq-bgm                   0x00000000000001C9
        //   eq-vocal                 0x00000000000009C9
        //   eq-heavy                 0x00000000000005C9
        //   eq-wm                    0x0000000000000DC9
        //   eq-car                   0x00000000000003C9
        //   eq-file1                 0x0000000000000BC9
        //   eq-file2                 0x00000000000007C9
        //   eq-file3                 0x0000000000000AC9
        //   eq-file4                 0x0000000000000B89
        //   eq-file5                 0x0000000000000789
        //   phono                    0x0000000000000041
        //   dat                      0x0000000000000621
        //   KEY_VIDEO                0x0000000000000441        #  Was: video
        //   surround                 0x0000000000000FC6
        //   dbfb                     0x00000000000008C6
        //   memory                   0x0000000000000709
        //   KEY_VOLUMEUP             0x0000000000000481        #  Was: vol+
        //   KEY_VOLUMEDOWN           0x0000000000000C81        #  Was: vol-


        using Power      = IRCommand< 0x0000000000000A81ULL >;
        using VolumeUp   = IRCommand< 0x0000000000000481ULL >;
        using VolumeDn   = IRCommand< 0x0000000000000C81ULL >;
        using InputTuner = IRCommand< 0x0000000000000481ULL >;
        using InputDat   = IRCommand< 0x0000000000000621ULL >;
        using InputCD    = IRCommand< 0x0000000000000A41ULL >;
        using InputTape  = IRCommand< 0x0000000000000C41ULL >;
        using InputPhono = IRCommand< 0x0000000000000041ULL >;

        Payload asPayload(const uint8_t *p) {
            Payload result = htonl(*reinterpret_cast<const uint32_t *>(p));
            result <<= 32;
            result |= htonl(*reinterpret_cast<const uint32_t *>(p + 4));
        }
    } // end namespace rm_s1

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


    void sendPower(const char * /*p*/, size_t /*len*/) {
        rm_s1::Power();
    }

    void sendInput(const char * p, size_t len) {
        const String input(*reinterpret_cast<const uint8_t *>(p), HEX);
        Serial.print("Input:");
        Serial.println(input);

        if(memcmp(p, "Tuner", len) == 0) {
            rm_s1::InputTuner();
        } else if(memcmp(p, "CD", len) == 0) {
            rm_s1::InputCD();
        } else if(memcmp(p, "Aux", len) == 0) {
            rm_s1::InputDat();
        } else if(memcmp(p, "Phono", len) == 0) {
            rm_s1::InputPhono();
        }
    }

    void sendVolume(const char * p, size_t len) {
        const String input(*reinterpret_cast<const uint32_t*>(p), HEX);
        Serial.print("Volume: 0x");
        Serial.println(input);

        // this is a bit tricky: I get a number or the desired
        // volume but cannot know the initial volume.
        // To change volume the commands rm_s1::[VolumeUp(),VolumeDn()]
        // have to be repeated until the desired volume is reached.
        // Ah!, I could interpret the number as change request...
    }

}