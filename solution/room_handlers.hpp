#ifndef ROOM_HANDLERS_HPP
#define ROOM_HANDLERS_HPP

#include "game_types.hpp"

// Handle monster encounters
void handleMonsterRoom(Room& room, Player& player);

// Handle puzzle rooms
bool handlePuzzleRoom(Room& room, Player& player);

// Handle merchant rooms
void handleMerchantRoom(Player& player);

#endif // ROOM_HANDLERS_HPP