#pragma once
#include "actor.h"

#define DISPLAY_POWER_STATUS_ID 1

class PowerStatus : public Actor {
  public:
    bool ready();
    void run();

    void display();
    const uint32_t displayIdentifier() {
      return DISPLAY_POWER_STATUS_ID;
    }

  private:
    long unsigned int last_run = 0;
    char display_buffer[255];

    void pluggedInSummary();
    void batterySummary();
};
