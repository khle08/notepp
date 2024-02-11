
#include <string>
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#include "MQTTClient.h"

#define ADDRESS     "tcp://guardingeyeai.com:8883"
#define USERNAME    "emqx"
#define PASSWORD    "public"
#define CLIENTID    "mqttx_38c419c3"
#define QOS         0
#define TOPIC       "1234"
#define TIMEOUT     10000L

void publish(MQTTClient client, const char *topic, char *payload) {
    MQTTClient_message message = MQTTClient_message_initializer;
    message.payload = payload;
    message.payloadlen = strlen(payload);
    message.qos = QOS;
    message.retained = 0;
    MQTTClient_deliveryToken token;
    MQTTClient_publishMessage(client, topic, &message, &token);
    MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Send `%s` to topic `%s` \n", payload, TOPIC);
}

int on_message(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    char *payload = (char*)message->payload;
    printf("Received `%s` from `%s` topic \n", payload, topicName);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

int main(int argc, char *argv[]) {
    int rc;
    MQTTClient client;

    const char* address = "tcp://guardingeyeai.com:8883";
    const char* clientid = "mqttx_38c419c3";
    const char* username = "emqx";
    const char* password = "public";

    MQTTClient_create(&client, address, clientid, 0, NULL);
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.username = username;
    conn_opts.password = password;
    MQTTClient_setCallbacks(client, NULL, NULL, on_message, NULL);
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    } else {
        printf("Connected to MQTT Broker!\n");
    }

    const char* topic = "1234";
    int qos = 0;
    int timeout = 10000L;

    // subscribe topic
    MQTTClient_subscribe(client, topic, qos);
    char payload[16];
    for (int i = 0; i < 100; i += 1) {
        // publish message to broker
        // std::string payload = "message-" + std::to_string(i);
        snprintf(payload, 16, "message-%d", i);
        publish(client, topic, payload);
        sleep(1);
    }
    MQTTClient_disconnect(client, TIMEOUT);
    MQTTClient_destroy(&client);
    return rc;
}


// #include <map>
// #include <mutex>
// #include <thread>
// #include <string>
// #include <stdio.h>
// #include <stdlib.h>
// #include <iostream>
// #include <unistd.h>    // for "usleep"

// #include "MQTTClient.h"

// #define print(x) std::cout << x << std::endl

// #define ADDRESS "tcp://localhost:1883"
// #define CLIENTID "ExampleClientSub"
// #define TOPIC "MQTT Examples"
// #define PAYLOAD "Hello World!"
// #define QOS 1
// #define TIMEOUT 10000L

// volatile MQTTClient_deliveryToken deliveredtoken;


// void delivered(void *context, MQTTClient_deliveryToken dt)
// {
//     printf("Message with token value %d delivery confirmed\n", dt);
//     deliveredtoken = dt;
// }


// int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
// {
//     int i;
//     char *payloadptr;
//     printf("Message arrived\n");
//     printf("     topic: %s\n", topicName);
//     printf("   message: ");
//     payloadptr = (char*)message->payload;
//     for (i = 0; i < message->payloadlen; i++)
//     {
//         putchar(*payloadptr++);
//     }
//     putchar('\n');
//     MQTTClient_freeMessage(&message);
//     MQTTClient_free(topicName);
//     return 1;
// }


// void connlost(void *context, char *cause)
// {
//     printf("\nConnection lost\n");
//     printf("     cause: %s\n", cause);
// }


// int main(int argc, char *argv[])
// {
//     print("\n===== paho.mqtt testing [start] =====");

//     printf("\nCreating MQTTClient\n");
//     MQTTClient client;

//     // #define TOPIC "MQTT Examples"
//     // #define PAYLOAD "Hello World!"
//     // #define QOS 1
//     // #define TIMEOUT 10000L

//     const char* address = "tcp://guardingeyeai.com:8884";
//     const char* clientid = "ExampleClientSub";

//     MQTTClient_create(&client, address, clientid,
//                       MQTTCLIENT_PERSISTENCE_NONE, NULL);

//     MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
//     conn_opts.keepAliveInterval = 20;
//     conn_opts.cleansession = 1;
//     MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

//     MQTTClient_destroy(&client);
//     printf("\nExiting\n");

//     print(  "\n===== paho.mqtt testing [ end ] =====\n");
//     return 0;
// }


