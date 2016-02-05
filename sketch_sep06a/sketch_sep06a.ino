/*
  Simple example for receiving

  http://code.google.com/p/rc-switch/
*/

#include <RCSwitch.h>

// ye, thats the led pin #
#define LED_PIN 13

// class for 315 receiver & transmitter
RCSwitch rf315Switch = RCSwitch();
// class for 434 receiver & transmitter
RCSwitch rf434Switch = RCSwitch();

void setup() {
  Serial.begin(9600);
  rf315Switch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
  rf434Switch.enableReceive(1);  // Receiver on inerrupt 1 => that is pin #3
    digitalWrite(LED_PIN, false);
}

void loop() {
  if (rf434Switch.available()) {
    digitalWrite(LED_PIN, true);


  }
  if (rf315Switch.available()) {
    digitalWrite(LED_PIN, true);

  }
    rf434Switch.resetAvailable();
    rf315Switch.resetAvailable();
}
