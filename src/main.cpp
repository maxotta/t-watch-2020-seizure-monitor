#include <LilyGoWatch.h>

#include "serial_message_queue.h"
#include "power_manager.h"

#include "clock.h"
#include "power_status.h"
#include "display.h"

TTGOClass *watch;

Clock display_clock;
PowerStatus display_power;
Accelerometer display_acceleration;
PowerManager power_manager;
Display display;
TaskHandle_t display_task;

bool low_power = false;

void setup(void) {
  watch = TTGOClass::getWatch();
  watch->begin();

  runSerialMessenger();

  watch->rtc->check();
  watch->bl->adjust(150);

  watch->tft->fillScreen(TFT_BLACK);
  watch->tft->setTextColor(TFT_WHITE, TFT_BLACK);
  watch->tft->setTextFont(8);
  watch->openBL();

  pinMode(AXP202_INT, INPUT);
  attachInterrupt(AXP202_INT, [] {
      power_manager.interrupt();
  }, FALLING);

  display.power = (PowerStatus*) &display_power;
  display.clock = (Clock*) &display_clock;
  display.accel = (Accelerometer*) &display_acceleration;
  display.system = watch;

  runDisplayTask((Display *) &display, &display_task);
  runPowerManagement((PowerManager *) &power_manager);

  Actor::setWatch(watch);
  Actor::setPower((PowerManager *) &power_manager);
  Actor::setDisplayTask(display_task);

  runActor("watchface", &display_clock, 20);
  runActor("power", &display_power, 11);
  runActor("accel", &display_acceleration, 11);

}

void loop() {
  vTaskDelay(10000);
}
