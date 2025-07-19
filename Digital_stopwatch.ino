#include <LiquidCrystal.h>
      // Initialize LCD: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
     // Button pins
const int startButton = 8;
const int stopButton = 9;
const int resetButton = 10;
     // Stopwatch variables
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
bool running = false;

void setup() {
  // Set button pins as input with internal pull-up resistors
  pinMode(startButton, INPUT_PULLUP);
  pinMode(stopButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Stopwatch Ready");
}

void loop() {
  // Start button pressed
  if (digitalRead(startButton) == LOW) {
    if (!running) {
      running = true;
      startTime = millis() - elapsedTime;  // resume from previous
      delay(200); // debounce
    }
  }

  // Stop button pressed
if (digitalRead(stopButton) == LOW) {
    if (running) {
      running = false;
      elapsedTime = millis() - startTime;
      delay(200); // debounce
    }
  }

  // Reset button pressed
  if (digitalRead(resetButton) == LOW) {
    running = false;
    elapsedTime = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Stopwatch Reset");
    delay(500); // debounce
  }

  // Update time if running
  if (running) {
    elapsedTime = millis() - startTime;
  }

  // Display time
  lcd.setCursor(0, 1);
  unsigned long seconds = elapsedTime / 1000;
  unsigned long minutes = seconds / 60;
  seconds = seconds % 60;
  unsigned long milliseconds = (elapsedTime % 1000) / 10;
  lcd.print("Time: ");
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) lcd.print("0");
  lcd.print(seconds);
lcd.print(".");
  if (milliseconds < 10) lcd.print("0");
  lcd.print(milliseconds);
}
