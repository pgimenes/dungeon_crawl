### Stage 2: The Game's Blueprint - Defining Our World and Hero

Now that our game can say hello and keep the screen clean, it's time to give it some substance! In this stage, we're going to create the fundamental building blocks of our game: what our player looks like, what kinds of rooms are in our dungeon, and how big our map is. Think of this as drawing the blueprints for our game world.

**Files to Create/Edit:**

* `game_types.hpp` (This is where all our game's special "words" and "blueprints" will live)

---

**Step 1: Setting Up Your Game's Dictionary (`game_types.hpp`)**

`game_types.hpp` is going to be your game's dictionary. It's where you'll define all the custom "words" and "shapes" that describe things in your game, like a `Player` or a `Room`.

**In `game_types.hpp`:**

1.  Open the file named `game_types.hpp`.
2.  Just like `utils.hpp`, you'll see the special guard lines at the top: `#ifndef GAME_TYPES_HPP` and `#define GAME_TYPES_HPP`. Keep them there!
3.  Below those lines, you'll need to include the standard library headers for `std::string` (for text) and `std::vector` (for lists of things, like inventory or rows of rooms).
    ```cpp
    #include <string>
    #include <vector>
    ```
4.  **Define Game Constants:**
    These are like the unchangeable rules of your game! We use `const int` because these numbers won't ever change while the game is running.
    * `MAP_SIZE`: This will determine how big our dungeon map is. We'll make it a square, so a value of `5` means a 5x5 map.
        ```cpp
        const int MAP_SIZE = 5;
        ```
    * `MAX_HEALTH`: This is the maximum health your brave adventurer can have. Let's set it to `100`.
        ```cpp
        const int MAX_HEALTH = 100;
        ```
    * `GOLD_TO_ESCAPE`: This is the target amount of gold your player needs to collect to win the game! Make it `150`.
        ```cpp
        const int GOLD_TO_ESCAPE = 150;
        ```
    * *(Self-correction: The original code had `NUM_ROOMS = 10;`. We don't really use this directly for map generation in the final game, as the map size is based on `MAP_SIZE`. You can omit it for now to keep things simpler, or include it as a placeholder if you prefer for consistency with the initial overview.)*
        ```cpp
        // const int NUM_ROOMS = 10; // You can omit this for now, or keep it if you like
        ```
5.  **Define Room Types (`enum RoomType`):**
    Imagine you have a list of categories for things. An `enum` (short for enumeration) is perfect for this! We'll list all the different kinds of rooms your dungeon can have.
    * Write down the `enum` definition like this:
        ```cpp
        enum RoomType { MONSTER, TREASURE, POTION, PUZZLE, TRAP, MERCHANT, EMPTY, EXIT };
        ```
        * Each word here (like `MONSTER` or `TREASURE`) is a special "name" for a type of room.

6.  **Define Monster Levels (`enum MonsterLevel`):**
    Monsters aren't all the same strength! This `enum` will help us categorize them.
    * Write down:
        ```cpp
        enum MonsterLevel { EASY, MEDIUM, HARD };
        ```

7.  **Define Item Types (`enum ItemType`):**
    Your player will find and use different items. This `enum` lists them.
    * Write down:
        ```cpp
        enum ItemType { HEALTH_POTION, STRENGTH_POTION, SHIELD };
        ```

8.  **Create Your Player's Blueprint (`struct Player`):**
    A `struct` (short for structure) is like a blueprint for creating custom objects. Our `Player` struct will define everything that describes your hero!
    * Start the `struct` definition:
        ```cpp
        struct Player {
            // ... properties go here ...
        };
        ```
    * Inside the curly braces `{}` of the `Player` struct, list these properties with their starting values:
        * `health`: An integer starting at `MAX_HEALTH`. (This uses the constant we just defined!)
            * `int health = MAX_HEALTH;`
        * `gold`: An integer starting at `0`.
            * `int gold = 0;`
        * `strength`: An integer starting at `10`. This will make your player's attacks stronger.
            * `int strength = 10;`
        * `defense`: An integer starting at `5`. This will help your player take less damage.
            * `int defense = 5;`
        * `inventory`: A `std::vector` (a dynamic list) that will hold `ItemType` items. It starts empty.
            * `std::vector<ItemType> inventory;`
        * `x` and `y`: Integers that represent your player's current position on the map. We'll start them in the middle of our `MAP_SIZE` dungeon.
            * `int x = MAP_SIZE / 2;`
            * `int y = MAP_SIZE / 2;`

9.  **Design Your Room's Blueprint (`struct Room`):**
    Now, let's create a blueprint for each individual room in our dungeon.
    * Start the `struct` definition:
        ```cpp
        struct Room {
            // ... properties go here ...
        };
        ```
    * Inside the curly braces `{}` of the `Room` struct, list these properties with their starting values (if any):
        * `type`: This will be a `RoomType` (like `MONSTER` or `TREASURE`), telling us what kind of room it is.
            * `RoomType type;`
        * `description`: A `std::string` that will hold a short text describing the room (e.g., "A dusty, empty corridor.").
            * `std::string description;`
        * `visited`: A `bool` (true or false) that starts as `false`. This helps us remember if the player has been in this room before.
            * `bool visited = false;`
        * *(Self-correction: The original code has many more properties for `Room` like `monsterLevel`, `goldAmount`, etc. For incremental learning, we should *only* include the properties that are absolutely necessary for the current stage. We will add more properties to `Room` as we introduce more complex room types later.)*
        * For now, we'll keep the `Room` struct simple with just `type`, `description`, and `visited`. We'll add more details as we build out more complex room interactions in later stages.

10. **Build Your Dungeon Map's Blueprint (`struct DungeonMap`):**
    Finally, we need a blueprint for the entire dungeon map itself! This will hold all the individual `Room` objects in a grid.
    * Start the `struct` definition:
        ```cpp
        struct DungeonMap {
            // ... properties go here ...
        };
        ```
    * Inside the curly braces `{}` of the `DungeonMap` struct, list these properties:
        * `rooms`: This will be a `std::vector` of `std::vector<Room>`, creating a 2D grid to hold all our `Room` objects.
            * `std::vector<std::vector<Room>> rooms;`
        * `revealed`: This will be a 2D array of `bool` values (we'll declare it as `bool revealed[MAP_SIZE][MAP_SIZE];` in `main.cpp` when we create a `DungeonMap` object, but here we just declare the structure that holds it). This helps us know which parts of the map the player has explored and which are still hidden.
            * `bool revealed[MAP_SIZE][MAP_SIZE];`

11. At the very bottom, you'll see `#endif // GAME_TYPES_HPP`.

---

**Step 2: What's Next for `main.cpp`?**

For this stage, we're not changing `main.cpp` yet. The purpose of this stage is just to set up the definitions of our game's data. In the next stage, we'll use these new definitions to actually create a `Player` and start displaying some basic information about them!

---

**Step 3: Compile and Test (No Visible Changes Yet)**

Since we've only defined blueprints and not actually *used* them in `main.cpp` yet, running your game will show the exact same welcome and goodbye messages as before. This is normal!

1.  **Open your terminal or command prompt.**
2.  **Navigate to your project folder.**
3.  **Compile your code.** You'll use the same command as before:
    ```bash
    g++ main.cpp utils.cpp -o dungeon_game
    ```
    * Make sure there are no errors. If you see any, carefully check your `game_types.hpp` file for typos or missing semicolons.
4.  **Run your game!**
    ```bash
    ./dungeon_game
    ```

Great job! You've successfully laid down the foundational data structures for your dungeon and adventurer. This might seem like a small step, but it's crucial for building a complex game. In the next stage, we'll bring our player to life and start displaying their stats!