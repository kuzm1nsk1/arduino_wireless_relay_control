#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define cePin 9
#define csnPin 10

#define button1 2
#define button2 3
#define button3 4
#define button4 5
#define button5 6
#define button6 7


RF24 radio(cePin, csnPin);

const byte address[6] = "00001";

int relayState[6] = { LOW, LOW, LOW, LOW, LOW, LOW };
unsigned long relayTime[6] = { 0, 0, 0, 0, 0, 0 };
int buttons[6] = { button1, button2, button3, button4, button5, button6 };
unsigned long buttonTimer = 0;
bool buttonPressed[6] = { false, false, false, false, false, false };
bool buttonActive = false;
bool longPress[6] = { false, false, false, false, false, false };
bool longPressActive = false;
const int longPressTime = 2000;


void setup() {

  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);

  for (int i = 0; i < 6; i++) {

    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {

  for (int i = 0; i < 6; i++) {

    if (digitalRead(buttons[i]) == LOW) {

      if (buttonActive == false) {

        buttonActive = true;
        buttonTimer = millis();
      }

      buttonPressed[i] = true;
    }
  }

  if (buttonActive == true && millis() - buttonTimer > longPressTime && longPressActive == false) {

    longPressActive = true;

    for (int i = 0; i < 6; i++) {

      if (buttonPressed[0] == true && buttonPressed[1] == true) {

        for (int i = 0; i < 6; i++) {

          relayState[i] = LOW;
        }
      } else if (buttonPressed[4] == true && buttonPressed[5] == true) {

        for (int i = 0; i < 6; i++) {

          relayState[i] = HIGH;
        }
      } else if (buttonPressed[i] == true) {

        longPress[i] = true;
        relayState[i] = HIGH;
        relayTime[i] = millis();
      }
    }
  }

  if (buttonActive == true && digitalRead(buttons[0]) == HIGH && digitalRead(buttons[1]) == HIGH && digitalRead(buttons[2]) == HIGH && digitalRead(buttons[3]) == HIGH && digitalRead(buttons[4]) == HIGH && digitalRead(buttons[5]) == HIGH) {

    if (longPressActive == true) {

      longPressActive = false;

    } else {

      for (int i = 0; i < 6; i++) {

        if (buttonPressed[i] == true) {

          relayState[i] = !relayState[i];
        }
      }
    }

    buttonActive = false;

    for (int i = 0; i < 6; i++) {

      buttonPressed[i] = false;
    }
  }

  for (int i = 0; i < 6; i++) {

    if (millis() - relayTime[i] >= 10000 && longPress[i] == true) {

      relayTime[i] = millis();
      longPress[i] = false;
      relayState[i] = LOW;
    }
  }

  radio.write(relayState, sizeof(relayState));
}