
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

    res = client->subscribe("1234");
    res = client->subscribe("5678");
    // if (res != 0) {
    //     delete client;
    //     return -1;
    // }

    char payload[16];
    std::string news = "";
    // for (int i = 0; i < 100; i += 1)
    while (true) {
        // snprintf(payload, 16, "message-%d", i);
        // res = client->publish(payload);

        // [!] The received data can be obtained below (only English and characters)
        // std::string _news = client->getMsg();
        // if (_news.size() > 0 && _news != news) {
        //     print(_news);
        //     news = _news;
        // }

        sleep(1);
    }

    delete client;
    return 0;
}

