#pragma once
#include "actor.h"

#define DISPLAY_ACCELEROMETER 3

class Accelerometer : public Actor {
    public:
        Accelerometer() { };

        void run();
        void init();
        void display();

        const uint32_t displayIdentifier() {
            return DISPLAY_ACCELEROMETER;
        }

    private:
        BMA *sensor = nullptr;
        Accel acceleration = {0, 0, 0};
        char display_buffer[255];
};
