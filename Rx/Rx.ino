// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define b1 2   // Button 1
#define b2 3   // Button 2
#define b3 4   // Button 3
#define b4 5   // Button 4

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

struct Data_Package{
  bool button1;
  bool button2;
  bool button3;
  bool button4;
};
Data_Package data;

//===========

void setup() {

    Serial.begin(9600);

    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate(RF24_2MBPS);
    radio.setPALevel(RF24_PA_MIN);      
    radio.setChannel(108);
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();

    pinMode(b1,OUTPUT);
    pinMode(b2,OUTPUT);
    pinMode(b3,OUTPUT);
    pinMode(b4,OUTPUT);

  data.button1 = 0;
  data.button2 = 0;
  data.button3 = 0;
  data.button4 = 0;
}

//=============

void loop() {
    getData();
    showData();
    writeData();
}

//==============

void getData() {
    if ( radio.available() ) {
        radio.read(&data, sizeof(Data_Package));
    }
}

void showData() {
        Serial.print("Data received: ");
        Serial.print(data.button1);
        Serial.print(data.button2);
        Serial.print(data.button3);
        Serial.println(data.button4);
}

void writeData() {
  digitalWrite(b1,data.button1);
  digitalWrite(b2,data.button2);
  digitalWrite(b3,data.button3);
  digitalWrite(b4,data.button4);
}
