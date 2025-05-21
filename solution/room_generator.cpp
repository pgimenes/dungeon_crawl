#include "room_generator.hpp"
#include <cstdlib>
#include <vector>
#include <utility>

// Function to create a monster room
Room createMonsterRoom() {
    Room room;
    room.type = MONSTER;
    
    // Determine monster difficulty
    int level = rand() % 100;
    if (level < 60) {
        room.monsterLevel = EASY;
        room.description = "A small goblin lurks in the shadows, its eyes glowing with malice.";
    } else if (level < 90) {
        room.monsterLevel = MEDIUM;
        room.description = "A hulking orc guards this chamber, wielding a rusty battleaxe.";
    } else {
        room.monsterLevel = HARD;
        room.description = "A terrifying troll roars as you enter, its massive club ready to strike!";
    }
    
    return room;
}

// Function to create a treasure room
Room createTreasureRoom() {
    Room room;
    room.type = TREASURE;
    
    // Determine gold amount
    room.goldAmount = rand() % 41 + 20; // 20-60 gold
    
    std::vector<std::string> descriptions = {
        "A small chest sits in the corner, filled with gleaming gold coins.",
        "Scattered across the floor are precious gemstones and gold pieces.",
        "The skeleton of an adventurer clutches a bag of gold in its bony fingers.",
        "A broken statue reveals a hidden cache of treasure within."
    };
    
    room.description = descriptions[rand() % descriptions.size()];
    return room;
}

// Function to create a potion room
Room createPotionRoom() {
    Room room;
    room.type = POTION;
    
    // Determine healing amount
    room.healthAmount = rand() % 26 + 15; // 15-40 health
    
    std::vector<std::string> descriptions = {
        "A bubbling cauldron emits a pleasant aroma. Perhaps the contents are beneficial?",
        "Shelves line the walls, filled with colorful potions and elixirs.",
        "A pedestal in the center holds a glowing red potion.",
        "An alchemist's workbench contains a freshly brewed healing draught."
    };
    
    room.description = descriptions[rand() % descriptions.size()];
    return room;
}

// Function to create a puzzle room
Room createPuzzleRoom() {
    Room room;
    room.type = PUZZLE;
    
    // Array of riddles with answers
    std::vector<std::pair<std::string, std::string>> riddles = {
        {"I speak without a mouth and hear without ears. I have no body, but I come alive with wind. What am I?", "echo"},
        {"The more you take, the more you leave behind. What am I?", "footsteps"},
        {"What has keys but no locks, space but no room, and you can enter but not go in?", "keyboard"},
        {"What comes once in a minute, twice in a moment, but never in a thousand years?", "m"},
        {"What can travel around the world while staying in a corner?", "stamp"}
    };
    
    int index = rand() % riddles.size();
    room.puzzleQuestion = riddles[index].first;
    room.puzzleAnswer = riddles[index].second;
    
    room.description = "A strange inscription is carved into the wall, posing a riddle:";
    return room;
}

// Function to create a trap room
Room createTrapRoom() {
    Room room;
    room.type = TRAP;
    
    // Determine damage amount
    room.damageAmount = rand() % 16 + 10; // 10-25 damage
    
    std::vector<std::string> descriptions = {
        "As you enter, the floor gives way beneath you! Sharp spikes await below.",
        "Poisonous darts shoot from the walls as you trigger a hidden pressure plate!",
        "A swinging blade descends from the ceiling, barely missing your head!",
        "The room suddenly fills with noxious gas, burning your lungs and eyes!"
    };
    
    room.description = descriptions[rand() % descriptions.size()];
    return room;
}

// Function to create a merchant room
Room createMerchantRoom() {
    Room room;
    room.type = MERCHANT;
    
    room.description = "A weary traveler has set up a small shop in this room, offering various items for sale.";
    return room;
}

// Function to create an empty room
Room createEmptyRoom() {
    Room room;
    room.type = EMPTY;
    
    std::vector<std::string> descriptions = {
        "This room is eerily quiet. Dust covers the floor, undisturbed for ages.",
        "Ancient tapestries hang from the walls, depicting battles long forgotten.",
        "Water drips from the ceiling, forming a small puddle on the stone floor.",
        "Broken furniture and scattered debris suggest this room was once inhabited."
    };
    
    room.description = descriptions[rand() % descriptions.size()];
    return room;
}

// Function to create the exit room
Room createExitRoom() {
    Room room;
    room.type = EXIT;
    room.description = "A massive iron door stands before you, engraved with ancient runes. A keyhole gleams, shaped to accept gold coins...";
    return room;
}

// Generate a random room based on probabilities
Room generateRandomRoom() {
    int r = rand() % 100;
    
    if (r < 25) {
        return createMonsterRoom();
    } else if (r < 40) {
        return createTreasureRoom();
    } else if (r < 55) {
        return createPotionRoom();
    } else if (r < 70) {
        return createPuzzleRoom();
    } else if (r < 80) {
        return createTrapRoom();
    } else if (r < 90) {
        return createMerchantRoom();
    } else {
        return createEmptyRoom();
    }
}

// Initialize the dungeon map
DungeonMap initializeDungeon() {
    DungeonMap dungeon;
    dungeon.rooms.resize(MAP_SIZE, std::vector<Room>(MAP_SIZE));
    
    // Generate random rooms for the map
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            dungeon.rooms[y][x] = generateRandomRoom();
        }
    }
    
    // Place exit room in a random edge position
    int edge = rand() % 4;  // 0=top, 1=right, 2=bottom, 3=left
    int pos = rand() % MAP_SIZE;
    
    switch (edge) {
        case 0: // Top edge
            dungeon.rooms[0][pos] = createExitRoom();
            break;
        case 1: // Right edge
            dungeon.rooms[pos][MAP_SIZE-1] = createExitRoom();
            break;
        case 2: // Bottom edge
            dungeon.rooms[MAP_SIZE-1][pos] = createExitRoom();
            break;
        case 3: // Left edge
            dungeon.rooms[pos][0] = createExitRoom();
            break;
    }
    
    return dungeon;
}