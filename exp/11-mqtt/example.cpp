
#include <string>
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#include "MQTTClient.h"

// #define ADDRESS     "tcp://guardingeyeai.com:8883"
// #define USERNAME    "emqx"
// #define PASSWORD    "public"
// #define CLIENTID    "mqttx_38c419c3"
#define QOS         0
#define TOPIC       "1234"
#define TIMEOUT     10000L

void publish(MQTTClient client, const char *topic, char *payload, 
             MQTTClient_message &message, MQTTClient_deliveryToken &token) {
    message.payload = payload;
    message.payloadlen = strlen(payload);
    message.qos = QOS;
    message.retained = 0;
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

int main(int argc, char *argv[])
{
    // init
    const char* address = "tcp://guardingeyeai.com:8883";
    const char* clientid = "mqttx_38c419c3";
    const char* username = "emqx";
    const char* password = "public";
    int timeout = 10000L;
    int qos = 0;

    MQTTClient client;
    MQTTClient_message message;
    MQTTClient_deliveryToken token;
    MQTTClient_connectOptions conn_opts;

    MQTTClient_create(&client, address, clientid, 0, NULL);
    message = MQTTClient_message_initializer;
    conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.username = username;
    conn_opts.password = password;


    // connect
    MQTTClient_setCallbacks(client, NULL, NULL, on_message, NULL);

    int rc = MQTTClient_connect(client, &conn_opts);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    } else {
        printf("Connected to MQTT Broker!\n");
    }


    // subscribe
    const char* topic = "1234";
    MQTTClient_subscribe(client, topic, qos);


    // push
    char payload[16];
    for (int i = 0; i < 100; i += 1) {
        // publish message to broker
        // std::string payload = "message-" + std::to_string(i);
        snprintf(payload, 16, "message-%d", i);
        publish(client, topic, payload, message, token);
        sleep(1);
    }


    // destroy
    MQTTClient_unsubscribe(client, topic);
    MQTTClient_disconnect(client, timeout);
    MQTTClient_destroy(&client);
    return rc;
}

