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
int MAX = 12;
int MIN = 5;
int RANGE = MAX-MIN;
int STEP = 1;
int DELAY = 150;

int charCount  = 0;

struct CommandPacket {
  int LED = 3;
int MAX = 12;
int MIN = 5;
int STEP = 1;
int DELAY = 150;
};

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(32);
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(warmLED, OUTPUT);
  pinMode(coldLED, OUTPUT);

    analogWrite(coldLED, 0);
  
}

void loop() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = MIN ; fadeValue <= MAX; fadeValue += STEP) {
    // sets the value (range from 0 to 255):
    analogWrite(warmLED, fadeValue);
  //  analogWrite(coldLED, MIN+(MAX-fadeValue));
    delay(DELAY);
  }
  digitalWrite(13, HIGH);

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = MAX ; fadeValue >= MIN; fadeValue -= STEP) {
    // sets the value (range from 0 to 255):
    analogWrite(warmLED, fadeValue);
 //   analogWrite(coldLED, MIN+(MAX-fadeValue));
    delay(DELAY);
  }
  digitalWrite(13, LOW);

  
      Serial.println( MIN);
}
/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    byte inChar = (byte)Serial.read();
    if(charCount > 3)
      charCount = 0;
    switch(charCount)
    {
      case 0:
      MIN = (int)inChar;
      case 1:
      MAX = (int)inChar;
      case 2:
      STEP = (int)inChar;
      case 3:
      DELAY = (int)inChar;
    }
    charCount++;

  }
}

    

