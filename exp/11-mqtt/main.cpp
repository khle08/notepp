
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

    char payload[16];
    res = client->subscribe("1234");
    // if (res != 0) {
    //     delete client;
    //     return -1;
    // }

    for (int i = 0; i < 100; i += 1) {
        // snprintf(payload, 16, "message-%d", i);
        // res = client->publish(payload);

        // [!] The received data can also be obtained below
        char* news = (char*)client->amessage.payload;
	    printf("Received: `%s`\n", news);

        // std::string nnn(news);
        // print(news);

        sleep(1);
    }

    delete client;
    return 0;
}

