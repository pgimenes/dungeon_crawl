### Stage 3: Bringing Your Hero to Life - Displaying Player Status

Now that we have the blueprints for our `Player` (and other game elements) in `game_types.hpp`, it's time to make our hero visible! In this stage, we'll create a new set of files specifically for showing information to the player. We'll start by displaying your adventurer's health, gold, and other stats.

**Files to Create/Edit:**

* `display_functions.hpp` (Our display tools blueprint)
* `display_functions.cpp` (Our display tools themselves!)
* `main.cpp` (To use our new display tool)

---

**Step 1: Setting Up Your Display Toolbox (`display_functions.hpp` and `display_functions.cpp`)**

Just like our `utils` files, we'll have a blueprint (`.hpp`) and the actual tool implementation (`.cpp`) for displaying things.

**In `display_functions.hpp`:**

1.  Open the file named `display_functions.hpp`.
2.  Add the standard guard lines at the top and bottom:
    ```cpp
    #ifndef DISPLAY_FUNCTIONS_HPP
    #define DISPLAY_FUNCTIONS_HPP

    // ... your declarations will go here ...

    #endif // DISPLAY_FUNCTIONS_HPP
    ```
3.  Since our display functions will need to know what a `Player` is, we must include `game_types.hpp`:
    ```cpp
    #include "game_types.hpp"
    ```
4.  Now, declare our first display tool, a function called `displayStatus`. This function will show the player's health, gold, strength, and defense.
    * Write down:
        ```cpp
        void displayStatus(const Player& player);
        ```
        * `void` means it doesn't give back any specific value.
        * `displayStatus` is its name.
        * `const Player& player` means it takes a `Player` object as input, and `const&` means it won't change the player's data, just read it to display.
    * *(Important Note: We will also have a `displayMap` function later, but for now, we're keeping it simple and focusing only on the player's status.)*

**In `display_functions.cpp`:**

1.  Open the file named `display_functions.cpp`.
2.  At the top, include `display_functions.hpp` (because we're defining the functions declared there) and `iostream` (for `std::cout` to print things). You'll also need `string` for `std::to_string` to convert numbers into text.
    ```cpp
    #include "display_functions.hpp"
    #include <iostream>
    #include <string> // For std::to_string
    ```
3.  Now, let's build the `displayStatus` function!
    * Start by defining the function as you declared it:
        ```cpp
        void displayStatus(const Player& player) {
            // ... put the code here ...
        }
        ```
    * Inside the curly braces `{}`:
        * First, let's print a decorative border or title for our status display. This makes it look neat! You can use characters like `═` or `─` and `║` if your terminal supports them, or just use `=` and `|` for simplicity.
            * `std::cout << "\n╔════════════════════════════╗\n";`
        * Now, print each of the player's stats on separate lines. For example, for health:
            * `std::cout << "║ ❤️  HP: " << player.health << "/" << MAX_HEALTH << " ";`
            * Remember `player.health` comes from the `player` object we passed in, and `MAX_HEALTH` comes from `game_types.hpp`.
            * You can even add a little " (DANGER!)" message if the player's health drops low!
                ```cpp
                if (player.health < 30) {
                    std::cout << "(DANGER!)";
                }
                ```
            * You might also want to add spaces to make sure everything lines up nicely, no matter how many digits the numbers have. This often involves a `for` loop to print spaces.
                ```cpp
                // Example for health: Adjust the 12 based on the maximum length of your health string
                for (int i = 0; i < 12 - std::to_string(player.health).length() - std::to_string(MAX_HEALTH).length(); i++) {
                    std::cout << " ";
                }
                std::cout << "║\n";
                ```
            * Repeat this pattern for `Gold`, `Strength`, and `Defense`, using `player.gold`, `player.strength`, and `player.defense`.
            * Remember to use `std::to_string()` when you want to print an integer as part of a `std::cout` string that has other text.
                * `std::cout << "║ 💰 Gold: " << player.gold << "/" << GOLD_TO_ESCAPE;`
        * Finally, close off the status display with another decorative border:
            * `std::cout << "╚════════════════════════════╝\n";`

---

**Step 2: Using Our New Display Tool (`main.cpp`)**

Now, let's make our `main` function actually use the `displayStatus` function and show our hero's stats!

**In `main.cpp`:**

1.  Open the file named `main.cpp`.
2.  At the top, you need to include `game_types.hpp` (because we'll be creating a `Player` object) and `display_functions.hpp` (because we'll be calling `displayStatus`).
    ```cpp
    #include "game_types.hpp"          // For Player, MAX_HEALTH, etc.
    #include "display_functions.hpp"   // For displayStatus
    // ... keep #include "utils.hpp" and <iostream> ...
    ```
3.  Let's create a new function `playGame()` to keep our `main` function tidy. This function will hold the main game loop logic.
    * Below your existing includes and above `int main()`, define `void playGame() { ... }`.
    * Move your welcome message and `waitForKey()` calls from `main()` into the `playGame()` function.
    * Inside `playGame()`, after the welcome message and `waitForKey()`:
        * Create a `Player` object. This will automatically set its `health`, `gold`, `etc.` to the starting values you defined in `game_types.hpp`.
            * `Player player;`
        * Now, call your `displayStatus` function, passing in your `player` object.
            * `displayStatus(player);`
        * Add another `waitForKey()` so you can admire your player's stats!
            * `waitForKey();`
    * In your `int main()` function, all you need to do is call `playGame();`
        ```cpp
        int main() {
            playGame(); // Start the game!
            return 0;
        }
        ```
    * *(Optional: To see your stats change, you could temporarily set `player.health = 25;` before calling `displayStatus` to see the "DANGER!" message. Remember to change it back!)*

---

**Step 3: Compile and Test Your Hero's Debut!**

It's time to see your hero's status proudly displayed!

1.  **Open your terminal or command prompt.**
2.  **Navigate to your project folder.**
3.  **Compile your code.** Now you have three `.cpp` files to compile:
    ```bash
    g++ main.cpp utils.cpp display_functions.cpp -o dungeon_game
    ```
    * If there are no errors, you're doing great! Check for any typos if you get errors.
4.  **Run your game!**
    ```bash
    ./dungeon_game
    ```
    * You should now see your welcome message, then your player's status displayed with their starting health, gold, strength, and defense!

Fantastic! You've given your hero a presence in the game. In the next stage, we'll start building the actual dungeon map and display it to the player, letting them see their location in the world!