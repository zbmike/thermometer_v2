# thermometer_v2
Built a digital thermometer with Raspberry Pi 4, DHT11 sensor and a 16x2 lcd as Practise of Python.

hardware wiring is harder than expected, But here it is, a photo of the thermometer version 2's prototype:

![thermometer_v2](images/v2.jpg)

And here is a battery-powered version of v2 built on Raspberry Pi Zero W:
![thermometer_battery_v2](images/v3.jpg)
After that, I detoured a little bit to the ESP32 microcontroller of which firmware is written in C++
![thermometer_microcontroller_with_battery](images/v4.jpg)
These are all environmental data gathering points. All of them have wireless capability. They will be gathering temp/humi data for my later projects.
<br>
<br>
package needed
```
sudo apt-get install libgpiod2
sudo pip3 install adafruit-circuitpython-dht rplcd
```