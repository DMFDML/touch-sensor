# Touch Sensor with Moving Average

This Arduino sketch demonstrates touch sensor control using a moving average to stabilize readings. It offers two options: one for Arduino boards and another for ESP32 boards. The sketch uses a capacitive touch sensor to toggle an output pin (motor) based on touch events detected by the moving average of sensor readings. Additionally, new Bluetooth functionality has been added to the ESP32 version for wireless control, which can be integrated with Unity or VR applications.

## Requirements

- **Option 1 (Arduino):**
  - Arduino board (e.g., Arduino Uno)
  - Capacitive touch sensor connected to pins 6 and 5
  - Motor driver circuit connected to pin 7 for motor control
  - [CapacitiveSensor library](https://playground.arduino.cc/Main/CapacitiveSensor/) installed

- **Option 2 (ESP32 with Bluetooth for Unity/VR):**
  - ESP32 board (e.g., ESP32 DevKit)
  - Capacitive touch sensor connected to pin 4
  - Motor driver circuit connected to pin 12 for motor control
  - Bluetooth functionality added to enable wireless control
  - Upload `esp_4_12_BT.ino` to your ESP32 board
  - Use the `read_BT.py` Python script as an example of reading data from the ESP32 over Bluetooth
  - Integrate the Bluetooth data into Unity or VR applications for interactive control

- **Option 3 (ESP32 without Bluetooth):**
  - ESP32 board (e.g., ESP32 DevKit)
  - Capacitive touch sensor connected to pin 4
  - Motor driver circuit connected to pin 12 for motor control
  - Upload the provided sketch `esp_4_12.ino` to your ESP32 board
  - Open the Serial Monitor at a baud rate of 9600 to view the sensor readings and calculated values.

## Getting Started

Choose the appropriate option for your hardware and follow the respective setup instructions:

### Option 1: Arduino

1. Connect the capacitive touch sensor to pins 6 and 5 of the Arduino.
2. Connect a motor driver circuit to pin 7 of the Arduino for motor control.
3. Install the [CapacitiveSensor library](https://playground.arduino.cc/Main/CapacitiveSensor/) if not already installed.
4. Upload the provided sketch to your Arduino board.
5. Open the Serial Monitor at a baud rate of 9600 to view the sensor readings and calculated values.

### Option 2: ESP32 with Bluetooth for Unity/VR

1. Connect the capacitive touch sensor to pin 4 of the ESP32.
2. Connect a motor driver circuit to pin 12 of the ESP32 for motor control.
3. Upload the provided sketch (`esp_4_12_BT.ino`) to your ESP32 board.
4. Use the `read_BT.py` Python script as an example to read and process data from the ESP32 over Bluetooth.
5. Integrate the Bluetooth data into your Unity or VR applications for interactive control.
6. Open the Serial Monitor at a baud rate of 9600 to view the sensor readings and calculated values.

### Option 3: ESP32 without Bluetooth

1. Connect the capacitive touch sensor to pin 4 of the ESP32.
2. Connect a motor driver circuit to pin 12 of the ESP32 for motor control.
3. Upload the provided sketch (`esp_4_12.ino`) to your ESP32 board.
4. Open the Serial Monitor at a baud rate of 9600 to view the sensor readings and calculated values.

![Circuit Diagram](https://github.com/mikewharton/touch-sensor/blob/main/circuit_diagram.png)

## Using the `read_BT.py` Script

The included `read_BT.py` Python script serves as an example of how to read and process data from the ESP32 over Bluetooth. It's intended for demonstration purposes and can be modified to suit your specific requirements.

## Finding the Bluetooth COM Port (Windows)

To locate the COM port associated with the Bluetooth connection on Windows:
1. Go to Bluetooth settings in your system settings.
2. Navigate to "More Bluetooth options" or similar settings.
3. Look for the "COM Ports" tab to find the COM port assigned to the Bluetooth connection.

## Code Explanation

The provided sketches follow similar steps and logic:

1. Initialize necessary variables and constants.
2. Set up the pinMode for the motor and capacitive touch sensor.
3. If you're using the Arduino option, set the capacitive sensor autocalibration.
4. In the loop:
   - Read the sensor value and calculate the moving average using the `avgMoving` function.
   - Toggle the motor based on the calculated moving average and threshold values.
   - Update previous values and optionally print sensor information to the Serial Monitor.
5. In the ESP32 version with Bluetooth, data is also transmitted wirelessly to a connected device.

## Adjusting Parameters

You can adjust the following parameters in the sketches to customize behavior:

- `const int mPin`: Output pin for controlling the motor.
- `const byte n`: Number of readings to consider for the moving average.
- `const float th`: Threshold for detecting touch events.
- `delay(5)`: Adjust the delay time between readings if necessary.

## Related Projects

See the [haptics-demo](https://github.com/DMFDML/haptics-demo) repository for a Unity project that integrates the ESP32 with Bluetooth for interactive control of a haptic device.