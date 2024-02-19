
#include <map>
#include <mutex>
#include <thread>
#include <string>

#include "mqtt.h"


int main(int argc, char *argv[])
{
    MqttCli* client = new MqttCli("tcp://guardingeyeai.com:8883",
                                  "mqttx_38c419c3",
                                  "emqx",
                                  "public");

    int res = client->connect();
    if (res < 0) {
        delete client;
        return -1;
    }

    char payload[16];
    res = client->subscribe("1234");

    for (int i = 0; i < 100; i += 1) {
        snprintf(payload, 16, "message-%d", i);
        res = client->publish(payload);

        sleep(1);
    }

    delete client;
    return 0;
}

