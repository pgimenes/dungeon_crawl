#ifndef ROOM_GENERATOR_HPP
#define ROOM_GENERATOR_HPP

#include "game_types.hpp"

// Room creation functions
Room createMonsterRoom();
Room createTreasureRoom();
Room createPotionRoom();
Room createPuzzleRoom();
Room createTrapRoom();
Room createMerchantRoom();
Room createEmptyRoom();
Room createExitRoom();

// Generate a random room based on probabilities
Room generateRandomRoom();

// Initialize the entire dungeon map
DungeonMap initializeDungeon();

#endif // ROOM_GENERATOR_HPP