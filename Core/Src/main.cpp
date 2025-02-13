#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"

uint32_t local_serversocket_port = 8202;
std::string localip = "127.0.0.1";
std::unique_ptr<ServerSocket> serversocket = nullptr;
StackPacket* inputpacket = nullptr;

int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif
    DigitalInput input(PA1);
    bool value = false;
    serversocket = std::make_unique<ServerSocket>(localip,local_serversocket_port);
    StackPacket* mypacket = new StackPacket(15,&value);//Random id
    STLIB::start();

    Time::register_low_precision_alarm(100,[&](){
        if(mysocket->is_connected() == false){
            mysocket->reconnect();
        }
    });

    while (1) {
        value = input.read_pin_state();
        serversocket->send_packet(mypacket);
        STLIB::update();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
