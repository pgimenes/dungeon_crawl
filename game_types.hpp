#ifndef GAME_TYPES_HPP
#define GAME_TYPES_HPP

#include <string>
#include <vector>

// Game constants
const int NUM_ROOMS = 10;
const int MAX_HEALTH = 100;
const int GOLD_TO_ESCAPE = 150;
const int MAP_SIZE = 5;  // 5x5 map

// Room types
enum RoomType { MONSTER, TREASURE, POTION, PUZZLE, TRAP, MERCHANT, EMPTY, EXIT };

// Monster difficulty levels
enum MonsterLevel { EASY, MEDIUM, HARD };

// Item types
enum ItemType { HEALTH_POTION, STRENGTH_POTION, SHIELD };

// Player structure
struct Player {
    int health = MAX_HEALTH;
    int gold = 0;
    int strength = 10;
    int defense = 5;
    std::vector<ItemType> inventory;
    int x = MAP_SIZE / 2;  // Starting position
    int y = MAP_SIZE / 2;
};

// Room structure
struct Room {
    RoomType type;
    std::string description;
    bool visited = false;
    MonsterLevel monsterLevel = EASY;    // Only relevant for monster rooms
    int goldAmount = 0;                  // For treasure rooms
    int healthAmount = 0;                // For potion rooms
    std::string puzzleQuestion;          // For puzzle rooms
    std::string puzzleAnswer;            // For puzzle rooms
    int damageAmount = 0;                // For trap rooms
};

// Dungeon map
struct DungeonMap {
    std::vector<std::vector<Room>> rooms;
    bool revealed[MAP_SIZE][MAP_SIZE] = {false};
};

// Direction mapping for navigation
enum Direction { NORTH, SOUTH, EAST, WEST };

#endif // GAME_TYPES_HPP