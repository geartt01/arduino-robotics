#include <Servo.h>

const int flexPins[] = {A1, A2, A3, A4, A5};
const int servoPins[] = {3, 8, 6, 12, 10};

int minVals[] = {820, 820, 780, 749, 750};  // straight
int maxVals[] = {880, 880, 810, 800, 800};  // bent


Servo servos[5];

int lastFlexValues[5] = {0, 0, 0, 0, 0};  // for noise filtering
int lastAngles[5] = {0, 0, 0, 0, 0};      // to hold last servo position

void setup() { 
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    servos[i].attach(servoPins[i]);
  }
}

int smoothFlexRead(int pin) {
  long total = 0;
  const int samples = 10;
  for (int i = 0; i < samples; i++) {
    total += analogRead(pin);
    delay(1);
  }
  return total / samples;
}

void loop() {
  for (int i = 0; i < 5; i++) {
    int flexValue = smoothFlexRead(flexPins[i]);

    // Optional noise filtering
    if (abs(flexValue - lastFlexValues[i]) < 3) {
      flexValue = lastFlexValues[i];
    } else {
      lastFlexValues[i] = flexValue;
    }

    int servoAngle = map(flexValue, minVals[i], maxVals[i], 180, 0);
    servoAngle = constrain(servoAngle, 0, 180);

    // Optional angle smoothing
    if (abs(servoAngle - lastAngles[i]) < 3) {
      servoAngle = lastAngles[i];
    } else {
      lastAngles[i] = servoAngle;
    }

    servos[i].write(servoAngle);

    Serial.print("Finger ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(flexValue);
    Serial.print(" -> Angle: ");
    Serial.println(servoAngle);
  }

  delay(300);
}
