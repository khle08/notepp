
#include "mqtt.h"


MqttCli::MqttCli(const char* address, const char* clientID, const char* username, const char* password)
        : address(address), clientID(clientID), username(username), password(password)
{
    MQTTClient_create(&this->client, address, clientID, 0, NULL);

    this->message = MQTTClient_message_initializer;
    this->connOpts = MQTTClient_connectOptions_initializer;
    this->connOpts.username = username;
    this->connOpts.password = password;
}


MqttCli::~MqttCli()
{
    MQTTClient_unsubscribe(this->client, this->topic);
    MQTTClient_disconnect(this->client, this->timeout);
    MQTTClient_destroy(&this->client);
}


int MqttCli::connect()
{
    MQTTClient_setCallbacks(this->client, NULL, NULL, callBack, NULL);

    int rc = MQTTClient_connect(this->client, &this->connOpts);
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
    MQTTClient_subscribe(this->client, topic, this->QoS);

    return 0;
}


int MqttCli::publish(char* payload)
{
    // ??? bug should be here !
    this->message.qos = this->QoS;
    this->message.payload = payload;
    this->message.retained = 0;
    this->message.payloadlen = strlen(payload);

    MQTTClient_publishMessage(this->client, this->topic, &this->message, &this->token);
    MQTTClient_waitForCompletion(this->client, this->token, this->timeout);

    print("Send " << payload << " to topic " << topic);
    return 0;
}


int MqttCli::callBack(void* context, char* topic, int topicLen, MQTTClient_message* message)
{
    char* payload = (char*)message->payload;
    printf("Received `%s` from `%s` topic \n", payload, topic);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topic);
    return 0;
}

