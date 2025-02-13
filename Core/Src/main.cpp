#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"



int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif
    uint16_t local_serversocket_port = 8202;
    std::string localip = "127.0.0.1";
    std::unique_ptr<ServerSocket> serversocket = nullptr;
    StackPacket* inputpacket = nullptr;
    DigitalInput input(PA1);
    bool value = false;
    serversocket = std::make_unique<ServerSocket>(localip,local_serversocket_port);
    StackPacket* mypacket = new StackPacket(15,&value);//Random id
    STLIB::start();

    Time::register_low_precision_alarm(1000,[&](){
        if(mysocket->is_connected() == false){
            mysocket->reconnect();
        }
    });

    Time::register_low_precision_alarm(200,[&](){
        serversocket->send_packet(mypacket);
    });

    while (1) {
        value = input.read_pin_state();
        STLIB::update();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
