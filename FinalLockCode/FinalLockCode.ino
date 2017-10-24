#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <Servo.h>

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t touch = 0;
uint16_t count = 0;

uint8_t code[3] = {1, 2, 4};
uint8_t test[3];

Servo myservo;

void setup() {
  myservo.attach(9);
  myservo.write(0);
  cap.begin(0x5A);

}

void loop() {
  touch = cap.touched();
  if (touch != 0) {
    tone(8, 440, 200);
    test[count++] = touch;
    if (count == 3) {
      count = 0;
      if (memcmp(test, code, sizeof(test)) == 0) {
        myservo.write(90);
        tone(8, 660, 400);
      }
      else {
        myservo.write(0);
        tone(8, 330, 400);
      }
    }
  }
  delay(200);
}
