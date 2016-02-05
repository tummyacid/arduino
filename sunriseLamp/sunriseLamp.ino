/*
 Fading

 This example shows how to fade an LED using the analogWrite() function.

 The circuit:
 * LED attached from digital pin 9 to ground.

 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe

 http://www.arduino.cc/en/Tutorial/Fading

 This example code is in the public domain.

 */


int warmLED = 9;    // LED connected to digital pin 9
int coldLED = 3;
int MAX = 20;
int MIN = 2;
int RANGE = MAX-MIN;
int STEP = 1;
int DELAY = 200;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(warmLED, OUTPUT);
  pinMode(coldLED, OUTPUT);

  analogWrite(coldLED, 2);
}

void loop() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = MIN ; fadeValue <= MAX; fadeValue += STEP) {
    // sets the value (range from 0 to 255):
    analogWrite(warmLED, fadeValue);
    //analogWrite(coldLED, MIN+(MAX-fadeValue));
    // wait for 30 milliseconds to see the dimming effect
    delay(DELAY);
  }
  digitalWrite(13, HIGH);

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = MAX ; fadeValue >= MIN; fadeValue -= STEP) {
    // sets the value (range from 0 to 255):
    analogWrite(warmLED, fadeValue);
    //analogWrite(coldLED, MIN+(MAX-fadeValue));
    // wait for 30 milliseconds to see the dimming effect
    delay(DELAY);
  }
  digitalWrite(13, LOW);
}


