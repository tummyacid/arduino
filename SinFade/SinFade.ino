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
int MAX = 127;
int MIN = 5;
int RANGE = MAX-MIN;
int STEP = 1;
int DELAY = 30;

#define SIN_TABLE_SIZE  90
#define TABLE_SIZE  45
double TAU = 6.2831853071;
//double PI  = 3.141592353;
double waveTable[TABLE_SIZE+1];


void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(warmLED, OUTPUT);
  pinMode(coldLED, OUTPUT);

    analogWrite(coldLED, 0);

    for(int i = 0;i<=TABLE_SIZE;i++)
    {
      waveTable[i] = (TAU/TABLE_SIZE)* i;
    }
    
    for(int i = 0;i<=TABLE_SIZE;i++)
    {
      waveTable[i] = 0.5 * sin(waveTable[i]) + 1;
    }
  
}

void loop() {
  // fade in from min to max in increments of 5 points:
for (int i = 0;i<=SIN_TABLE_SIZE;i++)
{
  analogWrite(warmLED, MAX*waveTable[i]);
  analogWrite(coldLED, MAX*waveTable[TABLE_SIZE-i]);
  delay(DELAY);
}
  digitalWrite(13, HIGH);
for (int i = SIN_TABLE_SIZE;i>0;i--)
{
  analogWrite(warmLED, MAX*waveTable[i]);
  analogWrite(coldLED, MAX*waveTable[TABLE_SIZE-i]);
  delay(DELAY);
}
  digitalWrite(13, LOW);
}


