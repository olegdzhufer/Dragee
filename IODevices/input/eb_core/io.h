#pragma once

#include <Arduino.h>
// #include <GyverIO.h>//todo replace

// bool EB_read(uint8_t pin);
// void EB_mode(uint8_t pin, uint8_t mode);
// uint32_t EB_uptime();

bool EB_read(uint8_t pin) {
    return digitalRead(pin);
}

void EB_mode(uint8_t pin, uint8_t mode) {
    pinMode(pin, mode);
}

uint32_t EB_uptime() {
    return millis();
}