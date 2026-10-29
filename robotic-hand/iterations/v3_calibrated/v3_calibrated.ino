#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int flex1 = A1;
int flex2 = A2;
int flex3 = A3;
int flex4 = A4;
int flex5 = A5;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Attach servos to their respective pins
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
}

void loop() {
  // Read flex sensor values and map them to servo angles
  int flex1_pos = analogRead(flex1);
  int servo1_pos = map(flex1_pos, 840, 900, 0, 180);
  servo1_pos = constrain(servo1_pos, 0, 180);
  servo1.write(servo1_pos);

  int flex2_pos = analogRead(flex2);
  int servo2_pos = map(flex2_pos, 879, 882, 0, 180);
  servo2_pos = constrain(servo2_pos, 0, 180);
  servo2.write(servo2_pos);

  int flex3_pos = analogRead(flex3);
  int servo3_pos = map(flex3_pos, 824, 828, 0, 180);
  servo3_pos = constrain(servo3_pos, 0, 180);
  servo3.write(servo3_pos);

  int flex4_pos = analogRead(flex4);
  int servo4_pos = map(flex4_pos, 874, 878, 0, 180);
  servo4_pos = constrain(servo4_pos, 0, 180);
  servo4.write(servo4_pos);

  int flex5_pos = analogRead(flex5);
  int servo5_pos = map(flex5_pos, 851, 855, 0, 180);
  servo5_pos = constrain(servo5_pos, 0, 180);
  servo5.write(servo5_pos);

  // Print flex sensor values for debugging
  Serial.print("Flex 1: "); Serial.print(flex1_pos); 
  Serial.print(" | Flex 2: "); Serial.print(flex2_pos);
  Serial.print(" | Flex 3: "); Serial.print(flex3_pos); 
  Serial.print(" | Flex 4: "); Serial.print(flex4_pos); 
  Serial.print(" | Flex 5: "); Serial.println(flex5_pos);

  // Small delay to make the output readable
  delay(1000);
}