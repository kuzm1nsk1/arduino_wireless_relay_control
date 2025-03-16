#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define cePin 9
#define csnPin 10

#define output1 3
#define output2 2
#define output3 5
#define output4 4
#define output5 7
#define output6 6

RF24 radio(cePin, csnPin);

const byte address[6] = "00001";

int outputs[6] = {output1, output2, output3, output4, output5, output6};
int relayState[6] = {LOW, LOW, LOW, LOW, LOW, LOW};

void setup() {

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);

  for (int i = 0; i < 6; i++) {
    
    pinMode (outputs[i], OUTPUT);
    
  }
}

void loop() {

 if (radio.available()) {
  
      radio.read(relayState, sizeof(relayState));

      for (int i = 0; i < 6; i++) {
        
        if (relayState[i] == HIGH) {
          
          digitalWrite (outputs[i], HIGH);
          
        } else {
          
          digitalWrite (outputs[i], LOW);
          
         }
      }  
   }
}
