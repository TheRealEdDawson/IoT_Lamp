
/*
* Getting Started example sketch for nRF24L01+ radios
* This is a very basic example of how to send data from one node to another
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"
#include <printf.h>

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(9,10);
/**********************************************************/

//byte addresses[][6] = {"1Node","2Node"};
const uint64_t addresses[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

// Used to control whether this node is sending or receiving

void setup() {
  Serial.begin(57600);
  printf_begin();
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  
  // Open a writing and reading pipe to recieve from the RPi
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);

  while (!Serial);
  Serial.println(F("Test output"));
  // Start the radio listening for data
  radio.startListening();
  radio.printDetails();
  
   pinMode(13, OUTPUT);
   pinMode(2, OUTPUT);
}

void loop() {
  
  


    unsigned int command = 0;
    
    if( radio.available()){
                                                                    // Variable for the received timestamp
      while (radio.available()) {                                   // While there is data ready
        radio.read( &command, sizeof(command) );             // Get the payload
    }
     
     analogWrite(3, command);
     Serial.println(command);
     
     
//      if (command == 1) {
//        Serial.println("Turn on");
//        digitalWrite(13, HIGH);
//         digitalWrite(2, HIGH);
//      }
//      if (command == 0) {
//        Serial.println("Turn off");
//        digitalWrite(13, LOW);
//         digitalWrite(2, LOW);
//      }
   }
  delay(50);  

} // Loop
