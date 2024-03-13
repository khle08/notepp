#ifndef _MQTT_H_
#define _MQTT_H_

#include <map>
#include <mutex>
#include <thread>
#include <vector>
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

    MQTTAsync aclient;
    MQTTAsync_token atoken;
    MQTTAsync_message amessage;
    MQTTAsync_disconnectOptions adisConnOpts;

    const char* address;
    const char* clientID;

    int days = 3;       // Maximum keep alive time period
    int connected = 0;  // 0: false / 1: true
    std::map<std::string, std::string> news;

    int connect(std::vector<std::string>& topicVec);
    int publish(std::string& topic, char* payload);

    std::string getMsg(std::string& topic);

private:
    int QoS = 0;
    int timeout = 86400L;
    int finished = 0;

    bool isAsync = false;

    // const char* topic;  // useless
    const char* username;
    const char* password;
    std::vector<std::string> topicVec;

    int init();
    int subscribe(std::string& topic);

    static void disconnect(void* context, char* cause);

    // Callback funcs only for
    static void onSend(void* context, MQTTAsync_successData* response);
    static void onConnect(void* context, MQTTAsync_successData* response);
    static void onSubscribe(void* context, MQTTAsync_successData* response);
    static void onDisconnect(void* context, MQTTAsync_successData* response);

    static void onSendFailure(void* context, MQTTAsync_failureData* response);
    static void onConnectFailure(void* context, MQTTAsync_failureData* response);
    static void onSubscribeFailure(void* context, MQTTAsync_failureData* response);
    static void onDisconnectFailure(void* context, MQTTAsync_failureData* response);

    static int received(void* context, char* topic, int topicLen,
                        MQTTClient_message* message);
    static int areceived(void* context, char* topicName, int topicLen, 
                         MQTTAsync_message* message);

};


#endif  // _MQTT_H_
