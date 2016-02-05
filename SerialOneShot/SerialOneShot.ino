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


#define warmLED  9    // LED connected to digital pin 9
int warmDest = 0;
int warmSTEP = 1;
int warmDELAY = 30;

#define coldLED 3
int coldDest = 0;
int coldSTEP = 1;
int coldDELAY = 30;

int DELAY = 0;

int Src = 0;
int dst = 0;

int charCount  = 0;

volatile bool command = false;

struct CommandPacket {
  int LED = 3;
int MAX = 12;
int MIN = 5;
int STEP = 1;
int DELAY = 150;
};

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

static byte warmValue = 0;
static byte coldValue = 0;

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

    
if (!command)
{
  if ((warmValue > warmDest) && (warmValue > 0))
    warmValue-=warmSTEP;
  if ((warmValue < warmDest) && (warmValue < 255))
    warmValue+=warmSTEP;
    
  if ((coldValue > coldDest) && (coldValue > 0))
    coldValue-=coldSTEP;
  if ((coldValue < coldDest) && (coldValue < 255))
    coldValue+=coldSTEP;
    
    analogWrite(warmLED, warmValue);
    analogWrite(coldLED, coldValue);
}
 //   analogWrite(coldLED, MIN+(MAX-fadeValue));
    delay(DELAY);
  }

 
/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    command = true;
    // get the new byte:
    switch((byte)Serial.read())
    {
    case warmLED:
     warmDest = (byte)Serial.read();
     warmSTEP = (byte)Serial.read();
     DELAY = (byte)Serial.read();
     break;
    case coldLED:
     coldDest = (byte)Serial.read();
     coldSTEP = (byte)Serial.read();
     DELAY = (byte)Serial.read();
    break;
    }
    command = false;

  }
}

    

