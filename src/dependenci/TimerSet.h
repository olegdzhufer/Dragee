#ifndef TM_H
#define TM_H

#include <Arduino.h>
#include "dallas_sensor.h"
#include "menu.h"
#include "relay.h"
#include <Ticker.h>


float most_recent_temperature_measurement;

void temperatureTimerISR(){
  REG_FLAG |= (1 << 0 ) | (1 << 1);
}

// Глобальний об'єкт Ticker
Ticker temperatureTicker;

void timer_setup(){
  pinMode(REL1, OUTPUT);
  

    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);

    gpio_set_level((gpio_num_t)V33, 1);

  // Налаштування таймера з інтервалом 5 секунд
  temperatureTicker.attach(1, temperatureTimerISR);
}

void timer_loop(){
  if (REG_FLAG & (1 << 1))
  {
    REG_FLAG &= ~(1 << 1);
    most_recent_temperature_measurement = readTemperatureSensor(temperatureSensor);
  }
}

#endif