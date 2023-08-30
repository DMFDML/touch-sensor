#include "CapacitiveSensor.h" // Include CapacitiveSensor library for capacitive
// sensing
#include <Wire.h> // Include Wire library for I2C communication

// Set initial variables
const int mPin = 7; // Motor pin
CapacitiveSensor cs_6_5 = CapacitiveSensor(6, 5); // Create a new capacitive 
// sensor object
bool on = false; // Motor state
float prev = 0; // Previous value
const byte n = 20; // Number of samples to use in moving average
const float th = 20; // Threshold gradient value to change motor state

void setup() {
  pinMode(mPin, OUTPUT);
  cs_6_5.set_CS_AutocaL_Millis(0xFFFFFFFF); // Calibrate capacitive sensor
  // Serial.begin(9600); // Start serial communication at 9600 baud (if need be)
}

void loop() {
  long s1 = cs_6_5.capacitiveSensor(30); // Read 30 capacitive sensor samples
  float avg = avgMoving(s1); // Calculate moving average using function (defined
  // below)

  // If the gradient is less than the threshold and the motor is off, turn on
  // If the gradient is greater than the threshold and the motor is on, turn off
  if (avg - prev > th && !on) {
    on = true;
    digitalWrite(mPin, HIGH);
  } else if (avg - prev < -th && on) {
    on = false;
    digitalWrite(mPin, LOW);
  }

  prev = avg;

  // Print values to serial monitor for debugging threshold/moving average
  // Serial.print(s1);
  // Serial.print("\t");
  // Serial.print(avg);
  // Serial.print("\t");
  // Serial.print(avg - prev);
  // Serial.print("\n");

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