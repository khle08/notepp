
#include "mqtt.h"


MqttCli::MqttCli(const char* address, const char* clientID, const char* username, const char* password)
        : address(address), clientID(clientID), username(username), password(password)
{
    // reader = std::thread(this->read, src, inputId, std::ref(images), std::ref(m));
    // reader.detach();

    MQTTClient_create(&client, address, clientID, 0, NULL);

    message = MQTTClient_message_initializer;
    connOpts = MQTTClient_connectOptions_initializer;
    connOpts.username = username;
    connOpts.password = password;

    MQTTClient_setCallbacks(client, NULL, NULL, callBack, NULL);
}


MqttCli::~MqttCli()
{
    MQTTClient_unsubscribe(client, topic);
    MQTTClient_disconnect(client, timeout);
    MQTTClient_destroy(&client);
}


int MqttCli::connect()
{
    int rc = MQTTClient_connect(client, &connOpts);
    if (rc != MQTTCLIENT_SUCCESS) {
        print("Failed to connect, return code: " << rc);
        exit(-1);
        return -1;
    }

    print("Connected to MQTT Broker");
    return 0;
}


int MqttCli::subscribe(const char* topic)
{
    topic = topic;
    MQTTClient_subscribe(client, topic, QoS);

    return 0;
}


int MqttCli::publish(char* payload)
{
    message.payload = payload;
    message.payloadlen = strlen(payload);
    message.qos = QoS;
    message.retained = 0;

    MQTTClient_publishMessage(client, topic, &message, &token);
    MQTTClient_waitForCompletion(client, token, timeout);

    print("Send " << payload << " to topic " << topic);
    return 0;
}


int MqttCli::callBack(void* context, char* topic, int topicLen, MQTTClient_message* message)
{

    return 0;
}

