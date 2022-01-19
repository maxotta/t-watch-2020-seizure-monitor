#include "accelerometer.h"

void Accelerometer::init() {
    sensor = watch->bma;
    Acfg cfg;
    cfg.odr = BMA4_OUTPUT_DATA_RATE_25HZ;
    cfg.range = BMA4_ACCEL_RANGE_2G;
    cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
    cfg.perf_mode = BMA4_CONTINUOUS_MODE;
    sensor->accelConfig(cfg);
    sensor->enableAccel();
}

void Accelerometer::run() {
    sensor->getAccel(acceleration);
    snprintf(display_buffer, sizeof(display_buffer),
        "Accel: X=%i Y=%i Z=%i", acceleration.x, acceleration.y, acceleration.z
    );
    if (power->lowPower())
        delay_time = 1000;
    else
        delay_time = 20;

    refresh_display = true;
}

void Accelerometer::display() {
    screen->drawString(display_buffer, 0, 50, 2);
}