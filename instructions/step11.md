### Progress Report: Where We Are

**Implemented (All Core Gameplay Features Are In!):**

* **Stage 1: Basic Setup and Welcome**
* **Stage 2: The Game's Blueprint - Defining Our World and Hero**
* **Stage 3: Bringing Your Hero to Life - Displaying Player Status**
* **Stage 4: Unveiling the Dungeon - Basic Map Generation and Display**
* **Stage 5: The First Steps - Player Movement**
* **Stage 6: Populating the Dungeon & Basic Room Interactions (Treasure and Empty Rooms)**
* **Stage 7: The Roar of Battle - Combat Encounters (Monster Rooms)**
* **Stage 8: Health and Hazards - Potion and Trap Rooms**
* **Stage 9: Mind Games and Marketplaces - Puzzle and Merchant Rooms**
* **Stage 10: The Grand Escape - The Exit Room and Winning the Game**
    * **Crucially, the `EXIT` room logic is now implemented in `main.cpp`**, checking for `GOLD_TO_ESCAPE` and setting `gameOver = true;` on success, or informing the player if they need more gold.

**Remaining Quests (Optional Polish & Enhancements):**

* **Inventory Management (Usage):** While items can be bought from the merchant and stored, there's no system for the player to *use* them from their inventory (e.g., using a health potion bought or found). This would significantly enhance player strategy.
* **Game Over Screen:** A more dedicated "Game Over" or "Victory" screen instead of just text before exiting.
* **Replayability:** Option to start a new game after winning or losing.
* **More Item Types & Effects:** Expanding the variety of items and their uses.
* **Advanced Combat Mechanics:** Adding more depth to combat (e.g., critical hits, monster special attacks).

---

### Bonus Stage: Inventory Usage & Game Over Flow

This stage will focus on adding a crucial strategic element: the ability for the player to use items from their inventory at will (specifically, health potions for now). We'll also refine the game over/win flow.

**Files to Create/Edit:**

* `main.cpp` (For input handling to use inventory and refining game end)
* `display_functions.hpp`/`display_functions.cpp` (Optional: To display inventory)
* `room_handlers.hpp`/`room_handlers.cpp` (Optional: To move item usage logic if it gets complex)

---

**Step 1: Implementing Inventory Usage (Health Potions)**

We'll add a new input option for the player to use items. For simplicity, we'll start with `HEALTH_POTION`s.

**In `main.cpp`:**

1.  **Add a new input option:** In the `main.cpp` `while (!gameOver)` loop, in the section where you list movement options (W, S, A, D, Q), add a new option for inventory. Let's use 'I' for Inventory.

    ```cpp
    // ... (existing movement options) ...
    std::cout << "I - Use Item (Inventory)\\n"; // Add this line
    std::cout << "Q - Quit Game\\n";
    std::cout << "Your choice: ";
    std::cin >> input;
    // ...
    ```

2.  **Add a new `case 'I'` to the input `switch` statement:** After the movement cases, before the `case 'Q'`.

    ```cpp
    char input;
    std::cin >> input;
    input = toupper(input); // Convert to uppercase for consistent handling

    switch (input) {
        case 'W': // ... existing movement logic ...
        case 'S': // ... existing movement logic ...
        case 'A': // ... existing movement logic ...
        case 'D': // ... existing movement logic ...
        case 'I': { // Use Item / Inventory
            clearScreen();
            displayStatus(player); // Show current status before inventory
            typeText("\n🎒 Your Inventory:");

            if (player.inventory.empty()) {
                typeText("Your inventory is empty. Find some items first!");
            } else {
                typeText("Available Items:");
                // Count potions for display
                int healthPotions = 0;
                for (ItemType item : player.inventory) {
                    if (item == HEALTH_POTION) {
                        healthPotions++;
                    }
                }

                if (healthPotions > 0) {
                    typeText("1. Health Potion (x" + std::to_string(healthPotions) + ")");
                } else {
                    typeText("No Health Potions available.");
                }
                typeText("Enter number to use, or 0 to cancel:");
                int itemChoice;
                std::cin >> itemChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

                if (itemChoice == 1 && healthPotions > 0) {
                    // Find and remove one health potion
                    auto it = std::find(player.inventory.begin(), player.inventory.end(), HEALTH_POTION);
                    if (it != player.inventory.end()) {
                        player.inventory.erase(it);
                        typeText("✨ You consume a Health Potion. You feel invigorated!");
                        player.health += 30; // Restore a fixed amount of health
                        if (player.health > MAX_HEALTH) {
                            player.health = MAX_HEALTH;
                        }
                        typeText("Your health is now " + std::to_string(player.health) + "/" + std::to_string(MAX_HEALTH) + ".");
                    }
                } else if (itemChoice == 0) {
                    typeText("You decide not to use anything.");
                } else {
                    typeText("Invalid item choice or no such item.");
                }
            }
            waitForKey();
            // Don't change player.x, player.y so they stay in the current room
            // and the main loop will redraw the map and status.
            break;
        }
        case 'Q': // ... existing quit logic ...
        default: // ... existing default case ...
    }
    ```
    * **Explanation:**
        * This `case 'I'` will clear the screen, show the player's status, and then list the contents of their inventory (specifically focusing on `HEALTH_POTION` for now).
        * It allows the player to choose an item to use.
        * If `HEALTH_POTION` is chosen and available, one potion is removed from the inventory, and the player's health is restored, capped at `MAX_HEALTH`.
        * `std::cin.ignore()` is important to clear the input buffer after `std::cin >> itemChoice;` to prevent issues with subsequent `std::cin.get()` calls.
        * The player's position is not changed, so they remain in the same room after interacting with their inventory.

