#include <Servo.h>

const int flexPins[] = {A1, A2, A3, A4, A5};
const int servoPins[] = {3, 5, 6, 9, 10};

int minVals[] = {820, 835, 750, 780, 750};  // When fingers are relaxed
int maxVals[] = {880, 890, 820, 810, 810};  // When fingers are curled


Servo servos[5];

void setup() {
  Serial.begin(9600);  // <-- This must match the Serial Monitor baud rate!
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
    
    Serial.print("Finger ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(flexValue);

    int angle = map(flexValue, minVals[i], maxVals[i], 180, 0);
    angle = constrain(angle, 0, 180);
    servos[i].write(angle);
  }

  Serial.println("---");
  delay(300);
}
