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

// New variables for round system
int currentRound = 1; // Start with round 1
int maxRounds = 5; // Total number of rounds
int roundSuccesses = 0; // Count of successful hits in the current round
int hitsPerRound = 3; // Number of successful hits needed to advance to the next round

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
  // Check if all rounds are completed
  if (currentRound > maxRounds) {
    lcd.clear();
    lcd.print("Game Over!");
    lcd.setCursor(0, 1);
    lcd.print("Well Played!");
    delay(3000); // Display message for 3 seconds
    return; // End the game loop
  }

  // Display the current round
  lcd.clear();
  lcd.print("Round: ");
  lcd.print(currentRound);

  // Choose a random mole to appear
  if (random(2) == 0) {
    moleWhack(mole1Switch, mole1LED); // Mole is at position 1
  } else {
    moleWhack(mole2Switch, mole2LED);
  }

  // Decrease wait time between moles in each round
  delay(random(1000 - (200 * currentRound), 4000 - (800 * currentRound)));
}

void moleWhack(int moleSwitch, int moleLED) {
  digitalWrite(moleLED, HIGH); // Turn on the mole LED
  lcd.clear(); // Clear LCD
  lcd.print("Whack a mole!"); // Display message

  // Decrease the wait time in each round to make it more challenging
  int moleWait = random(200 - (20 * currentRound), 700 - (70 * currentRound)); // Decrease time as rounds progress
  moleWait = max(moleWait, 100); // Ensure time doesn't go below 100 milliseconds
  long startTime = millis();

  while (millis() - startTime < moleWait) { // Stay in loop until timer expires
    if (digitalRead(moleSwitch) == LOW) {
      digitalWrite(successLED, HIGH); // Blink on
      digitalWrite(moleLED, LOW); // Turn off mole LED, it's been whacked
      lcd.clear(); // Clear LCD
      lcd.print("Whack!"); // Display message
      delay(500);
      digitalWrite(successLED, LOW); // Blink off

      roundSuccesses++; // Increment successful hits
      // Check if enough hits are made to advance to the next round
      if (roundSuccesses >= hitsPerRound) {
        currentRound++; // Move to the next round
        roundSuccesses = 0; // Reset successes for the new round
        lcd.clear();
        lcd.print("Round ");
        lcd.print(currentRound);
        lcd.print(" Start!");
        delay(1000); // Pause before starting the next round
      }

      return; // Terminate the function
    }
  }

  digitalWrite(moleLED, LOW); // Turn off mole light for next mole
  digitalWrite(failedLED, HIGH); // Indicate a missed mole
  lcd.clear(); // Clear LCD
  lcd.print("Missed!"); // Display missed message
  delay(500);
  digitalWrite(failedLED, LOW); // Turn off failed LED
}
