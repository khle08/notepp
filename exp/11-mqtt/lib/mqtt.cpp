
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

    this->init();
}


MqttCli::~MqttCli()
{
    if (isAsync) {
        // MQTTAsync_unsubscribe(aclient, topic);
        MQTTAsync_disconnect(aclient, &adisConnOpts);
        MQTTAsync_destroy(&aclient);

    } else {
        for (int i = 0; i < topicVec.size(); i++) {
            MQTTClient_unsubscribe(client, topicVec[i].c_str());
        }
        MQTTClient_disconnect(client, timeout);
        MQTTClient_destroy(&client);
    }
}


int MqttCli::init()
{
    if (isAsync) {
        MQTTAsync_create(&aclient, address, clientID, 0, NULL);

        adisConnOpts = MQTTAsync_disconnectOptions_initializer;
        adisConnOpts.context = this;  // to avoid non-static error, send class to the func
        adisConnOpts.onSuccess = onDisconnect;
        adisConnOpts.onFailure = onDisconnectFailure;

        amessage = MQTTAsync_message_initializer;

    } else {
        MQTTClient_create(&client, address, clientID, 0, NULL);
        message = MQTTClient_message_initializer;
    }

    return 0;
}


int MqttCli::connect(std::vector<std::string>& topicVec)
{
    this->topicVec = topicVec;

    if (isAsync) {
        MQTTAsync_setCallbacks(aclient, this, disconnect, areceived, NULL);

        MQTTAsync_connectOptions aconnOpts = MQTTAsync_connectOptions_initializer;
        aconnOpts.context = this;  // to avoid non-static error, send class to the func
        aconnOpts.username = username;
        aconnOpts.password = password;
        aconnOpts.connectTimeout = timeout;
        aconnOpts.keepAliveInterval = (int)(86400 * days);
        aconnOpts.onSuccess = onConnect;
        aconnOpts.onFailure = onConnectFailure;
#ifdef USE_SSL
        MQTTAsync_SSLOptions assl_opts = MQTTAsync_SSLOptions_initializer;
        assl_opts.enableServerCertAuth = 1;
        // [!] The path of server CA
        // ssl_opts.trustStore = CA_CERTIFICATE_FILE_PATH;
        aconnOpts.ssl = assl_opts;
#endif

        // Connection callback can only be defined in "aconnOpts"
        int rc = MQTTAsync_connect(aclient, &aconnOpts);

    } else {
        MQTTClient_setCallbacks(client, this, disconnect, received, NULL);

        // Attrs in: "include/MQTTAsync.h"
        MQTTClient_connectOptions connOpts = MQTTClient_connectOptions_initializer;
        connOpts.username = username;
        connOpts.password = password;
        connOpts.connectTimeout = timeout;
        connOpts.keepAliveInterval = (int)(86400 * days);
#ifdef USE_SSL
        MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
        ssl_opts.enableServerCertAuth = 1;
        // [!] The path of server CA
        // ssl_opts.trustStore = CA_CERTIFICATE_FILE_PATH;
        connOpts.ssl = ssl_opts;
#endif

        int rc = MQTTClient_connect(client, &connOpts);
        if (rc != MQTTCLIENT_SUCCESS) {  // MQTTCLIENT_SUCCESS == 0
#ifdef DEBUG_PRINT_LOG
            print("-- [X] Failed to connect, return code: " << rc);
#endif
            return -1;
        } else {
#ifdef DEBUG_PRINT_LOG
            print("-- [O] Successful connection");
#endif
        }

        // Only non-async mode can subscribe here
        for (int i = 0; i < topicVec.size(); i++) {
            this->subscribe(topicVec[i]);
        }
    }

    return 0;
}


