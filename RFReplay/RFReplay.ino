#include <RCSwitch.h>

/*
 * RF Sniffer (C) Elia Yehuda 2014
 * 
 * This program was coded.
 *
 * No warranty whatsoever.
 * Using this program will cause something, most likely problems.
 *
 */
 
#include <RCSwitch.h>
 
// number of times to resend sniffed value. use 0 to disable.
#define RESEND_SNIFFED_VALUES 10
 
// ye, thats the led pin #
#define LED_PIN 13
 
// class for 315 receiver & transmitter
RCSwitch rf315Switch = RCSwitch();
// class for 434 receiver & transmitter
RCSwitch rf434Switch = RCSwitch();
 
void setup()
{
        // print fast to console
        Serial.begin(9600);
 
        // 315 receiver on interrupt #0 (pin #2)
        rf315Switch.enableReceive(0);  
        // 315 transmitter on pin #4
        rf315Switch.enableTransmit(4);
        // how many resends
        rf315Switch.setRepeatTransmit(RESEND_SNIFFED_VALUES);
         
        // 434 receiver on interrupt #1 (pin #3)
        rf434Switch.enableReceive(1);  
        // 434 transmitter on pin #5
        rf434Switch.enableTransmit(5);
        // how many resends
        rf434Switch.setRepeatTransmit(RESEND_SNIFFED_VALUES);
         
        Serial.println("[+] Listening");
}
 
// simple decimal-to-binary-ascii procedure
char *tobin32(unsigned long x)
{
        static char b[33];
        b[32] = '\0';
         
        for ( int z = 0; z < 32; z++) {
                b[31 - z] = ((x >> z) & 0x1) ? '1' : '0';
        }
         
        return b;
}
 
void process_rf_value(RCSwitch rfswitch, int rf)
{
        char str[120];
        unsigned long value;
 
        // flash a light to show transmission
        digitalWrite(LED_PIN, true);
         
        value = rfswitch.getReceivedValue();
        if (value) {
                sprintf(str, "[+] %d Received: %s / %010lu / %02d bit / Protocol = %d",
                        rf, tobin32(value), value, rfswitch.getReceivedBitlength(), rfswitch.getReceivedProtocol() );
        } else {
                sprintf(str, "[-] %d Received: Unknown encoding (0)", rf);
        }
        Serial.println(str);
 
        // resend the sniffed value (RESEND_SNIFFED_VALUES times)
        rfswitch.send(value, rfswitch.getReceivedBitlength());
         
        // reset the switch to allow more data to come
        rfswitch.resetAvailable();
        // stop light to show end of transmission
        digitalWrite(LED_PIN, false);
}
 
void loop()
{
 
        if (rf315Switch.available()) {
        digitalWrite(LED_PIN, true);
                process_rf_value(rf315Switch, 315);
        }
 
        if (rf434Switch.available()) {
        digitalWrite(LED_PIN, true);
                process_rf_value(rf434Switch, 434);
        }
}
