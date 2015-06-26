#include <Wire.h>

/*
* temporary - will replace with approriate libaries for 7-segment display
*/
#include <LiquidCrystal.h>

// after bit shifting will be converted to I2C slave address 8
#define SLAVE_ADDRESS 0x04

/*
* temporary - initialize lcd object and set I2C simulating arming button 
* pin/state
*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const char armingPin = 6;
char armingButtonState = LOW;

// armed indicator led pin
const char armedPin = 8;

// user trigger button pin and state
const char triggerPin = 7;
char triggerState = LOW;

// the controller must be armed by an I2C message before the user button will be
// activated. Once armed the system cannot be armed again until after a
// countdown and I2C send
boolean systemArmed = false;

// captures the state of trigger button. If false, prevents a button push
// from triggering a countdown. Should be set to true when the system becomes
// armed and then to false again the first time the button is pushed.
boolean triggerReady = false;

// countdown timer = 5 seconds
const long interval = 5000;

// contains the last data received or sent over the i2c bus
int inCode;
int outCode;

void setup() {
  // start I2C slave
  Wire.begin(SLAVE_ADDRESS);
  
  // I2C communication callbacks
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  
  /*
  * temporary - setup and test lcd
  */
  lcd.begin(16, 2);
  printStatus();
  
  // set the armedPin to OUTPUT
  pinMode(armedPin, OUTPUT);
  
  // set the triggerPin to INPUT
  pinMode(triggerPin, INPUT);
}

void loop() {
  
  triggerState = digitalRead(triggerPin);
  if (triggerState == HIGH && systemArmed && triggerReady) {
    digitalWrite(armedPin, LOW);
    triggerReady = false;
    
    /*
    * temporary
    */
    printStatus();
    
    countdown();
  }
}

void receiveData(int numBytes) {
  while (Wire.available()) {
    // capture the data and decide which command it represents
    inCode = Wire.read();
    switch (inCode) {
      case 1:
        armBeforeCountdown();
        break;
      case 2:
        disarmAfterCountdown();
        break;
      default:
        /*
        * temporary
        */
        lcd.clear();
        lcd.print("Unrecognized cmd");
    }
  }
}

void sendData() {
  // send the outgoing code
  Wire.write(outCode);
}

void armBeforeCountdown() {
  if (!systemArmed) {
    systemArmed = true;
    triggerReady = true;
    digitalWrite(armedPin, HIGH);
    
    /*
    * temporary
    */
    printStatus();
  }
}

void disarmAfterCountdown() {
  systemArmed = false;
  
  /*
  * temporary
  */
  printStatus();
  
  outCode = 2;
}

// nonblocking countdown timer
void countdown() {
  long curr = millis();
  long delta = millis() - curr;
  while ((interval - delta) >= 0) {
    /*
    * temporary
    */
    lcd.setCursor(15, 0);
    lcd.print((((interval - delta)) / 1000) + 1);
    
    delta = millis() - curr;
  }
  
  /*
  * temporary
  */
  lcd.setCursor(15, 0);
  lcd.print(" ");
  
  outCode = 1;
}

/*
* temporay - print system state to lcd display
*/
void printStatus() {
  lcd.clear();
  lcd.print("Sys. armed:  ");
  lcd.print(systemArmed);
  lcd.setCursor(0, 1);
  lcd.print("Trig. ready: ");
  lcd.print(triggerReady);
}

