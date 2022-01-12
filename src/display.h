#pragma once

#include "power_status.h"
#include "clock.h"
#include "serial_message_queue.h"

#define DISPLAY_POWER 0x1
#define DISPLAY_WATCH 0x2

class Display {
  public:
    PowerStatus * power;
    Clock * clock;
    TTGOClass * system;

    void run() {
      if (update_key & power->displayIdentifier()) {
        power->display();
      }

      if (update_key & clock->displayIdentifier()) {
        clock->display();
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
