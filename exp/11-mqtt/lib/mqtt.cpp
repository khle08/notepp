
#include "mqtt.h"

// #define DEBUG_PRINT_LOG


MqttCli::MqttCli(const char* address, const char* clientID, const char* username, const char* password, bool isAsync)
        : address(address), clientID(clientID), username(username), password(password), isAsync(isAsync)
{
    // [!] The forth param in order to create mqtt client.
    // MQTTCLIENT_PERSISTENCE_NONE  =  0 - This persistence_type value specifies the default file system-based persistence mechanism
    // MQTTCLIENT_PERSISTENCE_USER  =  1 - This persistence_type value specifies a memory-based persistence mechanism
    // MQTTCLIENT_PERSISTENCE_USER  =  2 - This persistence_type value specifies an application-specific persistence mechanism
    // MQTTCLIENT_PERSISTENCE_ERROR = -2 - Application-specific persistence functions must return this error code if there is a problem executing the function.

    if (isAsync) {
        MQTTAsync_create(&aclient, address, clientID, 0, NULL);

        aconnOpts = MQTTAsync_connectOptions_initializer;
        aconnOpts.username = username;
        aconnOpts.password = password;
        aconnOpts.connectTimeout = 10;
        aconnOpts.keepAliveInterval = 20;

        adisConnOpts = MQTTAsync_disconnectOptions_initializer;
        adisConnOpts.onSuccess = onDisconnect;
        adisConnOpts.onFailure = onDisconnectFailure;
        adisConnOpts.context = aclient;

        aresOpts = MQTTAsync_responseOptions_initializer;
        aresOpts.onSuccess = onSubscribe;
        aresOpts.onFailure = onSubscribeFailure;
        aresOpts.context = aclient;

        amessage = MQTTAsync_message_initializer;

#ifdef USE_SSL
        MQTTAsync_SSLOptions assl_opts = MQTTAsync_SSLOptions_initializer;
        assl_opts.enableServerCertAuth = 1;
        // [!] The path of server CA
        // ssl_opts.trustStore = CA_CERTIFICATE_FILE_PATH;
        aconnOpts.ssl = assl_opts;
#endif

    } else {
        MQTTClient_create(&client, address, clientID, 0, NULL);

        // Attrs in: "include/MQTTAsync.h"
        connOpts = MQTTClient_connectOptions_initializer;
        connOpts.username = username;
        connOpts.password = password;
        connOpts.connectTimeout = 10;
        connOpts.keepAliveInterval = 20;

        message = MQTTClient_message_initializer;

#ifdef USE_SSL
        MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
        ssl_opts.enableServerCertAuth = 1;
        // [!] The path of server CA
        // ssl_opts.trustStore = CA_CERTIFICATE_FILE_PATH;
        connOpts.ssl = ssl_opts;
#endif
    }
}


MqttCli::~MqttCli()
{
    if (isAsync) {
        // MQTTAsync_unsubscribe(aclient, topic);
        MQTTAsync_disconnect(aclient, &adisConnOpts);
        MQTTAsync_destroy(&aclient);

    } else {
        MQTTClient_unsubscribe(client, topic);
        MQTTClient_disconnect(client, timeout);
        MQTTClient_destroy(&client);
    }
}


int MqttCli::connect()
{
    if (isAsync) {


    } else {
        MQTTClient_setCallbacks(client, NULL, disconnect, received, NULL);

        int rc = MQTTClient_connect(client, &connOpts);
        if (rc != MQTTCLIENT_SUCCESS) {
#ifdef DEBUG_PRINT_LOG
            print("-- [X] Failed to connect, return code: " << rc);
#endif
            return -1;
        }
    }

#ifdef DEBUG_PRINT_LOG
    print("-- [O] Connected to MQTT Broker");
#endif
    return 0;
}


int MqttCli::subscribe(const char* topic)
{
    this->topic = topic;

    int res = 0;
    if (isAsync) {
        res = MQTTAsync_subscribe(aclient, topic, QoS, &aresOpts);

    } else {
        res = MQTTClient_subscribe(client, topic, QoS);
    }

    return res;
}


int MqttCli::publish(char* payload)
{
    if (isAsync) {


    } else {
        message.qos = QoS;
        message.payload = payload;
        message.retained = 0;
        message.payloadlen = strlen(payload);

        MQTTClient_publishMessage(client, topic, &message, &token);
        MQTTClient_waitForCompletion(client, token, timeout);
    }

#ifdef DEBUG_PRINT_LOG
    print("Send " << payload << " to topic " << topic);
#endif
    return 0;
}


void MqttCli::disconnect(void* context, char* cause)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [X] Disconnected cause: %s\n", cause);
#endif
}


void MqttCli::onDisconnect(void* context, MQTTAsync_successData* response)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [O] Successful disconnection\n");
#endif
}


void MqttCli::onDisconnectFailure(void* context, MQTTAsync_failureData* response)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [X] Disconnect failed\n");
#endif
}


void MqttCli::onSubscribe(void* context, MQTTAsync_successData* response)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [O] Successful Subscribe\n");
#endif
}


void MqttCli::onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [X] Subscribe failed\n");
#endif
}


int MqttCli::received(void* context, char* topicName, int topicLen, MQTTClient_message* message)
{
#ifdef DEBUG_PRINT_LOG
    char* payload = (char*)message->payload;
    printf("Received `%s` from `%s` topic \n", payload, topicName);
#endif

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;  // 0: topic will be erased after one request; 1: topic will keep alive
}

