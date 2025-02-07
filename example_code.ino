#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

// Player 1 Joystick
const int SW_pin1 = 2;
const int X_pin1 = 1;
const int Y_pin1 = 3;

// Player 2 Joystick
const int SW_pin2 = 5; 
const int X_pin2 = 0;
const int Y_pin2 = 4;

int RED_LED = 5;
int BLUE_LED = 8;
int YELLOW_LED = 7;
int GREEN_LED = 6;

// Array for LED pins
int ledPins[] = {RED_LED, BLUE_LED, YELLOW_LED, GREEN_LED};
const char* colors[] = {"RED", "BLUE", "YELLOW", "GREEN"};

int sequence[6]; // Store a sequence of 6 LEDs
int playerSequence[6]; // Store the player's input sequence
int sequenceLength = 6; // Length of the sequence for the game
int currentRound = 0; // Current round of the game

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(SW_pin1, INPUT_PULLUP);
  pinMode(SW_pin2, INPUT_PULLUP);
  
  lcd.begin(16,2);
  lcd.backlight();
  
  randomSeed(analogRead(4)); // Use a different analog pin for randomSeed
}

void loop() {
  showMenu();
  int gameChoice = getMenuChoice();
  
  if (gameChoice == 1) {
    playMemoryGame();
  } else if (gameChoice == 2) {
    playReactionGame();
  }
}

void showMenu() {
  lcd.clear();
  lcd.print("Select Game:");
  lcd.setCursor(0, 1);
  lcd.print("1:Memory 2:React");
}

int getMenuChoice() {
  while (true) {
    int x1 = analogRead(X_pin1);
    if (x1 < 100) return 1; // Left for Memory Game
    if (x1 > 900) return 2; // Right for Reaction Game
    delay(50); // Small delay to prevent rapid readings
  }
}
