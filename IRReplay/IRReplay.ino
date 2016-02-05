

// We need to use the 'raw' pin reading methods
// because timing is very important here and the digitalRead()
// procedure is slower!
//uint8_t IRpin = 2;
// Digital pin #2 is the same as Pin D2 see
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping
#define IRpin_PIN PIND
#define IRpin 2
int IRledPin =  13;    // LED connected to digital pin 13
// for MEGA use these!
//#define IRpin_PIN PINE
//#define IRpin 4

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 65000

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[100][2]; // pair is high and low pulse
uint8_t currentpulse = 0; // index for pulses we're storing
bool haveKey = false;

uint16_t sendPulse[100][2]; // datagram to transmit
uint16_t IRsignal[] = {
// ON, OFF (in 10's of microseconds)
  440, 440,
  56, 162,
  56, 162,
  56, 162,
  56, 54,
  54, 54,
  56, 54,
  54, 54,
  56, 52,
  56, 164,
  54, 164,
  54, 164,
  54, 54,
  56, 54,
  56, 52,
  56, 54,
  54, 54,
  54, 56,
  54, 54,
  54, 54,
  56, 54,
  54, 164,
  56, 52,
  56, 54,
  56, 52,
  56, 162,
  56, 164,
  54, 162,
  56, 164,
  54, 54,
  56, 162,
  56, 162,
  56, 162,
  56, 0};




void setup(void) {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
}

void loop(void) {

    delay(1000);
    digitalWrite(IRledPin, LOW);  // this takes about 3 microseconds to happen
    delay(1000);
    digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
    sendKey(IRsignal,(int) 68);
    sendKey(IRsignal,(int) 68);
    sendKey(IRsignal,(int) 68);
    sendKey(IRsignal,(int) 68);


}

void getKey()
{
  
    uint16_t highpulse, lowpulse; // temporary storage timing
    highpulse = lowpulse = 0; // start out with no pulse length


    // while (digitalRead(IRpin)) { // this is too slow!
    while (IRpin_PIN & (1 << IRpin)) {
      // pin is still HIGH

      // count off another few microseconds
      highpulse++;
      delayMicroseconds(RESOLUTION);

      // If the pulse is too long, we 'timed out' - either nothing
      // was received or the code is finished, so print what
      // we've grabbed so far, and then reset
      if ((highpulse >= MAXPULSE) && (currentpulse != 0)) {
        printpulses();
        currentpulse = 0;
        return;
      }
    }
    // we didn't time out so lets stash the reading
    pulses[currentpulse][0] = highpulse;

    // same as above
    while (! (IRpin_PIN & _BV(IRpin))) {
      // pin is still LOW
      lowpulse++;
      delayMicroseconds(RESOLUTION);
      if ((lowpulse >= MAXPULSE) && (currentpulse != 0)) {
        printpulses();
        currentpulse = 0;
        return;
      }
    }
    pulses[currentpulse][1] = lowpulse;

    // we read one high-low pulse successfully, continue!
    currentpulse++;
}



void sendKey(uint16_t code[], int arrayLength)
{
  for (int i = 0; i < arrayLength; i+=2)
  {
    pulseIR(code[i] * RESOLUTION);
    delayMicroseconds(code[i+1] * RESOLUTION);
  }
}
// This procedure sends a 38KHz pulse to the IRledPin
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait

  cli();  // this turns off any background interrupts

  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
    delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
    digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
    delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working

    // so 26 microseconds altogether
    microsecs -= 26;
  }

  sei();  // this turns them back on
}
void printpulses(void) {
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  for (uint8_t i = 0; i < currentpulse; i++) {
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.println(" usec");
  }

  // print it in a 'array' format
  Serial.println("int IRsignal[] = {");
  Serial.println("// ON, OFF (in 10's of microseconds)");
  for (uint8_t i = 0; i < currentpulse - 1; i++) {
    Serial.print("\t"); // tab
    Serial.print(pulses[i][1] * RESOLUTION / 10, DEC);
    Serial.print(", ");
    Serial.print(pulses[i + 1][0] * RESOLUTION / 10, DEC);
    Serial.println(",");
  }
  Serial.print("\t"); // tab
  Serial.print(pulses[currentpulse - 1][1] * RESOLUTION / 10, DEC);
  Serial.print(", 0};");
}
