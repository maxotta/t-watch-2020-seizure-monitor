#pragma once

#include "power_status.h"
#include "clock.h"
#include "accelerometer.h"
#include "serial_message_queue.h"

class Display {
  public:
    PowerStatus * power;
    Clock * clock;
    Accelerometer * accel;
    TTGOClass * system;

    void run() {
      if (update_key & power->displayIdentifier()) {
        power->display();
      }

      if (update_key & clock->displayIdentifier()) {
        clock->display();
      }

      if (update_key & accel->displayIdentifier()) {
        accel->display();
      }

    }

    void notified_by(uint32_t notification_value) {
      update_key = notification_value;
    }

  private:
    uint32_t update_key = 0;
};

void displayTask(void* object);
void runDisplayTask(Display * display, TaskHandle_t * display_task);
