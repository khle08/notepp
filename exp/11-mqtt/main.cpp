
#include <map>
#include <mutex>
#include <thread>
#include <string>

#include "mqtt.h"


int main(int argc, char *argv[])
{
    print("compiled successfully");
    
    std::string uniqueId = "WEQFRE";
    MqttCli* client = new MqttCli("tcp://192.168.110.50:1883",  // address
                                  "mqttx_38c419c3",                // clientid
                                  "emqx",                          // username
                                  "public",                        // password
                                  uniqueId,
                                  true);

    std::vector<std::string> topicVec = {"1234", "5678"};
    int res = -1;
    while (res < 0) {
        res = client->connect(topicVec);
        sleep(client->interval);
    }

    int cnt = 1;
    char payload[16];
    std::vector<std::string> newsVec = {"", ""};
    // for (int i = 0; i < 100; i += 1)
    while (true) {
        // [!] The received data can be obtained below (only English and characters)
        for (int i = 0; i < topicVec.size(); i++) {
            // test: send
            // snprintf(payload, 16, "message-%d:%d", i, cnt);
            // res = client->publish(topicVec[i], payload);

            // test: receive
            std::string _news = client->getMsg(topicVec[i]);
            if (_news.size() > 0 && _news != newsVec[i]) {
                print(">> get: " << _news);
                newsVec[i] = _news;
            }
        }

        // snprintf(payload, 16, "test-%d", cnt);
        // client->reconnect(payload);

        print("status: " << client->connected << " | " << client->hasmsg);
        cnt += 1;
        sleep(client->interval);
    }

    delete client;
    return 0;
}

