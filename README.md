# mqtt2sony_ta-sa2
Listen to MQTT topics and convert them to IR codes (SIRCS) so that
the old stereo can be use remote controlled using a smartphone

Since I haven't used WiFiManager yet I created a little wlan.cfg file which is not git managed
It should have this content:

    '-DWIFI_SSID="secret"'
    '-DWIFI_PASSWORD="less_secret"'
    '-DMQTT_HOST="mqtt.localnet"'

These 12 bit IR commands seem to work (found under a remote repository which I don't remember)

12 bit

Pwr     0xA81 = 2689 = 0b101010000001
Vol-    0xC81 = 3201 = 0b110010000001
Vol+    0x481 = 1153 = 0b010010000001



    KEY_POWER                0x0000000000000A81        #  Was: power
    KEY_TAPE                 0x0000000000000C41        #  Was: tape
    tape-a-fast-rew          0x0000000000000CC1
    tape-a-rew               0x0000000000000EC1
    tape-a-fwd               0x00000000000004C1
    tape-a-fast-fwd          0x00000000000002C1
    tape-a-stop              0x00000000000001C1
    tape-a-pause             0x00000000000009C1
    tape-a-sync              0x0000000000000FC1
    tape-a-rec               0x00000000000006C1
    tape-b-fast-rew          0x0000000000000D8E
    tape-b-rew               0x000000000000004E
    tape-b-fwd               0x000000000000058E
    tape-b-fast-fwd          0x000000000000038E
    tape-b-stop              0x000000000000018E
    tape-b-pause             0x000000000000098E
    tape-b-sync              0x0000000000000F8E
    tape-b-rec               0x000000000000078E
    KEY_CD                   0x0000000000000A41        #  Was: cd
    cd-play                  0x00000000000004D1
    cd-pause                 0x00000000000009D1
    cd-stop                  0x00000000000001D1
    cd-time                  0x0000000000000151
    cd-skip-rev              0x00000000000000D1
    cd-skip-fwd              0x00000000000008D1
    cd-continue              0x0000000000000B91
    cd-program               0x0000000000000F91
    cd-repeat                0x0000000000000351
    cd-check                 0x0000000000000B11
    cd-clear                 0x0000000000000F11
    cd->12                   0x0000000000000E51
    cd-1                     0x0000000000000011
    cd-2                     0x0000000000000811
    cd-3                     0x0000000000000411
    cd-4                     0x0000000000000C11
    cd-5                     0x0000000000000211
    cd-6                     0x0000000000000A11
    cd-7                     0x0000000000000611
    cd-8                     0x0000000000000E11
    cd-9                     0x0000000000000111
    cd-10                    0x0000000000000051
    cd-11                    0x0000000000000851
    cd-12                    0x0000000000000451
    KEY_TUNER                0x0000000000000841        #  Was: tuner
    tuner-band               0x0000000000000F16
    tuner-clear              0x0000000000000056
    tuner->12                0x0000000000000656
    tuner-1                  0x0000000000000016
    tuner-2                  0x0000000000000816
    tuner-3                  0x0000000000000416
    tuner-4                  0x0000000000000C16
    tuner-5                  0x0000000000000216
    tuner-6                  0x0000000000000A16
    tuner-7                  0x0000000000000616
    tuner-8                  0x0000000000000E16
    tuner-9                  0x0000000000000116
    tuner-10                 0x0000000000000916
    tuner-11                 0x0000000000000516
    tuner-12                 0x0000000000000D16
    eq                       0x0000000000000EE6
    KEY_UP                   0x00000000000001E6        #  Was: up
    KEY_DOWN                 0x00000000000009E6        #  Was: down
    KEY_LEFT                 0x00000000000005E6        #  Was: left
    KEY_RIGHT                0x0000000000000DE6        #  Was: right
    eq>12                    0x0000000000000629
    eq-bgm                   0x00000000000001C9
    eq-vocal                 0x00000000000009C9
    eq-heavy                 0x00000000000005C9
    eq-wm                    0x0000000000000DC9
    eq-car                   0x00000000000003C9
    eq-file1                 0x0000000000000BC9
    eq-file2                 0x00000000000007C9
    eq-file3                 0x0000000000000AC9
    eq-file4                 0x0000000000000B89
    eq-file5                 0x0000000000000789
    phono                    0x0000000000000041
    dat                      0x0000000000000621
    KEY_VIDEO                0x0000000000000441        #  Was: video
    surround                 0x0000000000000FC6
    dbfb                     0x00000000000008C6
    memory                   0x0000000000000709
    KEY_VOLUMEUP             0x0000000000000481        #  Was: vol+
    KEY_VOLUMEDOWN           0x0000000000000C81        #  Was: vol-
