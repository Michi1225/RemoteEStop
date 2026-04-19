#pragma once

#include "CC1101.h"
#include "main.h"
#include "params.h"
#include "codec.h"
#include "rng.h"
#include "tim.h"

class Transceiver {
public:
    Transceiver(bool isTransmitter);
    virtual ~Transceiver() = default;
    void init();
    void run();
    void timeout();
    bool isESTOP() const { return this->ESTOP; }
    CC1101 cc1101;
private:
    bool transmitter = false;
    uint8_t xferData[64] = {0};
    bool ESTOP = true;

    // For Receiver
    int64_t prevCounter = 0;
    uint16_t lostPacketCount = 0;
    uint16_t validPacketCount = 0;

    // For Transmitter
    uint32_t txCounter = 0;
};