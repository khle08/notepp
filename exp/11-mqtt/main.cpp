
#include <map>
#include <mutex>
#include <thread>
#include <string>

#include "mqtt.h"


int main(int argc, char *argv[])
{
    print("compiled successfully");
    
    MqttCli* client = new MqttCli("tcp://guardingeyeai.com:8883",
                                  "mqttx_38c419c3",
                                  "emqx",
                                  "public",
                                  true);

    int res = client->connect();
    if (res != 0) {
        delete client;
        return -1;
    }

    sleep(1);

    std::vector<std::string> topicVec = {"1234", "5678"};
    for (int i = 0; i < topicVec.size(); i++) {
        res = client->subscribe(topicVec[i]);
    }

    char payload[16];
    std::vector<std::string> newsVec = {"", ""};
    // for (int i = 0; i < 100; i += 1)
    while (true) {
        // snprintf(payload, 16, "message-%d", i);
        // res = client->publish(payload);

        // [!] The received data can be obtained below (only English and characters)
        for (int i = 0; i < topicVec.size(); i++) {
        	std::string _news = client->getMsg(topicVec[i]);

        	if (_news.size() > 0 && _news != newsVec[i]) {
        		print("received: " << _news);
        		newsVec[i] = _news;
        	}
        }

        sleep(1);
    }

    delete client;
    return 0;
}

