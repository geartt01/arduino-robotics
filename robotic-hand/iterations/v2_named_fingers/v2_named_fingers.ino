#include <Servo.h>  // Include the Servo library

// Create Servo objects for each finger
Servo thumbServo, indexServo, middleServo, ringServo, pinkyServo;

// Define flex sensor pins (INPUT)
const int thumbSensor = A0;
const int indexSensor = A1;
const int middleSensor = A2;
const int ringSensor = A3;
const int pinkySensor = A4;

// Define servo motor pins (OUTPUT)
const int thumbServoPin = 3;
const int indexServoPin = 5;
const int middleServoPin = 6;
const int ringServoPin = 9;
const int pinkyServoPin = 10;

// Sensor calibration values (Adjust these based on testing)
int minFlex = 300;  // Value when finger is straight
int maxFlex = 800;  // Value when finger is fully bent

void setup() {
    Serial.begin(9600);  // Start Serial Monitor for debugging

    // Attach servos to their respective pins
    thumbServo.attach(thumbServoPin);
    indexServo.attach(indexServoPin);
    middleServo.attach(middleServoPin);
    ringServo.attach(ringServoPin);
    pinkyServo.attach(pinkyServoPin);
}

void loop() {
    // Read flex sensor values
    int thumbVal = analogRead(thumbSensor);
    int indexVal = analogRead(indexSensor);
    int middleVal = analogRead(middleSensor);
    int ringVal = analogRead(ringSensor);
    int pinkyVal = analogRead(pinkySensor);

    // Convert sensor values to servo angles (0° - 180°)
    int thumbAngle = map(thumbVal, minFlex, maxFlex, 0, 180);
    int indexAngle = map(indexVal, minFlex, maxFlex, 0, 180);
    int middleAngle = map(middleVal, minFlex, maxFlex, 0, 180);
    int ringAngle = map(ringVal, minFlex, maxFlex, 0, 180);
    int pinkyAngle = map(pinkyVal, minFlex, maxFlex, 0, 180);

    // Constrain angles to prevent out-of-range values
    thumbAngle = constrain(thumbAngle, 0, 180);
    indexAngle = constrain(indexAngle, 0, 180);
    middleAngle = constrain(middleAngle, 0, 180);
    ringAngle = constrain(ringAngle, 0, 180);
    pinkyAngle = constrain(pinkyAngle, 0, 180);

    // Move servos to corresponding angles
    thumbServo.write(thumbAngle);
    indexServo.write(indexAngle);
    middleServo.write(middleAngle);
    ringServo.write(ringAngle);
    pinkyServo.write(pinkyAngle);

    // Print sensor values and servo angles for debugging
    Serial.print("Thumb: "); Serial.print(thumbAngle);
    Serial.print(" | Index: "); Serial.print(indexAngle);
    Serial.print(" | Middle: "); Serial.print(middleAngle);
    Serial.print(" | Ring: "); Serial.print(ringAngle);
    Serial.print(" | Pinky: "); Serial.println(pinkyAngle);

    delay(50);  // Small delay for smoother movement
}


