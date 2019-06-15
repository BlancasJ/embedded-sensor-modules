# Embedded Sensor & Module Reference Library

Collection of standalone sensor and module implementations across multiple embedded platforms. Each folder contains code that reads a specific sensor or interfaces with a module — a reference library for embedded development.

## Context
- **Date:** 2016-2020 (various)
- **Institution:** Universidad Politecnica de Yucatan (UPY)
- **Type:** Reference / Learning

## Platforms
- Arduino (ATmega, ESP8266, ESP32, NodeMCU)
- PIC18F4550 / PIC12F1822 (CCS C compiler)
- STM32 (ARM Cortex-M)
- Intel Edison (Python, MRAA)
- LabVIEW

## Sensors

| Folder | Sensor/Module | Files | What they do |
|--------|--------------|-------|-------------|
| `temperature-lm35/` | LM35 analog temp | `basic-analog-read.ino`, `fire-alarm-lcd.c`, `binary-protocol-to-pc.c` | Read LM35, display on LCD, send via UART with checksum |
| `temperature-dht11/` | DHT11 temp/humidity | `basic-read-serial.ino`, `DHT11.c` (library), `pic12f1822-read-lcd.c`, `pic18f4550-read-lcd.c` | Read DHT11 on Arduino and two PIC variants |
| `temperature-th02/` | TH02 temp/humidity (I2C) | `basic-read-serial.ino`, `th02_demo.ino` (ESP32) | Read TH02 via I2C on Arduino and ESP32 |
| `ultrasonic-hcsr04/` | HC-SR04 distance | `basic-distance-pins-2-3.ino`, `basic-distance-nodemcu.ino`, `basic-distance-meters.ino` | Measure distance in cm/meters on different boards |
| `current-simple/` | ACS712 current | `basic-current-read.ino` | Read current sensor, convert ADC to amps |
| `sound-microphone/` | Analog microphone | `db-calculation.ino`, `db-level-classification.ino`, `db-level-with-leds.ino`, `interrupt-gate-detection.ino` | Calculate dB, classify levels, LED indicators, interrupt detection |
| `gas-mq2/` | MQ-2 gas/smoke | `calibration-ppm.ino` | Calibrate sensor, calculate ppm concentration |
| `light-ldr/` | LDR photoresistor | `lux-calculation.c`, `lux-with-threshold.c`, `luxmeter-final.c` (PIC) | Calculate lux, threshold-based light control |

## Modules

| Folder | Module | Files | What they do |
|--------|--------|-------|-------------|
| `lcd-16x2/` | LCD 16x2 display | `hello-world-scroll.ino` | Display text, scroll left/right |
| `led-basic/` | LED | `blink.ino`, `blink.c` | Blink LED on Arduino and PIC |
| `led-sequence/` | LED pattern | `button-pattern-switcher.c` | Cycle 3 LED patterns with button press (PIC) |
| `bluetooth-hc06/` | HC-06 Bluetooth | `at-configuration.ino` | Configure name, PIN, baudrate via AT commands |
| `keyboard-4x4/` | 4x4 matrix keypad | `matrix-scan-v1.c`, `v2.c`, `v3.c` | Scan keypad, display pressed key on LCD (PIC) |
| `seven-segment-display/` | 7-segment display | `counter-0-9.c` | Count 0-9 on 7-segment display (PIC) |
| `rtc-ds1302/` | DS1302 RTC | `pic18f4550-rtc-lcd-usb.c`, `ds1302-driver.c` | Read/write date-time, display on LCD, USB support |
| `counter-button/` | Push button counter | `interrupt-counter-0-9-lcd.c` | Count 0-9 with interrupt, display on LCD (PIC) |
| `motor-timer/` | DC motor timer | `timer3-pulse-1500ms.c` | Generate 1.5s pulse for motor via Timer3 (PIC) |
| `joystick-analog/` | Analog joystick | `joystick-button-detect-lcd.c` | Map joystick X/Y to button detection on LCD (PIC) |
| `ir-people-counter/` | Dual IR counter | `dual-ir-entry-exit-counter.c` | Count people entering/exiting with 2 IR sensors (PIC) |

## Communication & IoT

| Folder | Protocol | Files | What they do |
|--------|----------|-------|-------------|
| `thingspeak/` | ThingSpeak cloud | `esp8266-serial-to-thingspeak.ino`, `arduino-at-commands-dht11-lm35.ino`, `pic-esp8266-lm35-at-115200.c` | Send sensor data to ThingSpeak via ESP8266 |
| `esp8266-at-commands/` | ESP8266 WiFi | `at-esp8266-status.c` | Send AT commands, verify ESP8266 response (PIC) |
| `geolocation-wifi-api/` | Google Geolocation | `google-geolocation.ino` | Get lat/lon from surrounding WiFi networks |
| `xbee-sd-datalogger/` | XBee + SD card | `pic18f4550-xbee-sd.c`, `fat_m.c`, `mmcsd_m.c` | Receive XBee data, write to SD card with FAT filesystem (PIC) |
| `usb-sensor-reader/` | USB CDC | `pic18f4550-lm35-dht11-usb-cdc.c` | Read LM35+DHT11, send CSV via USB virtual COM port (PIC) |

## Boards

| Folder | Board | Files | What they do |
|--------|-------|-------|-------------|
| `stm32-blink-led/` | STM32F1 | `main.c` | Blink LED on GPIO B15 (ARM Cortex-M) |
| `intel-edison-sensors/` | Intel Edison | `temperature-thermistor.py`, `temperature-grove.py`, `uv-sensor.py`, `potentiometer-read.py`, `pwm-output.py`, `light-sensor-demo.py`, `multi-sensor-demo.py` | Various sensor reads using MRAA library |
| `labview-basics/` | LabVIEW | `example_one.vi` | Mean Point-by-Point statistics demo |
