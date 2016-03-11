#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

File countIt;
LiquidCrystal lcd(9, 6, 5, 4, 3, 2);

const int buttonPin7 = 7;
const int buttonPin8 = 8;
const int buttonPin14 = 14;

int buttonState7 = 0;
int buttonState8 = 0;
int buttonState14 = 0;
int count = 0;
int pressed7 = 0;
int pressed8 = 0;
int pressed14 = 0;

void setup() {
  
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  
  pinMode(10, OUTPUT);
  
  if (!SD.begin(10)) {
    lcd.println("SD Failed!");
    return;
  }
  else {
    lcd.print("SD READY!");
  }
}

void loop() {

  buttonState8 = digitalRead(buttonPin8);
  buttonState7 = digitalRead(buttonPin7);
  buttonState14 = digitalRead(buttonPin14);
  
  //increase the counter and write its value to file "count.txt"
  if (buttonState8 == LOW){
    pressed8 = 1;
  }
  else if (buttonState8 == HIGH) { 
    if (pressed8 == 1){
      countIt = SD.open("count.txt", FILE_WRITE);
      count += 1;
      if (countIt) {
        lcd.clear();
        lcd.print("Writing To File");
        lcd.setCursor(0, 1);
        lcd.print(count);
        countIt.println(count);
        countIt.close();
      }
      else {
        lcd.clear();
        lcd.println("Could Not Write");
        countIt.close();
      }
      pressed8 = 0;
    }
  }
  
  //Delete count.txt from SD card
  if (buttonState7 == LOW)
    pressed7 = 1; 
  else if (buttonState7 == HIGH) { 
    if (pressed7 == 1){
      lcd.clear();
      lcd.print("File Erased");
      SD.remove("count.txt");
      count = 0;
      pressed7 = 0;
    }
  }
  
  //Print contents of count.txt to the serial monitor
  if (buttonState14 == LOW)
    pressed14 = 1; 
  else if (buttonState14 == HIGH) { 
    if (pressed14 == 1){
      lcd.clear();
      lcd.print("File printed to");
      lcd.setCursor(0, 1);
      lcd.print("serial monitor");
      countIt = SD.open("count.txt");
      if (countIt){
      Serial.println("count.txt: ");
        while (countIt.available()) {   
          Serial.write(countIt.read());
        }
        countIt.close();
      }
      pressed14 = 0;
    }
  }
    
}


