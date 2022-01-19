#pragma once
#include "actor.h"

#define DISPLAY_CLOCK_ID 2

class DigitMetric {
  public:
    DigitMetric(int16_t _font) : font(_font), space(0), x(0), y(0) {};

    int16_t font = 1;
    int16_t space = 0;
    int16_t x = 0;
    int16_t y = 0;
};

class Clock : public Actor {
  public:
    Clock() : date{7}, hour{7}, minute{7}, second{7} { };

    bool ready();
    void run();
    void init();
    void display();

    const uint32_t displayIdentifier() {
      return DISPLAY_CLOCK_ID;
    }

  private:
    bool redisplay = false;

    RTC_Date time;
    int16_t x_middle, y_middle;

    DigitMetric date;
    DigitMetric hour;
    DigitMetric minute;
    DigitMetric second;

    int16_t time_space = 0;
    int16_t time_digit_width = 0;
    int16_t x_div_hm = 0;
    int16_t x_div_ms = 0;

    int16_t old_day = 31;
    int16_t old_hour = 24;
    int16_t old_minute = 61;
    int16_t old_second = 61;
};
