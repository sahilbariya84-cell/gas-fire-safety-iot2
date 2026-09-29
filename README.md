# IoT-Based Gas & Fire Safety Alert System

**Team**
- Bariya Sahil: 2305101270029 | BCA(H) | Div C
- Atmiya Patel: 2305101270218 | BCA(H) | Div C

An ESP32-based safety monitor simulated in [Wokwi](https://wokwi.com). It detects gas leakage and abnormal heat, raises a local alarm (buzzer + LED), and publishes live status over MQTT.

## Features
- Gas leak detection using an analog gas sensor
- Fire / heat detection using a DHT22 temperature sensor
- Instant local alarm: buzzer + red LED (green LED = safe)
- Remote monitoring: JSON status published to an MQTT broker (HiveMQ)

## Components
| Component | Role |
|---|---|
| ESP32 DevKit | Microcontroller with built-in WiFi |
| Gas sensor (MQ-2 style) | Gas concentration (analog) |
| DHT22 | Temperature sensing |
| Buzzer | Audible alarm |
| Red / Green LED + 220 ohm resistors | Alert / safe indicator |

## Pin Connections
| Part | Pin | ESP32 |
|---|---|---|
| Gas sensor | AOUT | GPIO 34 |
| DHT22 | SDA | GPIO 15 |
| Buzzer | + | GPIO 25 |
| Red LED (via resistor) | Anode | GPIO 26 |
| Green LED (via resistor) | Anode | GPIO 33 |
| All sensors | VCC / GND | 3V3 / GND |

## How It Works
1. Read gas level and temperature every 2 seconds.
2. Alarm if gas > 2000 (ADC scale 0-4095) **or** temperature > 50 C.
3. Alarm ON: red LED + buzzer. Normal: green LED.
4. Publish a JSON message to the MQTT topic, for example:
   `{"gas":1450,"temp":27.5,"status":"SAFE"}`

## Run in Wokwi
1. Create a new **ESP32** project at wokwi.com.
2. Replace `sketch.ino`, `diagram.json`, and `libraries.txt` with the files in this repo.
3. Press the green **Play** button.
4. Click the gas sensor and DHT22 in the simulation and raise their sliders to trigger the alarm.
5. Change the MQTT topic in `sketch.ino` to something unique, then watch messages in an MQTT client such as the HiveMQ web client.

## Running on Real Hardware
- Replace `WiFi.begin("Wokwi-GUEST", "", 6)` with your own WiFi name and password.
- A real MQ-2 uses 5V, so use a voltage divider on AOUT before GPIO34.
- Calibrate the gas threshold using your sensor's clean-air reading.

## Project Files
- `sketch.ino`: main firmware
- `diagram.json`: Wokwi circuit
- `libraries.txt`: Wokwi libraries
- `Gas_Fire_Safety_IoT.pptx`: project presentation

## Future Scope
- Add a real flame sensor and smoke sensor
- SMS / WhatsApp alerts through cloud services
- Automatic exhaust fan or valve shut-off using a relay
- Mobile dashboard with history and analytics
