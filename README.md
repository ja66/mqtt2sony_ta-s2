# mqtt2sony_ta-sa2
Listen to MQTT topics and convert them to IR codes (SIRCS) so that 
the old stereo can be use remote controlled using a smartphone

Since I haven't used WiFiManager yet I created a little wlan.cfg file which is not git managed
It should have this content:

    '-DWIFI_SSID="secret"'
    '-DWIFI_PASSWORD="less_secret"'
    '-DMQTT_HOST="mqtt.localnet"'

