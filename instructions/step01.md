# Stage 1: Basic Setup and Welcome

Alright, adventurer! Let's embark on this epic quest to build your Dungeon Crawl game, one exciting step at a time. We'll start with the very basics, like saying hello and letting your game take a breath, and then slowly add more magic!

### Stage 1: The Grand Welcome and Basic Tools

Every great journey begins with a first step, and for our game, that step is setting up a simple welcome message and some handy tools to make our text look cool and keep the screen tidy.

**Files to Create/Edit:**

* `main.cpp` (This will be the heart of our game)
* `utils.hpp` (Our toolbox blueprint)
* `utils.cpp` (Our toolbox itself!)

---

**Step 1: Setting up Your Toolbox (`utils.hpp` and `utils.cpp`)**

Imagine you have a toolbox. `utils.hpp` is like the label on the outside of the box, telling you what tools are inside. `utils.cpp` is where you actually build and put the tools!

**In `utils.hpp`:**

1.  Open the file named `utils.hpp`.
2.  At the very top, you'll see `#ifndef UTILS_HPP` and `#define UTILS_HPP`. These lines are like a special guard to make sure our tools don't get mixed up if we use them in different parts of our game. Keep them there!
3.  Below those lines, you'll need to tell the compiler that you'll be using `std::string` (for text messages). So, add:
    ```cpp
    #include <string>
    ```
4.  Now, let's declare our first tool, a function called `typeText`. This function will make our messages appear as if they're being typed, letter by letter, which is super cool for a text-based game!
    * Write down:
        ```cpp
        void typeText(const std::string& text, int speed = 20);
        ```
        * `void` means this function doesn't give back any specific value.
        * `typeText` is its name.
        * `const std::string& text` means it takes a message (a `string`) as input, and `const&` means it won't change the message, just use it.
        * `int speed = 20` means you can tell it how fast to "type" the message, and if you don't say, it will use a default speed of 20 milliseconds per letter.
5.  Next, declare a tool to clear the screen, so our game doesn't get cluttered:
    * Write down:
        ```cpp
        void clearScreen();
        ```
        * Again, `void` means it doesn't return anything. It just does its job.
6.  Finally, declare a tool to pause the game until the player is ready to continue:
    * Write down:
        ```cpp
        void waitForKey();
        ```
7.  At the very bottom, you'll see `#endif // UTILS_HPP`. This is the other half of our special guard.

**In `utils.cpp`:**

1.  Open the file named `utils.cpp`.
2.  At the top, you need to include the `utils.hpp` file itself, because this is where we're actually *building* the tools we declared in the header. You'll also need some other standard library headers for input/output, time, and limits.
    ```cpp
    #include "utils.hpp"
    #include <iostream>    // For input and output (like std::cout, std::cin)
    #include <thread>      // For pausing the program
    #include <chrono>      // For working with time durations
    #include <limits>      // For std::numeric_limits
    ```
3.  Now, let's build the `typeText` function!
    * Start by defining the function as you declared it:
        ```cpp
        void typeText(const std::string& text, int speed) {
            // ... put the code here ...
        }
        ```
    * Inside the curly braces `{}`:
        * You'll want to loop through each character of the `text` string. A `for` loop that uses a "range-based for loop" is perfect for this! It looks like this: `for (char c : text)`.
        * Inside this loop, you'll print each character (`c`) to the console. You'll also use `std::flush` to make sure the character appears right away, not just when the line is finished.
            * `std::cout << c << std::flush;`
        * After printing, you want to pause for a tiny moment to create the typing effect. You'll use `std::this_thread::sleep_for` with `std::chrono::milliseconds(speed)`.
            * `std::this_thread::sleep_for(std::chrono::milliseconds(speed));`
        * After the loop finishes (meaning all characters have been typed), you'll print a new line so the next text starts on a fresh line.
            * `std::cout << std::endl;`
4.  Next, let's build the `clearScreen` function:
    * Start by defining the function:
        ```cpp
        void clearScreen() {
            // ... put the code here ...
        }
        ```
    * Inside the curly braces `{}`:
        * Computers use different commands to clear the screen! We need to make sure our game works on different systems (like Windows or macOS/Linux). We can use a special `if` statement called a "preprocessor directive" for this.
        * If the system is Windows, it uses `system("cls");`.
        * Otherwise (for other systems), it uses `system("clear");`.
            ```cpp
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            ```
5.  Finally, let's build the `waitForKey` function:
    * Start by defining the function:
        ```cpp
        void waitForKey() {
            // ... put the code here ...
        }
        ```
    * Inside the curly braces `{}`:
        * First, print a friendly message to the player, like `"Press Enter to continue..."`.
            * `std::cout << "\nPress Enter to continue...";`
        * Then, we need to clear out any old keyboard presses that might be waiting in the computer's memory. This is a little tricky, but just copy this line for now:
            * `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');`
        * Finally, wait for the player to press the Enter key:
            * `std::cin.get();`

---

**Step 2: The Main Story Begins (`main.cpp`)**

`main.cpp` is where your game actually starts and runs. Think of it as the director of a play, telling everyone when to do their part.

**In `main.cpp`:**

1.  Open the file named `main.cpp`.
2.  At the very top, you'll need to include the `utils.hpp` file, because we're going to use the `typeText`, `clearScreen`, and `waitForKey` tools here. You also need `iostream` for general input/output.
    ```cpp
    #include "utils.hpp" // Our special tools!
    #include <iostream>  // For basic input/output
    ```
3.  Find the `main` function. This is where your program always begins.
    ```cpp
    int main() {
        // Start here...
        return 0; // Tells the computer the program finished successfully
    }
    ```
4.  Inside the `main` function, let's add our welcome message!
    * First, use `clearScreen()` to make sure the console is clean before we start.
    * Then, use `typeText` to print a welcome message. Make it fun! You can even change the `speed` parameter if you want to.
        * `clearScreen();`
        * `typeText("Welcome to the Dungeon Crawl!", 30);`
        * `typeText("Prepare for an epic adventure!", 25);`
    * After your welcome, add `waitForKey()` so the player can read the message before it disappears.
        * `waitForKey();`
    * Finally, add a goodbye message just to show that the game ran through.
        * `clearScreen();`
        * `typeText("Thanks for playing! See you next time!", 20);`
        * `waitForKey();`

---

**Step 3: Test Your First Steps!**

This is the moment of truth! Let's compile and run your game to see if your welcome message appears correctly.

1.  **Open your terminal or command prompt.**
2.  **Navigate to the folder** where you saved all your `.cpp` and `.hpp` files.
3.  **Compile your code.** This turns your human-readable C++ code into a computer-executable program. You'll need a C++ compiler installed (like g++). Type this command:
    ```bash
    g++ main.cpp utils.cpp -o dungeon_game
    ```
    * `g++` is the compiler command.
    * `main.cpp utils.cpp` tells the compiler which `.cpp` files to build.
    * `-o dungeon_game` tells the compiler to create an executable file named `dungeon_game`.
4.  **If there are no errors**, you'll see a new file named `dungeon_game` in your folder.
5.  **Run your game!** Type this command:
    ```bash
    ./dungeon_game
    ```
    * You should see your welcome message slowly typing out, then a prompt to press Enter, then a goodbye message, and another prompt to press Enter.
    * If you see "command not found" or "no such file or directory", double-check that you're in the correct folder and that g++ is installed. If you get compilation errors, carefully re-read the steps and compare what you typed.

Fantastic! You've just created the very first interactive part of your game! Give yourself a pat on the back. Next, we'll start defining the actual elements of our dungeon, like the player and the rooms!