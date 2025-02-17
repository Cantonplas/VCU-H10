#ifndef SIM_ON
#include "main.h"

#include "lwip.h"
#endif

#include "ST-LIB.hpp"
#include <thread>
#include <chrono>



int main(void) {
#ifdef SIM_ON
    SharedMemory::start();
#endif
    uint16_t local_serversocket_port = 8202;
    std::string localip = "127.0.0.1";
    
    uint8_t id = DigitalInput::inscribe(PA8);
    bool value = false;
    auto inputpacket = new StackPacket(15,&value);//Random id
    
    STLIB::start();
    ServerSocket serversocket(localip,local_serversocket_port);

    /*Time::register_low_precision_alarm(1000,[&](){
        if(!serversocket.is_connected()){
            serversocket.();
        }
    });*/

    Time::register_low_precision_alarm(200,[&](){
        serversocket.send();
    });

    while (1) {
        value = DigitalInput::read_pin_state(id);
        STLIB::update();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void Error_Handler(void) {
    ErrorHandler("HAL error handler triggered");
    while (1) {
    }
}
