# TTGo T-Watch 2020 V1 Seizure Monitor

A Simple project for using the [TTGo T-Watch 2020](https://t-watch-document-en.readthedocs.io/en/latest/introduction/product/2020.html) [V1](https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library/blob/master/docs/watch_2020_v1.md) as an epileptic seizure monitor and later detector with warning notifications.
It uses [FreeRTOS<sup>TM</sup>](https://www.freertos.org/) as the core operating system, inspired by the [My TTGo Watch](https://github.com/red-fox-star/ttgo_watch) project found on [GitHub](https://github.com).

## Roadmap

The project development is divided into subsequent stages, starting with a simple dumb watch and adding more and more features:

1. **Simple watch** - show time and date, battery info. Sleep/wake up by pressing the watch button. It makes use of the [AXP202](http://www.x-powers.com/en.php/Info/product_detail/article_id/30) API.
2. **Simple watch with 3D motion indicator** - additionally shows data read from the [3D Bosch Sensortec accelerometer](https://www.bosch-sensortec.com/products/motion-sensors/accelerometers/) using the [BMA423 Sensor API](https://github.com/BoschSensortec/BMA423-Sensor-API)
3. **Simple watch with wake up from light/deep sleep, when some motion is detected**
4. **Simple watch with Wifi connectivity and RTC synchronization using NTP**
5. **Simple watch with a MQTT client** - see [FreeRTOS<sup>TM</sup> coreMQTT](https://www.freertos.org/mqtt/index.html)
