### Stage 8: Health and Hazards - Potion and Trap Rooms

In this stage, we'll introduce two new room types that directly impact your hero's health: `POTION` rooms for recovery and `TRAP` rooms for danger!

**Files to Create/Edit:**

* `main.cpp` (To handle what happens in Potion and Trap rooms)

---

**Step 1: Handling Potion Rooms in `main.cpp`**

Potion rooms will allow your hero to restore lost health, a vital resource after tough monster encounters!

**In `main.cpp`:**

1.  Open the file named `main.cpp`.
2.  Locate the `switch (currentRoom.type)` statement inside your `if (!currentRoom.visited)` block.
3.  **Add a new `case` for `POTION` rooms.** Place it after your `case MONSTER:` block:

    ```cpp
    switch (currentRoom.type) {
        case EMPTY:
            // ... (existing EMPTY case) ...
            break;
        case TREASURE: {
            // ... (existing TREASURE case) ...
            break;
        }
        case MONSTER: {
            // ... (existing MONSTER case) ...
            break;
        }
        case POTION: { // Found a Potion!
            typeText("❤️ You found a glowing potion! You feel your strength returning.");
            // Restore health, but not above MAX_HEALTH
            player.health += currentRoom.healthAmount;
            if (player.health > MAX_HEALTH) {
                player.health = MAX_HEALTH;
            }
            typeText("Your health is now " + std::to_string(player.health) + "/" + std::to_string(MAX_HEALTH) + ".");
            currentRoom.healthAmount = 0; // Potion consumed
            currentRoom.type = EMPTY;     // Room becomes empty after potion is taken
            break;
        }
        // ... other room types will go here later ...
        default:
            typeText("You've entered a strange room..."); // Fallback for types not yet handled
            break;
    }
    ```
    * **Explanation:**
        * `player.health += currentRoom.healthAmount;`: Adds the health provided by the potion (which is set in `createPotionRoom()` in `room_generator.cpp`) to the player's current health.
        * `if (player.health > MAX_HEALTH) { player.health = MAX_HEALTH; }`: This crucial line ensures that the player's health doesn't go above `MAX_HEALTH`, preventing overhealing.
        * `currentRoom.healthAmount = 0;` and `currentRoom.type = EMPTY;`: These lines ensure the potion is consumed and the room becomes an `EMPTY` room after the player uses it, preventing multiple uses.

---

**Step 2: Handling Trap Rooms in `main.cpp`**

Trap rooms will add a layer of danger to your dungeon, requiring players to be cautious!

**In `main.cpp`:**

1.  Open the file named `main.cpp`.
2.  Locate the `switch (currentRoom.type)` statement inside your `if (!currentRoom.visited)` block.
3.  **Add a new `case` for `TRAP` rooms.** Place it after your `case POTION:` block:

    ```cpp
    switch (currentRoom.type) {
        case EMPTY:
            // ... (existing EMPTY case) ...
            break;
        case TREASURE: {
            // ... (existing TREASURE case) ...
            break;
        }
        case MONSTER: {
            // ... (existing MONSTER case) ...
            break;
        }
        case POTION: {
            // ... (existing POTION case) ...
            break;
        }
        case TRAP: { // Uh oh, a Trap!
            typeText("💥 A hidden trap springs! You take " + std::to_string(currentRoom.damageAmount) + " damage!");
            player.health -= currentRoom.damageAmount;
            typeText("Your health is now " + std::to_string(player.health) + "/" + std::to_string(MAX_HEALTH) + ".");
            currentRoom.damageAmount = 0; // Trap triggered, prevent re-triggering
            currentRoom.type = EMPTY;     // Room becomes empty after trap is triggered
            break;
        }
        // ... other room types will go here later ...
        default:
            typeText("You've entered a strange room..."); // Fallback for types not yet handled
            break;
    }
    ```
    * **Explanation:**
        * `player.health -= currentRoom.damageAmount;`: Deducts the damage taken from the trap (which is set in `createTrapRoom()` in `room_generator.cpp`) from the player's health.
        * `currentRoom.damageAmount = 0;` and `currentRoom.type = EMPTY;`: These lines ensure the trap is triggered only once and the room becomes an `EMPTY` room afterward.
    * **Important:** Remember the general player death check you have in `main.cpp` after the `if (!currentRoom.visited)` block:
        ```cpp
        // Check for player death (this is already present in your main.cpp)
        if (player.health <= 0) {
            typeText("\n💀 Your wounds are too severe. You collapse to the ground...");
            typeText("The dungeon claims another victim. Game Over!");
            gameOver = true;
        }
        ```
        This check will now correctly handle if the player dies from a trap as well!

---

**Step 3: Compile and Test Your Dungeon Survival Skills!**

Time to see your new room types in action!

1.  **Open your terminal or command prompt.**
2.  **Navigate to your project folder.**
3.  **Compile your code.** Make sure you're compiling all the `.cpp` files:
    ```bash
    g++ main.cpp utils.cpp display_functions.cpp room_generator.cpp room_handlers.cpp -o dungeon_game
    ```
    * If you encounter any compilation errors, carefully review the new `case POTION` and `case TRAP` blocks in `main.cpp`.
4.  **Run your game!**
    ```bash
    ./dungeon_game
    ```
    * As you move, you should now encounter `[H]` symbols on your map for Potion rooms and `[!]]` symbols for Trap rooms.
    * When you enter a `[H]` room, your health should increase (up to `MAX_HEALTH`).
    * When you enter a `[!]]` room, your health should decrease.
    * Test if you can die from a trap!

Great job! Your dungeon is getting more complex and dangerous, requiring careful health management. In the next stage, we'll introduce `PUZZLE` rooms to challenge the player's mind and `MERCHANT` rooms for strategic gear upgrades!