---

**Step 2: Refining Game Over/Win Flow**

Currently, when `gameOver` becomes true (either by winning or dying), the loop simply ends. Let's add a more conclusive message and ensure the game actually exits.

**In `main.cpp`:**

1.  **Modify the `main()` function:** Wrap the `playGame()` call in a loop, asking the user if they want to play again.

    ```cpp
    int main() {
        srand(static_cast<unsigned int>(time(0)));

        char playAgain = 'Y';
        while (toupper(playAgain) == 'Y') {
            playGame(); // This function now contains the full game loop

            typeText("\n\nWould you like to play again? (Y/N):");
            std::cin >> playAgain;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
            clearScreen(); // Clear screen for new game or exit
        }

        typeText("\nThank you for playing Dungeon Crawl! See you next time, adventurer!");
        waitForKey();
        return 0;
    }
    ```
    * **Explanation:**
        * The `playGame()` function (which contains your `while (!gameOver)` loop) is now called inside a `while (toupper(playAgain) == 'Y')` loop.
        * After `playGame()` finishes (meaning `gameOver` is true), the player is asked if they want to play again.
        * If 'Y' is entered, `playGame()` is called again, effectively starting a new game. If 'N' (or anything else), the outer loop ends, and the final thank you message is displayed.

2.  **Ensure `playGame()` resets player/dungeon for a new game:** Inside your `playGame()` function, at the very beginning, ensure `Player player;` and `DungeonMap dungeon = initializeDungeon();` are *inside* `playGame()`, so they are re-initialized each time a new game starts. Based on your previous snippet, they already are, which is perfect!

    ```cpp
    void playGame() {
        clearScreen();
        typeText("🏰 Welcome to the Dungeon Crawl! 🏰", 30);
        // ... rest of welcome text ...
        waitForKey();

        // Initialize player and dungeon - these should be local to playGame()
        Player player;
        DungeonMap dungeon = initializeDungeon();

        // ... rest of existing playGame() setup ...
    }
    ```

---

**Step 3: Compile and Test Your Polished Game!**

This is the very final compile, adventurer!

1.  **Open your terminal or command prompt.**
2.  **Navigate to your project folder.**
3.  **Compile your code.** Ensure you're compiling all `.cpp` files:
    ```bash
    g++ main.cpp utils.cpp display_functions.cpp room_generator.cpp room_handlers.cpp -o dungeon_game
    ```
    * If you encounter any compilation errors, carefully review the new `case 'I'` block in `main.cpp` for typos, especially with `std::find` and `std::vector::erase`. Ensure you have `#include <algorithm>` and `#include <cctype>` (for `toupper`) at the top of `main.cpp`.
4.  **Run your game!**
    ```bash
    ./dungeon_game
    ```
    * Play the game. When you buy a `HEALTH_POTION` from a merchant, or if you modify `TREASURE` rooms to sometimes drop them, press 'I' to open your inventory.
    * Try using a health potion and see your health increase.
    * Win the game, or die, and then see if you are prompted to play again. Test both 'Y' and 'N' responses.

---

**Congratulations, Grand Adventurer!**

You have not only implemented all the core gameplay features of your Dungeon Crawl, but you've also added inventory management and a proper game-over/restart flow!

You now possess a complete, playable, and engaging text-based dungeon crawler written in C++! This is a significant accomplishment in game development.

You can now take this project in any direction you choose for further enhancement, or simply be proud of what you've created.

Well done!