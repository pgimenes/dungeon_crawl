
# 🏰 Dungeon Crawl: A C++ Adventure! ⚔️

<div align="center">
  <img src="image.png" alt="A dark and mysterious dungeon scene, pixel art style" width="35%">
</div>

Welcome, brave adventurer! Prepare to descend into a text-based realm of danger, mystery, and shiny gold. This project is a fully functional dungeon crawler built entirely in C++, crafted through a step-by-step guided journey. You'll navigate a perilous map, battle fearsome monsters, solve ancient riddles, discover hidden treasures, and even haggle with a shady merchant, all while striving to escape with enough gold to buy your freedom!

## 🚀 How to Play

1.  **Compile the Game:**
    ```bash
    g++ main.cpp utils.cpp display_functions.cpp room_generator.cpp room_handlers.cpp -o dungeon_game
    ```
2.  **Run the Game:**
    ```bash
    ./dungeon_game
    ```
3.  **Navigate:** Use `W` (North), `S` (South), `A` (West), `D` (East) to move.
4.  **Interact:** Press `I` to access your inventory and `Q` to quit.
5.  **Escape!** Find the `[E]`xit room and gather `150` gold to buy your freedom!

## 🗺️ The Journey: Stage by Stage

This dungeon wasn't built in a day! Here's a quick peek at the epic construction process:

### Stage 1: The Grand Opening! 🚪
* **What you'll cook up:** Basic C++ setup, essential utility functions (`typeText` for dramatic flair, `clearScreen` for cleanliness, `waitForKey` for suspense!), and a warm welcome message.
* **Achieved:** A blinking cursor and a friendly "Hello, Adventurer!" – every epic journey starts somewhere!

### Stage 2: Blueprints & Heroes! 👤
* **What you'll cook up:** Defined the very essence of our game world! `Player` stats, `RoomType`s (monsters, treasure, puzzles!), `ItemType`s, and the grand `DungeonMap` structure.
* **Achieved:** Our hero now has a name (figuratively!) and the dungeon has a theoretical shape.

### Stage 3: Hero on Display! ✨
* **What you'll cook up:** Created `displayStatus` to show our hero's vital signs (HP, Gold, etc.).
* **Achieved:** No more guessing! We can see our adventurer's current state, always a good idea before facing a grumpy goblin.

### Stage 4: Unveiling the Void! 🌌
* **What you'll cook up:** `initializeDungeon` to generate an empty 5x5 grid and `displayMap` to show it. Player starts in the center, marked with `[P]`.
* **Achieved:** A vast, empty, terrifying (for now!) map. Like a canvas waiting for chaos!

### Stage 5: First Steps! 🚶
* **What you'll cook up:** Implemented player movement (`W`, `A`, `S`, `D`), boundary checks, and `revealed` rooms.
* **Achieved:** Our hero can finally wobble around the map! The world is now their oyster (or rather, their dungeon).

### Stage 6: Loot & Behold! 💰
* **What you'll cook up:** `initializeDungeon` now uses `generateRandomRoom` to populate the map with *actual* `TREASURE` and `MONSTER` rooms! We added logic to collect gold from `TREASURE` rooms.
* **Achieved:** Gold! Our dungeon now has shiny things to find, and the map shows `[T]` for treasure. It's no longer just empty squares!

### Stage 7: Let the Battles Begin! ⚔️
* **What you'll cook up:** Integrated `handleMonsterRoom` to bring combat to life. Players can now fight, take damage, and gain gold from defeated foes. Death is a real possibility!
* **Achieved:** The dungeon just got dangerous! `[M]` on the map means a fight, and our hero's health bar gets a workout.

### Stage 8: Health & Hazards! ❤️💥
* **What you'll cook up:** Added `POTION` rooms (heal up!) and `TRAP` rooms (ouch!). Logic to handle health restoration and damage from these new encounters.
* **Achieved:** More strategic decisions! Do you risk the `[!]]` for a potential shortcut, or seek out an `[H]` to patch yourself up?

### Stage 9: Brains & Bucks! 🧠💲
* **What you'll cook up:** Implemented `PUZZLE` rooms (solve riddles for rewards, or face consequences!) and `MERCHANT` rooms (buy health potions, strength, or defense upgrades!).
* **Achieved:** The dungeon is now a school *and* a shopping mall! `[?]` means a challenge for your mind, `[$]` means a challenge for your wallet.

### Stage 10: The Grand Escape! 🎉
* **What you'll cook up:** Implemented the `EXIT` room. Reach it with enough gold, and you win! Fail, and you're sent back to collect more.
* **Achieved:** A clear goal! The dungeon has a purpose, and freedom awaits those who are brave and rich enough. The game now has a true ending (or a restart option!).

### Bonus Stage: Polish & Play Again! ✨
* **What you'll cook up:** Added an "Inventory" (`I`) option to use collected `HEALTH_POTION`s. Implemented a "Play Again?" prompt after winning or losing.
* **Achieved:** A smoother, more replayable experience! You can now strategically use items and immediately jump back into the fray for another run.

---

So, what are you waiting for? Clone this repo, compile the code, and embark on your own C++ Dungeon Crawl! May your gold be plentiful and your health potions always stocked!

Happy adventuring!