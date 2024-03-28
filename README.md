# Smart Doorbell IoT

This project implements a smart doorbell system using an ESP32 microcontroller. It integrates with Home Assistant for remote monitoring and provides over-the-air (OTA) programming capability using Arduino OTA. The system utilizes WiFiManager for easy initial setup and connection management.

## Features
- Detects doorbell button press and sends notification to Home Assistant.
- Supports remote programming via Arduino OTA.
- Easily configurable through WiFiManager.

## Hardware Requirements
- ESP32 microcontroller
- Doorbell button

## Circuit Diagram
![schema elec sonnette connecter](schema elec sonnette connecter.pdf)


## Getting Started
1. **Modify the Sketch**:
   - Open the Arduino sketch provided in this repository.
   - Replace placeholders in the sketch with your specific information.
   - After flashing the ESP32 via USB, retrieve its IP address and update the configuration file of the PlatformIO project to enable remote uploading.

2. **Connect ESP32 to WiFi Network**:
   - Follow the steps outlined in the previous section to connect the ESP32 to your WiFi network using WiFiManager.

3. **Set OTA Hostname and Password**:
   - After connecting, ensure the OTA hostname and password are set correctly in the modified sketch.

4. **Configure Home Assistant Script**:
   - Create a script in Home Assistant to handle doorbell events.
   - Use the provided YAML script and adjust it as needed.
