### Stage 6: Populating the Dungeon & Basic Room Interactions (Treasure and Empty Rooms)

This is where your dungeon truly comes alive! We'll modify the dungeon generation to fill it with different room types (starting with `TREASURE` rooms), and then implement the logic for what happens when your player walks into one.

**Files to Create/Edit:**

* `room_generator.cpp` (To change how the dungeon is populated)
* `main.cpp` (To handle what happens in each room type)
* `game_types.hpp` (To ensure `Room` struct has necessary properties for treasure)

---

**Step 1: Enabling Random Room Generation (`room_generator.cpp`)**

Currently, your `initializeDungeon` function fills the entire map with `EMPTY` rooms using `createEmptyRoom()`. However, the provided `room_generator.cpp` actually contains a powerful function called `generateRandomRoom()` which already knows how to pick a random room type for you! We'll use this.

**In `room_generator.cpp`:**

1.  Open the file named `room_generator.cpp`.
2.  Locate the `initializeDungeon()` function.
3.  Inside the nested `for` loops (where you loop `for (int y = 0; y < MAP_SIZE; y++)` and `for (int x = 0; x < MAP_SIZE; x++)`), find the line that currently says:
    ```cpp
    dungeon.rooms[y][x] = createEmptyRoom();
    ```
4.  **Change this line** to call `generateRandomRoom()` instead:
    ```cpp
    dungeon.rooms[y][x] = generateRandomRoom();
    ```
    * **Explanation:** The `generateRandomRoom()` function (which is already present in your `room_generator.cpp` file snippet) uses `rand() % 100` to randomly decide if a room will be a `MONSTER`, `TREASURE`, `POTION`, `PUZZLE`, `TRAP`, `MERCHANT`, `EMPTY`, or `EXIT` room based on certain probabilities. By making this small change, your dungeon will now be randomly populated with all these different types from the start!

---

**Step 2: Refining the `Room` Structure (`game_types.hpp`)**

To handle `TREASURE` rooms (and eventually others), our `Room` struct needs to hold specific data for each type. The `game_types.hpp` snippet you provided already contains these, but let's make sure you understand their purpose.

**In `game_types.hpp`:**

1.  Open the file named `game_types.hpp`.
2.  Locate your `struct Room` definition.
3.  Ensure it includes the following properties (they should already be there based on your snippet):
    ```cpp
    struct Room {
        RoomType type;
        std::string description;
        bool visited = false;
        MonsterLevel monsterLevel = EASY;    // For MONSTER rooms
        int goldAmount = 0;                  // For TREASURE rooms
        int healthAmount = 0;                // For POTION rooms
        std::string puzzleQuestion;          // For PUZZLE rooms
        std::string puzzleAnswer;            // For PUZZLE rooms
        int damageAmount = 0;                // For TRAP rooms
    };
    ```
    * **Explanation:** `generateRandomRoom()` and the specific room creation functions (like `createTreasureRoom()`) will fill these properties with meaningful values when they create a room. For example, `createTreasureRoom()` will set `room.type = TREASURE;` and `room.goldAmount = ...;`.

---

**Step 3: Handling Room Interactions in `main.cpp` (Treasure and Empty)**

Now that the dungeon is populated, we need to update your `main.cpp` to react differently based on the type of room the player enters.

**In `main.cpp`:**

1.  Open the file named `main.cpp`.
2.  Locate the `if (player.x != prevX || player.y != prevY)` block inside your `while (!gameOver)` loop. This is where you currently just print `typeText(dungeon.rooms[player.y][player.x].description);`.
3.  We're going to replace that simple `typeText` call with a `switch` statement that checks `dungeon.rooms[player.y][player.x].type`.
4.  Inside the `if (player.x != prevX || player.y != prevY)` block, *after* `dungeon.revealed[player.y][player.x] = true;`, add this `switch` statement:

    ```cpp
    // Get a reference to the current room for easier access
    Room& currentRoom = dungeon.rooms[player.y][player.x];

    // Check if the room has been visited before
    if (!currentRoom.visited) {
        // This is a new room! Handle its type.
        typeText(currentRoom.description); // Always print the room's primary description

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
            // We'll add other room types (MONSTER, POTION, etc.) in later stages
            default:
                typeText("You've entered a strange room..."); // Fallback for types not yet handled
                break;
        }
        currentRoom.visited = true; // Mark room as visited AFTER handling its event
    } else {
        // Player has been here before
        typeText("🔄 You've been here before. The room is now empty.");
    }
    ```
    * **Explanation:**
        * `Room& currentRoom = dungeon.rooms[player.y][player.x];` creates a shortcut (`currentRoom`) to the room your player just entered. The `&` means it's a "reference", so any changes to `currentRoom` will actually change the room in your `dungeon.rooms` array.
        * `if (!currentRoom.visited)`: This checks if the room is new. We only trigger events (like finding treasure) the *first* time a player enters a room.
        * `typeText(currentRoom.description);`: This line is important, as every room has a basic description.
        * `case TREASURE:`: When the room is a `TREASURE` type:
            * We use `std::to_string` to convert the `int goldAmount` to text so we can print it.
            * `player.gold += currentRoom.goldAmount;` adds the gold to the player's total.
            * `currentRoom.goldAmount = 0;` and `currentRoom.type = EMPTY;` are crucial: they make sure the player can't keep getting gold from the same room and effectively convert the treasure room into an empty room once looted.
        * `case EMPTY:`: This case is simple, just prints the description.
        * `default:`: This is a safety net for any room types we haven't implemented yet.
        * `currentRoom.visited = true;`: Always mark the room as `visited` *after* its event has occurred for the first time.
    * **Important:** You also need to `#include <string>` at the top of `main.cpp` for `std::to_string`.

---

**Step 4: Compile and Test Your Looting Skills!**

Now, your dungeon will contain treasure, and your hero can find it!

1.  **Open your terminal or command prompt.**
2.  **Navigate to your project folder.**
3.  **Compile your code.** Make sure you're compiling all the `.cpp` files:
    ```bash
    g++ main.cpp utils.cpp display_functions.cpp room_generator.cpp -o dungeon_game
    ```
    * If you encounter any compilation errors, carefully review the code you've added for typos, missing semicolons, or incorrect includes. Pay close attention to the `switch` statement in `main.cpp`.
4.  **Run your game!**
    ```bash
    ./dungeon_game
    ```
    * As you move, you should now see `[T]` symbols on your map for Treasure rooms.
    * When you move into a `[T]` room, you should see a message about finding gold, and your `Gold` stat in the status display should increase!
    * If you move out of a treasure room and then back into it, it should now appear as `[ ]` on the map (because its type changed to `EMPTY`), and you'll get the "You've been here before..." message, without getting more gold.

Fantastic work! Your dungeon now feels more alive, and your hero has a reason to explore: treasure! In the next stage, we'll introduce the thrill of combat by implementing `MONSTER` rooms.