### Stage 5: The First Steps - Player Movement

Now that our hero can see the dungeon, it's time to let them explore! In this stage, you'll implement the core movement system, allowing your player to navigate the map using keyboard commands.

**Files to Create/Edit:**

* `main.cpp` (This is where your main game loop and input handling live)

---

**Step 1: Adding Movement Logic to `main.cpp`**

This is where the game truly becomes interactive! We'll add code inside your `playGame()` function's `while` loop to capture player input and update their position.

**In `main.cpp`:**

1.  Open the file named `main.cpp`.
2.  Locate the `while (!gameOver)` loop inside your `playGame()` function.
3.  Inside the loop, after `displayStatus(player);` and before `waitForKey();`, you need to:
    * **Prompt for input:** Tell the player what keys to press for movement and to quit.
        ```cpp
        std::cout << "\n➡️ Where will you go? (W:North, S:South, A:West, D:East, Q:Quit)\n";
        std::cout << "Your choice: ";
        ```
    * **Get player input:** Read a single character from the keyboard.
        ```cpp
        char input;
        std::cin >> input;
        
        // Convert input to uppercase to handle both 'w' and 'W', etc.
        input = toupper(input);
        
        // Handle any leftover characters in the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Clear any error flags on std::cin (important after bad input)
        std::cin.clear();
        ```
        * You'll need to `#include <cctype>` at the top of `main.cpp` for `toupper()`.
        * You already have `std::numeric_limits` from a previous stage if you used it in `waitForKey()`.
    * **Store old position:** Before trying to move, save the player's current `x` and `y` coordinates. This is useful if the move is invalid (e.g., off the map).
        ```cpp
        int prevX = player.x;
        int prevY = player.y;
        ```
    * **Process input using a `switch` statement:** This is a clean way to handle multiple possible inputs.
        ```cpp
        switch (input) {
            case 'W': // Move North (Up)
                if (player.y > 0) { // Check if not at the top edge
                    player.y--; // Decrease y-coordinate (moving up)
                    typeText("You move north.");
                } else {
                    typeText("You can't go that way! A solid rock wall blocks your path.");
                }
                break; // Very important to break out of the switch!
            case 'S': // Move South (Down)
                if (player.y < MAP_SIZE - 1) { // Check if not at the bottom edge
                    player.y++; // Increase y-coordinate (moving down)
                    typeText("You move south.");
                } else {
                    typeText("You can't go that way! There's no path forward.");
                }
                break;
            case 'A': // Move West (Left)
                if (player.x > 0) { // Check if not at the left edge
                    player.x--; // Decrease x-coordinate (moving left)
                    typeText("You move west.");
                } else {
                    typeText("You can't go that way! The passage ends abruptly.");
                }
                break;
            case 'D': // Move East (Right)
                if (player.x < MAP_SIZE - 1) { // Check if not at the right edge
                    player.x++; // Increase x-coordinate (moving right)
                    typeText("You move east.");
                } else {
                    typeText("You can't go that way! A thick, mossy barrier blocks your way.");
                }
                break;
            case 'Q': // Quit the game
                typeText("Are you sure you want to quit? (Y/N)");
                char confirm_quit;
                std::cin >> confirm_quit;
                confirm_quit = toupper(confirm_quit);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.clear();
                if (confirm_quit == 'Y') {
                    gameOver = true; // Set gameOver to true to exit the loop
                    typeText("You decide to abandon your quest. Until next time, adventurer!");
                } else {
                    typeText("You reconsider and continue your adventure!");
                }
                break;
            default: // Handle invalid input
                typeText("Invalid command. Please use W, S, A, D to move, or Q to quit.");
                break;
        }
        ```
    * **Update room status after a successful move:** If the player actually moved (i.e., `player.x` and `player.y` are different from `prevX` and `prevY`), mark the *new* room as `revealed` and print its description.
        ```cpp
        if (player.x != prevX || player.y != prevY) {
            dungeon.revealed[player.y][player.x] = true; // Reveal the room they moved into
            // For now, all rooms are EMPTY, so we'll just print its description.
            // In later stages, we'll use a switch statement here based on room.type
            // to handle different room events.
            typeText(dungeon.rooms[player.y][player.x].description);
            dungeon.rooms[player.y][player.x].visited = true; // Mark as visited
        }
        ```
    * Keep the `waitForKey();` at the end of the `while` loop.

---

**Step 2: Compile and Test Your Movement!**

It's time to see your hero walk!

1.  **Open your terminal or command prompt.**
2.  **Navigate to your project folder.**
3.  **Compile your code.** Make sure you're compiling all the `.cpp` files:
    ```bash
    g++ main.cpp utils.cpp display_functions.cpp room_generator.cpp -o dungeon_game
    ```
    * If you encounter any compilation errors, carefully review the code you've added for typos, missing semicolons, or incorrect includes (especially `cctype`).
4.  **Run your game!**
    ```bash
    ./dungeon_game
    ```
    * You should now be able to use 'W', 'A', 'S', 'D' to move your player `[P]` around the map! Try moving to the edges to see the "You can't go that way!" messages.
    * Try pressing 'Q' to quit and confirm.

Congratulations, you've taken a giant leap! Your hero can now explore the empty dungeon. In the next stage, we'll start populating this dungeon with different kinds of rooms, like treasure rooms, and make them interactive!