int MqttCli::subscribe(std::string& topic)
{
    // this->topic = topic.c_str();  // useless

    int res = 0;
    if (isAsync) {
        print("-- [INFO] Async client will auto subscribe the topic after connected");

    } else {
        res = MQTTClient_subscribe(client, topic.c_str(), QoS);
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


int MqttCli::publish(std::string& topic, char* payload)
{
    if (isAsync) {
        MQTTAsync_responseOptions aresOpts2 = MQTTAsync_responseOptions_initializer;
        aresOpts2.context = this;  // to avoid non-static error, send class to the func
        aresOpts2.onSuccess = onSend;
        aresOpts2.onFailure = onSendFailure;

        amessage.qos = QoS;
        amessage.payload = payload;
        amessage.retained = 0;
        amessage.payloadlen = strlen(payload);

        MQTTAsync_sendMessage(aclient, topic.c_str(), &amessage, &aresOpts2);

        // Only async client can auto reconnect after connecting back to online

    } else {
        message.qos = QoS;
        message.payload = payload;
        message.retained = 0;
        message.payloadlen = strlen(payload);

        MQTTClient_publishMessage(client, topic.c_str(), &message, &token);
        MQTTClient_waitForCompletion(client, token, timeout);
    }

#ifdef DEBUG_PRINT_LOG
    print("Send " << payload << " to topic " << topic);
#endif
    return 0;
}


std::string MqttCli::getMsg(std::string& topic)
{
    std::string none = "";

    int res = std::distance(news.begin(), news.find(topic));
    if (res != news.size()) {
        return news[topic];
    }

    return none;
}


void MqttCli::disconnect(void* context, char* cause)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [X] Disconnected cause: %s\n", cause);
#endif

    // Callback for failed connection (for both async and non-async cases)
    MqttCli* client = (MqttCli*)context;

    int res = -1;
    while (res < 0) {
        client->init();
        client->connect(client->topicVec);
        sleep(1);
    }
}


void MqttCli::onSend(void* context, MQTTAsync_successData* response)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [O] Successful send       (async)\n");
#endif
}


void MqttCli::onSendFailure(void* context, MQTTAsync_failureData* response)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [X] Send failed, rc: %d\n", response->code);
#endif

    // [!] Disconnect the internet will not raise this func
}


void MqttCli::onConnect(void* context, MQTTAsync_successData* response)
{
#ifdef DEBUG_PRINT_LOG
    printf("-- [O] Successful connection (async)\n");
#endif

    // [!] Subscribe here because of async client
    MqttCli* client = (MqttCli*)context;  // void* context <- should be assinged "this" class

    MQTTAsync_responseOptions aresOpts = MQTTAsync_responseOptions_initializer;
    aresOpts.context = client;
    aresOpts.onSuccess = client->onSubscribe;
    aresOpts.onFailure = client->onSubscribeFailure;

    for (int i = 0; i < client->topicVec.size(); i++) {
        MQTTAsync_subscribe(client->aclient, client->topicVec[i].c_str(), client->QoS, &aresOpts);
    }
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
    printf("-- [O] Successful subscribe  (async)\n");
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
    printf("Received `%s` from topic: `%s`\n", payload, topicName);
#endif

    // Contributed by CWZ (non-static function)
    MqttCli* client = (MqttCli*)context;
    client->message = *msg;

    std::string tpc(topicName);
    int len = client->message.payloadlen;
    if (len > 0) {
        char* info = (char*)client->message.payload;
        std::string out(info);

        if (out == " ") {  // Filter out the key values
            client->news[tpc] = "";
        } else {
            client->news[tpc] = out;
        }

    } else {
        client->news[tpc] = "";
    }

    MQTTClient_freeMessage(&msg);
    MQTTClient_free(topicName);
    return 1;  // 0: topic will be erased after one request; 1: topic will keep alive
}


int MqttCli::areceived(void* context, char* topicName, int topicLen, MQTTAsync_message* amsg)
{
#ifdef DEBUG_PRINT_LOG
    char* payload = (char*)amsg->payload;
    printf("Received `%s` from topic: `%s`\n", payload, topicName);
#endif

    // Contributed by CWZ (non-static function)
    MqttCli* client = (MqttCli*)context;
    client->amessage = *amsg;

    std::string tpc(topicName);
    int len = client->amessage.payloadlen;
    if (len > 0) {
        char* info = (char*)client->amessage.payload;
        std::string out(info);

        if (out == " ") {
            client->news[tpc] = "";
        } else {
            client->news[tpc] = out;
        }

    } else {
        client->news[tpc] = "";
    }

    MQTTAsync_freeMessage(&amsg);
    MQTTAsync_free(topicName);
    return 1;  // 0: topic will be erased after one request; 1: topic will keep alive
}

