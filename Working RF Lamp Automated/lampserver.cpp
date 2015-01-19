/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.

 03/17/2013 : Charles-Henri Hallard (http://hallard.me)
              Modified to use with Arduipi board http://hallard.me/arduipi
						  Changed to use modified bcm2835 and RF24 library
TMRh20 2014 - Updated to work with optimized RF24 Arduino library

 */

/**
 * This is an example of how to use the RF24 class on RPi, communicating to an Arduino running
 * the GettingStarted sketch.
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <RF24/RF24.h>

using namespace std;
//
// Hardware configuration
// Configure the appropriate pins for your connections
// Radio CE Pin, CSN Pin, SPI Speed
RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

int main(int argc, char** argv){


  printf("RF24/examples/GettingStarted/\n");

  // Setup and configure rf radio
  radio.begin();
  // sets the power level to low. Can also set to RF24_PA_MAX, RF24_PA_HIGH
  radio.setPALevel(RF24_PA_LOW);

  // optionally, increase the delay between retries & # of retries
  //radio.setRetries(15,15);
  // Dump the configuration of the rf unit for debugging
  radio.printDetails();


/***********************************/
  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.

      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1,pipes[1]);

	radio.startListening();

	// forever loop
	while (1)
	{
			// First, stop listening so we can talk.
			radio.stopListening();


			int data = 1;
			printf("Turning the lamp on.\n");
			bool ok = radio.write(&data,  sizeof(data) );

			if (!ok){
				printf("failed.\n");
			}
			sleep(1);
			data = 0;
			ok = radio.write(&data,  sizeof(data));
			printf("Turning the lamp off.\n");
			if (!ok) {
				printf("failed.\n");
			}
			sleep(1);
	} // forever loop
  return 0;
}

