
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
        aconnOpts.onSuccess = onConnect;
        aconnOpts.onFailure = onConnectFailure;

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
        MQTTAsync_setCallbacks(aclient, this, disconnect, areceived, NULL);

        int rc = MQTTAsync_connect(aclient, &aconnOpts);
        if (rc != MQTTASYNC_SUCCESS) {  // MQTTASYNC_SUCCESS == 0
#ifdef DEBUG_PRINT_LOG
            print("-- [X] Failed to connect, return code: " << rc);
#endif
            return -1;
        }

    } else {
        MQTTClient_setCallbacks(client, this, disconnect, received, NULL);

        int rc = MQTTClient_connect(client, &connOpts);
        if (rc != MQTTCLIENT_SUCCESS) {  // MQTTCLIENT_SUCCESS == 0
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
        print("-- [INFO] Async client will auto subscribe the topic after connected");

        res = MQTTAsync_subscribe(aclient, topic, QoS, &aresOpts);
        if (res != MQTTASYNC_SUCCESS) {  // MQTTASYNC_SUCCESS == 0
#ifdef DEBUG_PRINT_LOG
            print("-- [X] Failed to subscribe aclient, return code: " << res);
#endif
        }

    } else {
        res = MQTTClient_subscribe(client, topic, QoS);
#ifdef DEBUG_PRINT_LOG
        if (res != MQTTCLIENT_SUCCESS) { // MQTTCLIENT_SUCCESS == 0
            print("-- [X] Failed to subscribe client, return code: " << res);
        } else {
            print("-- [O] Successful subscribe");
        }
#endif
    }

    return res;
}


int MqttCli::publish(char* payload)
{
    if (isAsync) {
        MQTTAsync_responseOptions aresOpts2 = MQTTAsync_responseOptions_initializer;
        aresOpts2.onSuccess = onSend;
        aresOpts2.onFailure = onSendFailure;
        aresOpts2.context = aclient;  // Do not know what is the effect of this line ?????

        amessage.qos = QoS;
        amessage.payload = payload;
        amessage.retained = 0;
        amessage.payloadlen = strlen(payload);

        MQTTAsync_sendMessage(aclient, topic, &amessage, &aresOpts2);

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


void MqttCli::onSend(void* context, MQTTAsync_successData* response)
{
// #ifdef DEBUG_PRINT_LOG
//     printf("-- [O] Successful send\n");
// #endif
}


void MqttCli::onSendFailure(void* context, MQTTAsync_failureData* response)
{
// #ifdef DEBUG_PRINT_LOG
//     printf("-- [X] Send failed, rc: %d\n", response->code);
// #endif
}


void MqttCli::onConnect(void* context, MQTTAsync_successData* response)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [O] Successful connection\n");
#endif

//     [!] Subscribe here because of async client (still do not know why not working this way ?????)
//     MQTTAsync cli = (MQTTAsync)context;
//     MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
//     opts.onSuccess = onSubscribe;
//     opts.onFailure = onSubscribeFailure;
//     opts.context = cli;
// 
//     int res = MQTTAsync_subscribe(cli, "1234", 0, &opts);
//     if (res != MQTTASYNC_SUCCESS) {  // MQTTASYNC_SUCCESS == 0
// #ifdef DEBUG_PRINT_LOG
//         print("-- [X] Failed to subscribe aclient, return code: " << res);
// #endif
//     }
}


void MqttCli::onConnectFailure(void* context, MQTTAsync_failureData* response)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [X] Connect failed, rc: %d\n", response->code);
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
    printf("-- [X] Disconnect failed, rc: %d\n", response->code);
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
    printf("-- [X] Subscribe failed, rc: %d\n", response->code);
#endif
}


int MqttCli::received(void* context, char* topicName, int topicLen, MQTTClient_message* msg)
{
#ifdef DEBUG_PRINT_LOG
    char* payload = (char*)msg->payload;
    printf("Received `%s` from topic: `%s` \n", payload, topicName);
#endif

    MqttCli* client = (MqttCli*)context;
    client->message = *msg;
    MQTTClient_freeMessage(&msg);
    MQTTClient_free(topicName);
    return 1;  // 0: topic will be erased after one request; 1: topic will keep alive
}


int MqttCli::areceived(void* context, char* topicName, int topicLen, MQTTAsync_message* amsg)
{
#ifdef DEBUG_PRINT_LOG
    char* payload = (char*)amsg->payload;
    printf("Received `%s` from topic: `%s` \n", payload, topicName);
#endif

    MqttCli* client = (MqttCli*)context;
    client->amessage = *amsg;
    MQTTAsync_freeMessage(&amsg);
    MQTTAsync_free(topicName);
    return 1;  // 0: topic will be erased after one request; 1: topic will keep alive
}

