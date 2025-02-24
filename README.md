# CodeJoy.

This project is an Arduino-based game platform that by default, lets you play two interactive games on a single board:
- **Memory Game:** A Simon Says–style game where you repeat an LED sequence.
- **Reaction Game:** A game for two players who race to press their button as soon as an LED lights up. Rounds are repeated if the reaction time is less than 50 ms (to prevent button spamming).

---

## Hardware Requirements

- **Arduino Board:** (Uno, Mega, etc.)
- **I2C LCD Display:** 16x2 character display at I2C address 0x27.
- **Joysticks:** Two joysticks with integrated push buttons (one per player).
- **LEDs:** Four LEDs in the colors red, blue, yellow, and green.
- **Resistors:** Current-limiting resistors for LEDs and (if needed) for joystick buttons.
- **Breadboard & Jumper Wires**

---

## Pin Configuration

### LCD Display (I2C)
- **LCD Initialization:**  
  `LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);`  
  The LCD uses I2C with a custom pin mapping as required by the library.

### Joystick (Player 1)
- **SW_pin1:** Digital pin 2 (push button)
- **X_pin1:** Analog pin 1 (x-axis)
- **Y_pin1:** Digital pin 3 (y-axis)

### Joystick (Player 2)
- **SW_pin2:** Digital pin 4 (push button)
- **X_pin2:** Analog pin 0 (x-axis)
- **Y_pin2:** Digital pin 5 (y-axis)

### LEDs
- **RED_LED:** Digital pin 8
- **BLUE_LED:** Digital pin 7
- **YELLOW_LED:** Digital pin 6
- **GREEN_LED:** Digital pin 9

*Note:* The LED order in the `ledPins` array corresponds to the color names in the `colors` array. Use proper resistors to protect your LEDs.

---

## Code Overview

### Main Menu
- **Display:** The LCD shows the main menu with instructions.
- **Game Selection:**  
  - Move the left joystick **left** to start the Memory Game.
  - Move the left joystick **right** to start the Reaction Game.
- **Function Flow:**  
  The `loop()` function shows the menu, gets the choice via `getMenuChoice()`, and calls the corresponding game function.

### Memory Game
- **Sequence Generation:**  
  `generateSequence()` creates a random sequence of LED indices.
- **Displaying the Sequence:**  
  `displaySequence()` blinks the LEDs one-by-one as per the current round.
- **Player Input:**  
  `getPlayerInput()` uses the left joystick (read via `readJoystick()`) to capture directional input:
  - **Left:** BLUE (x < 100)
  - **Right:** RED (x > 900)
  - **Up:** YELLOW (y < 100)
  - **Down:** GREEN (y > 900)
- **Validation:**  
  `checkSequence()` compares the player's inputs with the generated sequence. Correct sequences advance the round; an error results in a game-over message.

### Reaction Game
- **Round Setup:**  
  The game consists of 5 rounds. Each round starts with a “Get ready!” message.
- **Random Delay:**  
  A random wait (between 2000 to 5000 ms) is inserted before an LED is lit.
- **Go Signal:**  
  When the LED lights, the LCD shows “GO!” and the game records the time.
- **Player Reaction:**  
  Both players try to press their assigned joystick button:
  - **Player 1:** SW_pin1 (Digital pin 2)
  - **Player 2:** SW_pin2 (Digital pin 4)
- **Spamming Prevention:**  
  If the reaction time is less than 50 ms, the LCD warns with "No spamming!" and "Redo round" (using multiple prints to meet the 16-character limit), and the round is repeated.
- **Scoring:**  
  Reaction times are displayed along with the winning player. After 5 rounds, the final scores and overall winner are shown.

---

## Coding New Games

The project is designed with modularity in mind. Here are some tips for adding your own games:

1. **Create a New Game Function:**
   - Write a new function (e.g., `void playNewGame()`) that contains your game logic.
   
2. **Integrate with the Menu:**
   - Update the main menu (`showMenu()` and `getMenuChoice()`) to include an option for your new game.
   - In `loop()`, add a condition to call your new game function based on the user’s choice.

3. **Display Considerations:**
   - Remember the LCD has a 16-character limit per line. If your text exceeds this limit, split it into multiple prints or clear the screen between messages.

4. **Reusing Existing Code:**
   - Use the joystick and LED functions as a reference. For example, use `analogRead()` to capture joystick movement and `digitalWrite()` to control LED output.
   - Utilize the existing delay and randomization techniques (`delay()`, `randomSeed()`, and `random()`) as shown in the code.

5. **Testing:**
   - Incrementally test your new game on the hardware to ensure it works with the current setup and doesn't conflict with existing features.

---

## Final Notes

- Ensure all wiring follows the pin configuration specified above.
- Double-check that your power supply, resistors, and connections are correct to avoid damaging components.
- This framework is a great starting point for experimenting with interactive Arduino projects. Modify, expand, and create new game experiences!

Happy coding and gaming!
