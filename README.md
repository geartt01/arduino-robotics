# Arduino & ESP32 Robotics

[![Compile sketches](https://github.com/geartt01/arduino-robotics/actions/workflows/compile.yml/badge.svg)](https://github.com/geartt01/arduino-robotics/actions/workflows/compile.yml)

Hardware projects I built and programmed in C++ with the Arduino IDE.

| Project | Board | What it does |
|---|---|---|
| [Robotic hand](robotic-hand/) | Arduino Uno | A 3D-printed hand whose fingers follow 5 flex sensors |
| [Weather station](esp32-weather-station/) | ESP32 | Reads 7 environmental sensors and shows the values on an OLED screen |

---

## Robotic hand

Five flex sensors, one per finger, drive five servo motors that move the fingers of a 3D-printed hand.
Bend a sensor and the matching robot finger bends with it. I presented it at a school event.

**Hardware:** Arduino Uno · 5 flex sensors on analog inputs A1–A5 · 5 servo motors (Servo library) · 3D-printed hand

**How it works** ([`robotic_hand.ino`](robotic-hand/robotic_hand/robotic_hand.ino)):
1. Each flex sensor is read 10 times and averaged to reduce noise.
2. Every finger has its own calibration (`minVals` = straight, `maxVals` = bent), because no two flex sensors read the same.
3. The reading is mapped to a servo angle from 0° to 180° and constrained to that range.
4. Changes smaller than 3 units are ignored (on both the sensor reading and the angle), so the servos don't jitter.

**Development log:** the [`iterations/`](robotic-hand/iterations/) folder keeps every stage, from the first
test to the final version:

| Version | Change |
|---|---|
| v1 – first test | Map each flex sensor to a servo with the full 0–1023 range |
| v2 – named fingers | One variable per finger, shared calibration constants, angle constraints |
| v3 – calibrated | Moved the sensors to A1–A5 and gave each one its own measured range |
| v4 – per-finger calibration | Calibration arrays, averaged readings, reversed direction to match the hand |
| **final** | Noise filtering and angle smoothing, so the fingers hold still when your hand does |

On every push, GitHub Actions compiles the final sketch and all four iterations for the Arduino Uno.

## ESP32 weather station

Built on the **ACEBOTT QE011** ESP32 kit. [`weather_station.ino`](esp32-weather-station/weather_station/weather_station.ino)
reads the kit's 7 environmental sensors and shows the values on a 128×64 OLED, updating every 2 seconds.

**Sensors:** DHT11 (temperature, humidity) · barometric pressure sensor · PM2.5 dust sensor · UV sensor · wind-cup anemometer · light sensor · raindrop sensor

**Libraries:** the ACEBOTT kit libraries (`ACB_DHT11`, `ACB_Atmospheric`, `ACB_PM25`, `ACB_Ultraviolet_V2`, `ACB_WindCup`) and [U8g2](https://github.com/olikraus/u8g2) for the display.

WiFi is optional: put your network name and password at the top of the sketch. If it can't connect within
10 seconds, the station keeps running offline.
