
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo door;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(
  makeKeymap(keys), rowPins, colPins, ROWS, COLS
);

String password = "1234";
String entered = "";

void setup() {
  lcd.init();
  lcd.backlight();

  door.attach(10);
  door.write(0);

  lcd.setCursor(0, 0);
  lcd.print("Digital Door");
  lcd.setCursor(0, 1);
  lcd.print("Enter Password");
  delay(1500);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '*') {
      entered = "";
      lcd.clear();
      lcd.print("Enter Password");
    }
    else if (key == '#') {
      lcd.clear();

      if (entered == password) {
        lcd.print("Access Granted");
        lcd.setCursor(0, 1);
        lcd.print("Door Open");
        door.write(90);
        delay(3000);
        door.write(0);
      } else {
        lcd.print("Wrong Password");
        delay(1500);
      }

      entered = "";
      lcd.clear();
      lcd.print("Enter Password");
    }
    else if (entered.length() < 4) {
      entered += key;
      lcd.setCursor(0, 1);
      lcd.print("Code: ");
      lcd.print(entered);
    }
  }
}
