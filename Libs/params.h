#pragma once

#include <cstdint>


constexpr uint8_t ADDRESS = 0x01;
constexpr uint8_t  CHANNEL = 0x00;
constexpr uint8_t APPEND_STATUS = 0x01;
constexpr uint8_t PACKET_LEN = 0x05;

constexpr uint8_t ROUNDS = 0x04;
constexpr uint16_t KEYS[ROUNDS] = {0x1234, 0xBEEF, 0xCAFE, 0x0BAD};
constexpr uint8_t TX_PERIOD_MS = 5;
constexpr uint8_t MAX_LOST_PACKETS = 5;
constexpr uint8_t VALID_PACKET_THRESHOLD = 100;
constexpr uint8_t VALID_FRAME_TIMEOUT_US = 20000;