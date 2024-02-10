
#include <map>
#include <mutex>
#include <thread>
#include <string>
#include <iostream>
#include <unistd.h>    // for "usleep"

#include "MQTTClient.h"

#define print(x) std::cout << x << std::endl


int main(int argc, char const *argv[])
{

    print("\n===== paho.mqtt testing [start] =====");

    MQTTClient client("localhost:1883", "publisher", MQTT_create_options(MQTTVERSION_5));

    print(  "===== paho.mqtt testing [ end ] =====\n");

    return 0;
}
