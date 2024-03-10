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

#include "MQTTAsync.h"
#include "MQTTClient.h"

// #define USE_SSL
#define print(x) std::cout << x << std::endl;


class MqttCli
{
public:
    MqttCli(const char* address, const char* clientID,
            const char* username, const char* password, bool isAsync);
    ~MqttCli();

    // The core objects in order to send or receive msg
    MQTTClient client;
    MQTTClient_message message;
    MQTTClient_deliveryToken token;
    MQTTClient_connectOptions connOpts;

    MQTTAsync aclient;
    MQTTAsync_token atoken;
    MQTTAsync_message amessage;
    MQTTAsync_connectOptions aconnOpts;
    MQTTAsync_responseOptions aresOpts;
    MQTTAsync_disconnectOptions adisConnOpts;

    const char* address;
    const char* clientID;

    std::map<std::string, std::string> news;

    int connect();
    int subscribe(const char* topic);
    int publish(char* payload);

private:
    int QoS = 0;
    int timeout = 10000L;
    int finished = 0;

    bool isAsync = false;

    const char* topic;
    const char* username;
    const char* password;

    static void disconnect(void* context, char* cause);

    static void onDisconnect(void* context, MQTTAsync_successData* response);
    static void onDisconnectFailure(void* context, MQTTAsync_failureData* response);
    static void onSubscribe(void* context, MQTTAsync_successData* response);
    static void onSubscribeFailure(void* context, MQTTAsync_failureData* response);

    static int received(void* context, char* topic, int topicLen,
                        MQTTClient_message* message);
};


#endif  // _MQTT_H_
