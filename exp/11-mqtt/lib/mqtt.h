#ifndef _MQTT_H_
#define _MQTT_H_

#include <map>
#include <mutex>
#include <thread>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // for "strlen"
#include <unistd.h>    // for "usleep" & "sleep"
#include <iostream>

#include "MQTTClient.h"

#define print(x) std::cout << x << std::endl;


class MqttCli
{
public:
    MqttCli(const char* address, const char* clientID,
            const char* username, const char* password);
    ~MqttCli();

    // The core objects in order to send or receive msg
    MQTTClient client;
    MQTTClient_message message;
    MQTTClient_deliveryToken token;
    MQTTClient_connectOptions connOpts;

    const char* address;
    const char* clientID;

    int connect();
    int subscribe(const char* topic);
    int publish(char* payload);

    int receive();

private:
    int QoS = 0;
    int timeout = 10000L;

    const char* topic;
    const char* username;
    const char* password;

    static int callBack(void* context, char* topic, int topicLen,
                        MQTTClient_message* message);
};


#endif  // _MQTT_H_
