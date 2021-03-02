// SimpleTx - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN  10

#define b1 2   // Button 1
#define b2 3   // Button 2
#define b3 4   // Button 3
#define b4 5   // Button 4
const byte slaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1; // send once per millisecond

struct Data_Package{
  bool button1;
  bool button2;
  bool button3;
  bool button4;
};
Data_Package data;

void setup() {

    Serial.begin(9600);

    Serial.println("SimpleTx Starting");
    radio.begin();
    radio.setDataRate(RF24_2MBPS);      
    radio.setChannel(108);
    radio.setPALevel(RF24_PA_MIN);
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(slaveAddress);

    pinMode(b1,INPUT_PULLUP);
    pinMode(b2,INPUT_PULLUP);
    pinMode(b3,INPUT_PULLUP);
    pinMode(b4,INPUT_PULLUP);

  data.button1 = 0;
  data.button2 = 0;
  data.button3 = 0;
  data.button4 = 0;
} 

//====================

void loop() {
    currentMillis = micros();
    if (currentMillis - prevMillis >= txIntervalMillis) {
        send();
        prevMillis = micros();
   }
}

//====================

void send() {
    bool rslt;
    rslt =  radio.write(&data, sizeof(Data_Package));
    
    Serial.print("Data Sent ");
    Serial.print(data.button1);
    Serial.print(data.button2);
    Serial.print(data.button3);
    Serial.print(data.button4);
    
    if (rslt) {
        Serial.println("  Acknowledge received");
        updateMessage();
    }
    else {
        Serial.println("  Tx failed");
    }
}

//================

void updateMessage() {
  data.button1 = (!digitalRead(b1));
  data.button2 = (!digitalRead(b2));
  data.button3 = (!digitalRead(b3));
  data.button4 = (!digitalRead(b4));
}
