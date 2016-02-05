/* 
  RF Blink - Receiver sketch 
     Written by ScottC 17 Jun 2014
     Arduino IDE version 1.0.5
     Website: http://arduinobasics.blogspot.com
     Receiver: XY-MK-5V
     Description: A simple sketch used to test RF transmission/receiver.          
 ------------------------------------------------------------- */

 #define rf434Switch A0  //RF Receiver pin = Analog pin 0
 #define rf315Switch A1  //RF Receiver pin = Analog pin 1
 #define ledPin 13        //Onboard LED = digital pin 13

 const unsigned int upperThreshold = 70;  //upper threshold value
 const unsigned int lowerThreshold = 50;  //lower threshold value

 void setup(){
   pinMode(ledPin, OUTPUT);
   Serial.begin(9600);
 }

 void loop(){
  thresholdCheck(analogRead(rf434Switch));
 // thresholdCheck(analogRead(rf315Switch));
  
 }

 void thresholdCheck(unsigned int data)
 {   
    if(data>upperThreshold)
    {
     digitalWrite(ledPin, LOW);   //If a LOW signal is received, turn LED OFF
     Serial.println(data);
   }
   
   if(data<lowerThreshold)
   {
     digitalWrite(ledPin, HIGH);   //If a HIGH signal is received, turn LED ON
     Serial.println(data);
   }
 }
  
 

