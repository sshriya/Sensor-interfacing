
//Read 15 bit A19 encoders

#include "SPI.h"
unsigned int result = 0;
unsigned int result1 = 0;
unsigned int result2 = 0;

const int clck = 13;
const int data = 12;

SPISettings mySettings(1000000, MSBFIRST, SPI_MODE2);

void setup() {
Serial.begin(115200);
SPI.begin();

pinMode(clck, OUTPUT);
pinMode(data, INPUT);

digitalWrite(13, HIGH);
}


void loop() {

SPI.beginTransaction(mySettings);  
digitalWrite(13, LOW);

//Reading 8 bit frame (the first half of 16-bit SPI transfer) - data sent does not matter
result1 = SPI.transfer(0b00000000);
// getting last 8 bits (the last half of 16-bit SPI transfer)
result2 = SPI.transfer(0b00000000);

// release SPI    
digitalWrite(13, HIGH);
SPI.endTransaction();

// removing (masking) first bit
result1 &= 0b01111111;
//shifting 8 bit to left. to create emty space for last 8 bit transfer
result1 = result1 << 8;
// merging
result = result1 | result2;

Serial.print("Position reading is: ");
Serial.print(" = ");
Serial.println(result, DEC);
Serial.println();

delayMicroseconds(800);
}
