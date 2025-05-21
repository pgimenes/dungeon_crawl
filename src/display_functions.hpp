#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "game_types.hpp"

// Display the map
void displayMap(const DungeonMap& dungeon, const Player& player);

// Display player status
void displayStatus(const Player& player);

#endif // DISPLAY_HPP