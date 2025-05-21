### Stage 10: The Grand Escape - The Exit Room and Winning the Game

This is it, adventurer! The final challenge: finding the `EXIT` and escaping the dungeon with enough gold to secure your freedom. This stage will implement the win condition and conclude the main gameplay loop.

**Files to Create/Edit:**

* `main.cpp` (To handle the `EXIT` room logic)

---

**Step 1: Handling the Exit Room in `main.cpp`**

The `EXIT` room is the ultimate goal. When the player enters it, you'll check if they have enough gold to escape.

**In `main.cpp`:**

1.  Open the file named `main.cpp`.
2.  Locate the `switch (currentRoom.type)` statement inside your `if (!currentRoom.visited)` block.
3.  **Add a new `case` for `EXIT` rooms.** This will be the final `case` in your `switch` statement:

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
        case MERCHANT: {
            // ... (existing MERCHANT case) ...
            break;
        }
        case EXIT: { // The Grand Escape!
            typeText("🚪 You've found the grand exit of the dungeon! A massive, ornate door stands before you.");
            if (player.gold >= GOLD_TO_ESCAPE) {
                typeText("You deposit your " + std::to_string(GOLD_TO_ESCAPE) + " gold into the door's mechanism...");
                typeText("With a thunderous rumble, the door swings open, revealing daylight beyond!");
                player.gold -= GOLD_TO_ESCAPE; // Deduct gold
                typeText("\n🎉 CONGRATULATIONS! You've escaped the dungeon with " + std::to_string(player.gold) + " extra gold!");
                gameOver = true; // Set game over to true - player wins!
            } else {
                typeText("\n🚪 The exit is sealed with a magical lock. An inscription reads:");
                typeText("\"Only those who offer " + std::to_string(GOLD_TO_ESCAPE) + " gold may pass.\"");
                typeText("You need " + std::to_string(GOLD_TO_ESCAPE - player.gold) + " more gold to escape!");
                // The room type does NOT change, allowing the player to return
                // after getting more gold.
            }
            break;
        }
        default:
            typeText("You've entered a strange room..."); // Fallback for types not yet handled
            break;
    }
    ```
    * **Explanation:**
        * `if (player.gold >= GOLD_TO_ESCAPE)`: This is the core win condition. It checks if the player has accumulated enough gold (defined in `game_types.hpp`).
        * If the condition is met, a success message is displayed, the required gold is deducted, and `gameOver` is set to `true`, ending the game loop.
        * If the player doesn't have enough gold, a message informs them how much more they need. The room type remains `EXIT`, allowing them to leave and return when they have enough gold.

---

**Step 2: Compile and Test Your Grand Escape!**

This is the moment of truth! Can your hero escape the dungeon?

1.  **Open your terminal or command prompt.**
2.  **Navigate to your project folder.**
3.  **Compile your code.** Make sure you're compiling all the `.cpp` files:
    ```bash
    g++ main.cpp utils.cpp display_functions.cpp room_generator.cpp room_handlers.cpp -o dungeon_game
    ```
    * If you encounter any compilation errors, carefully review the new `case EXIT` block in `main.cpp`.
4.  **Run your game!**
    ```bash
    ./dungeon_game
    ```
    * Explore the dungeon, find `[E]` on your map.
    * Try entering the `[E]` room with less than `GOLD_TO_ESCAPE` gold. See the message telling you how much more you need.
    * Now, play through, collect enough gold from `TREASURE` rooms, `MONSTER` fights, and `PUZZLE` solutions.
    * Once you have `GOLD_TO_ESCAPE` or more, go back to the `[E]` room and successfully escape!

---

**Congratulations, Adventurer!**

You have successfully implemented all the core features of your Dungeon Crawl game! Your hero can now explore, fight, find treasure, heal, avoid traps, solve puzzles, trade with merchants, and, most importantly, escape the dungeon to win the game!

This completes the guided incremental development of your game. You now have a fully functional text-based dungeon crawler!

**Final Polish (Optional Next Steps on Your Own):**

If you wish to further enhance your game, here are some ideas for future expansion:

* **Inventory Usage:** Implement a menu (perhaps activated by a key, e.g., 'I' for Inventory) where the player can see their collected `ItemType`s and choose to `USE` a `HEALTH_POTION` to heal.
* **More Item Types:** Add different types of items (e.g., permanent stat boosters, keys).
* **Save/Load Game:** Allow players to save their progress and load it later.
* **Advanced Combat:** Introduce critical hits, monster abilities, player special moves.
* **Story/NPCs:** Add more narrative elements, quests, or non-player characters beyond the merchant.
* **Equipment System:** Allow players to equip different weapons and armor found or bought, which dynamically change their strength and defense.

You've built a solid foundation. Go forth and continue to expand your game!