Here I will show you how to install and set up ESP32 board on Arduino IDE, and the code to use in order to get data readings of  from Higrow sensors and to upload data on Thingspeak.com channels and using Blynk app, it's super easy.

This type of sensro is wireless, it can be used to monitor and  detect pests that are thretening plants, by just getting on timely manner different environemtal parameters such as temperature, humidity, soil moisture and light intensity. 

# Higrow sensor 
Higrow is an open-source hardware integrated with ESP32 Bluetooth wifi development board supports NodeMCU / Arduino, DHt11 Temperature and Humidity sensor, Soil probe (long) detection module, CP2104 communication chip USB TO TTL, a Micro USB port, the sensor is powered by rechargeable 18650 Lithium Battery.
https://www.higrow.tech/ 

# ESP32 node CMU 
The NodeMCU ESP-32S is one of the development board created by NodeMcu to evaluate the ESP-WROOM-32 module, which is a powerful, generic WiFi+BT+BLE MCU module that targets a wide variety of applications, ranging from low-power sensor networks to the most demanding tasks, such as voice encoding, music streaming and MP3 decoding.

The ESP32 can be integrated on Arduino IDE, I have installed on my Linux as in follow command lines on the terminal:
- install Git and Python’s required packages:
curl -o get-pip.py https://bootstrap.pypa.io/get-pip.py && \ 
sudo python get.pip.py && \
sudo pip install pyserial

-create a folder espressif inside Hardware folder:
cd Downloads/arduino-1.6.11/hardware
mkdir espressif 
cd espressif

- Run thr git clone command inside the espressif folder:
git clone https://github.com/espressif/arduino-esp32.git esp32 && \
cd esp32/tools/ && \
python get.py

- Reopen Arduino IDE and ESP32 board is installed. 
