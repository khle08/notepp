
#include "mqtt.h"


MqttCli::MqttCli(const char* address, const char* clientID, const char* username, const char* password)
        : address(address), clientID(clientID), username(username), password(password)
{
    MQTTClient_create(&client, address, clientID, 0, NULL);

    // Attrs in: "include/MQTTAsync.h"
    connOpts = MQTTClient_connectOptions_initializer;
    connOpts.username = username;
    connOpts.password = password;
    connOpts.connectTimeout = 3;

    message = MQTTClient_message_initializer;

#ifdef USE_SSL
    MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
    ssl_opts.enableServerCertAuth = 1;
    // The path of server CA
    // ssl_opts.trustStore = CA_CERTIFICATE_FILE_PATH;
    connOpts.ssl = ssl_opts;
#endif
}


MqttCli::~MqttCli()
{
    MQTTClient_unsubscribe(client, topic);
    MQTTClient_disconnect(client, timeout);
    MQTTClient_destroy(&client);
}


int MqttCli::connect()
{
    MQTTClient_setCallbacks(client, NULL, NULL, callBack, NULL);

    int rc = MQTTClient_connect(client, &connOpts);
    if (rc != MQTTCLIENT_SUCCESS) {
        print("-- [X] Failed to connect, return code: " << rc);
        return -1;
    }

    print("-- [O] Connected to MQTT Broker");
    return 0;
}


int MqttCli::subscribe(const char* topic)
{
    this->topic = topic;
    MQTTClient_subscribe(client, topic, QoS);

    return 0;
}


int MqttCli::publish(char* payload)
{
    message.qos = QoS;
    message.payload = payload;
    message.retained = 0;
    message.payloadlen = strlen(payload);

    MQTTClient_publishMessage(client, topic, &message, &token);
    MQTTClient_waitForCompletion(client, token, timeout);

    print("Send " << payload << " to topic " << topic);
    return 0;
}


int MqttCli::callBack(void* context, char* topicName, int topicLen, MQTTClient_message* message)
{
    char* payload = (char*)message->payload;
    printf("Received `%s` from `%s` topic \n", payload, topicName);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;  // 0: topic will be erased after one request; 1: topic will keep alive
}

