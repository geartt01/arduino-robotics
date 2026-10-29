#include <Servo.h>  // Include the Servo library

const int numSensors = 5;  // Define the number of sensors

const int servoPins[numSensors] = {3, 5, 6, 9, 10};    // PWM pins for servos
const int flexPins[numSensors] = {A0, A1, A2, A3, A4}; // Analog pins for flex sensors

Servo servos[numSensors]; // Create an array of Servo objects

void setup() {
  Serial.begin(9600); // Start serial communication for debugging

  // Initialize servos
  for (int i = 0; i < numSensors; i++) {
    servos[i].attach(servoPins[i]); // Attach each servo to its pin
  }
}

void loop() {
  for (int i = 0; i < numSensors; i++) {
    // Read flex sensor value
    int flexValue = analogRead(flexPins[i]);
    
    // Map the sensor value to a servo angle (0 to 180 degrees)
    int servoAngle = map(flexValue, 0, 1023, 0, 180);
    
    // Write the mapped angle to the corresponding servo
    servos[i].write(servoAngle);

    // Debug output
    Serial.print("Flex Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(flexValue);
    Serial.print(" -> Servo Angle: ");
    Serial.println(servoAngle);
  }

  delay(50); // Add a small delay for stability
}

