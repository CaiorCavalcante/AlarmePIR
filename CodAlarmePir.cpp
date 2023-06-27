#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(13, 12, 14, 15, 16, 17);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {8, 7, 6, 9};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char* password = "1234";

const int pinoPIR = 1;
const int pinoLED = 11;
const int pinoBUZZER = 10;
int position = 0;
int sensor = 0;

void setup() {
  Serial.begin(9600);

  pinMode(pinoLED, OUTPUT);
  pinMode(pinoPIR, INPUT);
  pinMode(pinoBUZZER, OUTPUT);
}

void loop() {
  if (digitalRead(pinoPIR) == HIGH) {
    digitalWrite(pinoLED, HIGH);
    tone(pinoBUZZER, 196);
    sensor = 1;

    if (position == strlen(password)) {
      noTone(pinoBUZZER);
      digitalWrite(pinoLED, LOW);
      lcd.clear();
      lcd.print("OK!");
      sensor = 0;
      delay(500000);
      position = 0;
    } else {
      char key = keypad.getKey();
      
      if (key) {
        Serial.println(key);
        lcd.print(key);
      }
      
      if (key == '*' || key == '#') {
        position = 0;
        Serial.println("Comece outra vez");
        lcd.clear();
      }
      
      if (key == password[position]) {
        position++;
      }
    }
  } else {
    if (sensor == 0) {
      digitalWrite(pinoLED, LOW);
      noTone(pinoBUZZER);
    }
  }
}
