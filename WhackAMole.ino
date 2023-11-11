#include <LiquidCrystal.h> // include the library code

// Pin assignments
int mole1LED = 9; // LED for first mole
int mole2LED = 7; // LED for second mole
int mole1Switch = 8; // mole 1 switch
int mole2Switch = 5; // mole 2 switch
int successLED = 2; // LED if successful mole whack
int failedLED = 3; // LED if miss mole

// Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

void setup() {
  pinMode(mole1LED, OUTPUT);
  pinMode(mole2LED, OUTPUT);
  pinMode(mole1Switch, INPUT_PULLUP);
  pinMode(mole2Switch, INPUT_PULLUP);
  pinMode(successLED, OUTPUT);
  pinMode(failedLED, OUTPUT);

  randomSeed(millis()); // Random number generator seed

  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
}

void loop() {
  if (random(2) == 0) {
    moleWhack(mole1Switch, mole1LED); // Mole is at position 1
  } else {
    moleWhack(mole2Switch, mole2LED);
  }
  delay(random(1000, 4000)); // Wait a random time before a new mole appears
}

void moleWhack(int moleSwitch, int moleLED) {
  digitalWrite(moleLED, HIGH); // Turn on the mole LED
  lcd.clear(); // Clear LCD
  lcd.print("Whack a mole"); // Display message
  int moleWait = random(200, 700); // Random time for whack to occur
  long startTime = millis();

  while (millis() - startTime < moleWait) { // Stay in loop until timer expires
    if (digitalRead(moleSwitch) == LOW) {
      digitalWrite(successLED, HIGH); // Blink on
      digitalWrite(moleLED, LOW); // Turn off mole LED, it's been whacked
      lcd.clear(); // Clear LCD
      lcd.print("Whack!"); // Display message
      delay(500);
      digitalWrite(successLED, LOW); // Blink off
      return; // Terminate the function
    }
  }
  digitalWrite(moleLED, LOW); // Turn off mole light for next mole
  digitalWrite(failedLED, HIGH);
  lcd.clear(); // Clear LCD
  lcd.print("Missed!"); // Display missed message
  delay(500);
  digitalWrite(failedLED, LOW);
}
