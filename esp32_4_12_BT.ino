#include "BluetoothSerial.h" // Include BluetoothSerial library for Bluetooth communication
#include <Wire.h> // Include Wire library for I2C communication

BluetoothSerial SerialBT; // Create a new SerialBT object

// Set initial variables
const int mPin = 12; // Motor pin
bool on = false; // Motor state
float prev = 0; // Previous value
const byte n = 5; // Number of samples to use in moving average
const float th = 2; // Threshold gradient value to change motor state

void setup() {
  pinMode(mPin, OUTPUT); // Set motor pin as output
  Serial.begin(9600); // Start serial communication at 9600 baud
  SerialBT.begin("ESP32Bluetooth"); // Bluetooth device name
}

void loop() {
  long s1 = touchRead(4); // Use inbuilt esp32 touch sensor on pin 4 and read 
  // value
  float avg = movingAvg(s1); // Calculate moving average using function (defined
  // below)

  float gradient = avg - prev; // Calculate the gradient

  // If the gradient is less than the threshold and the motor is off, turn on
  // If the gradient is greater than the threshold and the motor is on, turn off
  if (gradient < -th && !on) {
    on = true;
    digitalWrite(mPin, HIGH);
  } else if (gradient > th && on) {
    on = false;
    digitalWrite(mPin, LOW);
  }

  // Print a stream of on/off values to both wired and bluetooth serial monitors
  if (on) {
    Serial.print("1");
    SerialBT.print("1");
  } else {
    Serial.print("0");
    SerialBT.print("0");
  }
  Serial.print("\n");
  SerialBT.print("\n");

  // Set previous value so that it can be used in the next loop
  prev = avg;

  delay(5); // Adding a delay was important to allow the capacitance to change
}

float movingAvg(float v) { // Function to calculate moving average
  static byte c = 0; // Current index
  static byte nv = 0; // Number of values
  static float s = 0; // Sum of values
  static float val[n]; // Array of values
  
  s += v; // Add new value to sum

  if (nv == n) { // If the array is full, subtract the oldest value from the sum
    s -= val[c];
  }

  val[c] = v; // Add new value to array
  // Increment current index, if it is greater than or equal to the number of 
  // values, reset it to 0

  if (++c >= n) { 
    // This means that the array will be filled in a loop
    c = 0; 
  }

  // If the number of values is less than the number of samples, increment it
  if (nv < n) { 
    // This means that the sum will be divided by the number of values, 
    // not the number of samples
    nv++; 
  }

  // Return the average
  return s / nv; 
}