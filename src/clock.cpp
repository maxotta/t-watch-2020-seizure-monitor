#include "clock.h"

void Clock::init() {
  x_middle = screen->width() / 2;
  y_middle = screen->height() / 2;

  int16_t hours_half_height = screen->fontHeight(hour.font) / 3;

  time_digit_width = screen->textWidth("00", minute.font);
  time_space = screen->textWidth("::", minute.font);

  minute.x = x_middle - time_digit_width * 0.5;
  minute.y = y_middle + hours_half_height;

  hour.x = x_middle - time_digit_width * 1.5 - time_space;
  hour.y = y_middle + hours_half_height;

  second.x = x_middle + time_digit_width * 0.5 + time_space;
  second.y = y_middle + hours_half_height;

  x_div_hm = minute.x - time_space / 2;
  x_div_ms = second.x - time_space / 2;

  date.x = 0;
  date.y = screen->height() - (screen->fontHeight(second.font) + 2);
}

void Clock::run() {
  time = watch->rtc->getDateTime();
  delay_time = 250;

  if (wakeUpRun()) redisplay = true;

  refresh_display = redisplay || time.second != old_second;
}
 
void Clock::display() {
  int16_t position_x = 0;

  redisplay = redisplay || time.second % 10 == 0;

  // date
  if (redisplay || time.day != old_day) {
    old_day = time.day;
    position_x = date.x;
    position_x += screen->drawNumber(time.day, position_x, date.y, date.font);
    position_x += screen->drawChar('.', position_x, date.y, date.font);
    position_x += screen->drawNumber(time.month, position_x, date.y, date.font);
    position_x += screen->drawChar('.', position_x, date.y, date.font);
  }

  // hours
  if (redisplay || old_hour != time.hour) {
    old_hour = time.hour;
    position_x = hour.x;
    screen->setTextPadding(screen->textWidth("0", hour.font));
    if (time.hour < 10) position_x += screen->drawChar('0', position_x, hour.y, hour.font);
    position_x += screen->drawNumber(time.hour, position_x, hour.y, hour.font);
  }

  if (redisplay) {
    screen->drawChar(':', x_div_hm, hour.y, hour.font);
  }

  // minutes
  if (redisplay || old_minute != time.minute) {
    old_minute = time.minute;
    position_x = minute.x;
    screen->setTextPadding(screen->textWidth("0", minute.font));
    if (time.minute < 10) position_x += screen->drawChar('0', position_x, minute.y, minute.font);
    position_x += screen->drawNumber(time.minute, position_x, minute.y, minute.font);
  }

  if (redisplay) {
    screen->drawChar(':', x_div_ms, hour.y, hour.font);
  }

  // seconds
  old_second = time.second;
  position_x = second.x;
  screen->setTextPadding(screen->textWidth("0", second.font));
  if (time.second < 10) {
    position_x += screen->drawChar('0', position_x, second.y, second.font);
    position_x += second.space;
    position_x += screen->drawNumber(time.second, position_x, second.y, second.font);
  } else {
    position_x += screen->drawNumber(time.second / 10, position_x, second.y, second.font);
    position_x += second.space;
    position_x += screen->drawNumber(time.second % 10, position_x, second.y, second.font);
  }

  redisplay = false;
}
