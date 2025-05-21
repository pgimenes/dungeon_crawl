### Stage 9: Mind Games and Marketplaces - Puzzle and Merchant Rooms

In this stage, your hero will encounter rooms that challenge their mind with riddles and opportunities to buy valuable gear or potions from a dungeon merchant!

**Files to Create/Edit:**

* `main.cpp` (To handle what happens in Puzzle and Merchant rooms)

---

**Step 1: Handling Puzzle Rooms in `main.cpp`**

Puzzle rooms will test your player's wit. Solving them can yield rewards, while failure might have consequences. The `handlePuzzleRoom` function already exists in `room_handlers.hpp` and `room_handlers.cpp`.

**In `main.cpp`:**

1.  Open the file named `main.cpp`.
2.  Locate the `switch (currentRoom.type)` statement inside your `if (!currentRoom.visited)` block.
3.  **Add a new `case` for `PUZZLE` rooms.** Place it after your `case TRAP:` block:

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
        case TRAP: {
            // ... (existing TRAP case) ...
            break;
        }
        case PUZZLE: { // It's a Puzzle!
            typeText("🤔 You've entered a room with an ancient inscription. A riddle appears before you...");
            bool puzzleSolved = handlePuzzleRoom(currentRoom, player);

            if (puzzleSolved) {
                typeText("The riddle fades, and the room feels safe now.");
                currentRoom.type = EMPTY; // Puzzle solved, room becomes empty
            } else {
                typeText("The riddle remains, its mystery unsolved for now.");
                // Player remains in a puzzle room until solved, or they leave.
                // handlePuzzleRoom already deducts health for failure.
                // The room type does NOT change, allowing re-attempts or leaving.
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
        * `handlePuzzleRoom(currentRoom, player);`: This function (from `room_handlers.cpp`) will display the puzzle, get player input, check the answer, and award gold for success or deduct health for failure.
        * `if (puzzleSolved) { currentRoom.type = EMPTY; }`: If the player solves the puzzle, the room is marked as `EMPTY` to prevent re-solving it for rewards.
        * If the puzzle is *not* solved, the room type remains `PUZZLE`, allowing the player to try again later or move on.

---

**Step 2: Handling Merchant Rooms in `main.cpp`**

Merchant rooms provide a much-needed respite, allowing your hero to spend their hard-earned gold on useful items to improve their chances of survival. The `handleMerchantRoom` function already exists in `room_handlers.hpp` and `room_handlers.cpp`.

**In `main.cpp`:**

1.  Open the file named `main.cpp`.
2.  Locate the `switch (currentRoom.type)` statement inside your `if (!currentRoom.visited)` block.
3.  **Add a new `case` for `MERCHANT` rooms.** Place it after your `case PUZZLE:` block:

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
        case TRAP: {
            // ... (existing TRAP case) ...
            break;
        }
        case PUZZLE: {
            // ... (existing PUZZLE case) ...
            break;
        }
        case MERCHANT: { // A friendly Merchant!
            typeText("💰 A shadowy figure emerges from the corner. \"Welcome, adventurer! Care to browse my wares?\"");
            handleMerchantRoom(player); // Handles the entire shopping interaction

            // Merchant rooms typically do NOT become empty after visit,
            // as players might want to return to buy more items.
            // So, we do NOT change currentRoom.type here.
            break;
        }
        // ... the final EXIT room will go here later ...
        default:
            typeText("You've entered a strange room..."); // Fallback for types not yet handled
            break;
    }
    ```
    * **Explanation:**
        * `handleMerchantRoom(player);`: This function (from `room_handlers.cpp`) will display the merchant's inventory, handle buying items, and update the player's gold and stats/inventory.
        * **Important:** Unlike `TREASURE`, `POTION`, `TRAP`, and `SOLVED_PUZZLE` rooms, a `MERCHANT` room remains a `MERCHANT` room. This allows the player to revisit the merchant later if they accumulate more gold.

---

**Step 3: Compile and Test Your Brainpower and Bargaining Skills!**

Now, your dungeon will truly test all aspects of your hero!

1.  **Open your terminal or command prompt.**
2.  **Navigate to your project folder.**
3.  **Compile your code.** Make sure you're compiling all the `.cpp` files:
    ```bash
    g++ main.cpp utils.cpp display_functions.cpp room_generator.cpp room_handlers.cpp -o dungeon_game
    ```
    * If you encounter any compilation errors, carefully review the new `case PUZZLE` and `case MERCHANT` blocks in `main.cpp`.
4.  **Run your game!**
    ```bash
    ./dungeon_game
    ```
    * As you move, you should now encounter `[?]` symbols on your map for Puzzle rooms and `[$]` symbols for Merchant rooms.
    * Try solving a puzzle and see if you get gold or take damage. Revisit a puzzle room you failed to see if you can try again.
    * Visit a merchant, try buying an item (you might need to find treasure first!). See if your gold, strength, or defense updates, or if a health potion is added to your inventory.

Fantastic work! Your dungeon now offers both intellectual challenges and opportunities for strategic upgrades. In the next and final stage, we'll implement the ultimate goal: the `EXIT` room, allowing your hero to finally escape!