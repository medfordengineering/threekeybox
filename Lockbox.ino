#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <Servo.h>

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t touch = 0;
uint16_t count = 0;

uint8_t code[3] = {1, 2, 4};
uint8_t test[3];

Servo myservo;

void setup() {
//  while (!Serial);        // needed to keep leonardo/micro from starting too fast!
  myservo.attach(9);
  Serial.begin(9600);
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
}

void loop() {
  touch = cap.touched();
  if (touch != 0) {
    Serial.print(touch);
    test[count++] = touch;
    if (count == 3) {
      count = 0;
      if (memcmp(test, code, sizeof(test)) == 0) {
        Serial.println("yes");
        myservo.write(90);
      }
      else {
        Serial.println("no");
         myservo.write(0);
      }
    }

  }

  // Serial.println(touch);
  delay(200);


}
