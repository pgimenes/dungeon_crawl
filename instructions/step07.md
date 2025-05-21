### Stage 7: The Roar of Battle - Combat Encounters (Monster Rooms)

Prepare for battle! In this stage, your hero will finally face the dangers of the dungeon by engaging in combat with monsters. We'll integrate the existing `handleMonsterRoom` function to manage these encounters.

**Files to Create/Edit:**

* `main.cpp` (To call the monster room handler)

---

**Step 1: Integrating Monster Encounters into `main.cpp`**

The `room_handlers.hpp` and `room_handlers.cpp` files already contain the `handleMonsterRoom` function, which has the full combat logic. All we need to do is call it when the player enters a `MONSTER` room.

**In `main.cpp`:**

1.  Open the file named `main.cpp`.
2.  Locate the `switch (currentRoom.type)` statement inside your `if (!currentRoom.visited)` block.
3.  **Add a new `case` for `MONSTER` rooms.** Place it right after your `case TREASURE:` block:

    ```cpp
    switch (currentRoom.type) {
        case EMPTY:
            // Nothing special happens in an empty room, description is enough
            break;
        case TREASURE: { // Use curly braces for new variables within a case
            typeText("💰 You found " + std::to_string(currentRoom.goldAmount) + " gold!");
            player.gold += currentRoom.goldAmount;
            currentRoom.goldAmount = 0; // Treasure taken, prevent re-collection
            currentRoom.type = EMPTY;   // Turn it into an empty room after collection
            break;
        }
        case MONSTER: { // Monster encounter!
            // The handleMonsterRoom function manages the entire fight.
            // It will update player health, gold, and potentially set game over.
            handleMonsterRoom(currentRoom, player);

            // After the fight, if the monster is defeated, the room becomes empty.
            // This is handled inside handleMonsterRoom by setting room.type = EMPTY.
            // If the player died, gameOver will be set to true inside handleMonsterRoom.

            // It's good practice to re-check player health immediately after combat
            // though the main loop's death check will also catch it.
            if (player.health <= 0) {
                typeText("The dungeon claims another victim. Game Over!");
                gameOver = true; // Set game over if player died in combat
            }
            break;
        }
        // ... other room types will go here later ...
        default:
            typeText("You've entered a strange room..."); // Fallback for types not yet handled
            break;
    }
    ```
    * **Explanation:**
        * `handleMonsterRoom(currentRoom, player);` is the key line. It takes the current room (which has the monster's details like `monsterLevel`) and the `player` object. The function will then run the combat simulation, updating the player's health, and potentially adding gold if the monster is defeated.
        * The comments emphasize that `handleMonsterRoom` itself changes `currentRoom.type` to `EMPTY` after a successful fight and can set `gameOver` if the player dies.
        * The explicit `if (player.health <= 0)` check right after the `handleMonsterRoom` call is a good safety measure to ensure the game ends immediately if the player's health drops to 0 or below during combat, even though a similar check exists at the end of the `while` loop.

---

**Step 2: Compile and Test Your Combat Prowess!**

It's time to face the creatures of the dungeon!

1.  **Open your terminal or command prompt.**
2.  **Navigate to your project folder.**
3.  **Compile your code.** Make sure you're compiling all the `.cpp` files, including `room_handlers.cpp` which contains the monster logic:
    ```bash
    g++ main.cpp utils.cpp display_functions.cpp room_generator.cpp room_handlers.cpp -o dungeon_game
    ```
    * If you encounter any compilation errors, carefully review the new `case MONSTER` block in `main.cpp` for typos or missing breaks.
4.  **Run your game!**
    ```bash
    ./dungeon_game
    ```
    * Now, as you move, you should encounter `[M]` symbols on your map for Monster rooms.
    * When you enter a `[M]` room, the combat sequence should begin. You'll be prompted to attack or run.
    * Your player's health should decrease during combat, and you might defeat monsters to gain gold.
    * If your health drops to 0 or below during a fight, the game should end with a "Game Over!" message.

Excellent! Your dungeon now offers thrilling combat encounters, a core part of any adventurer's journey. You've taken another massive leap in building your game. In the next stage, we'll implement more room types, starting with `POTION` rooms to help your hero recover!