#include "display_functions.hpp"
#include <iostream>
#include <string>

// Display the map
void displayMap(const DungeonMap& dungeon, const Player& player) {
    std::cout << "\n🗺️  DUNGEON MAP  🗺️\n";
    std::cout << "  ";
    for (int x = 0; x < MAP_SIZE; x++) {
        std::cout << " " << x + 1 << " ";
    }
    std::cout << std::endl;
    
    for (int y = 0; y < MAP_SIZE; y++) {
        std::cout << y + 1 << " ";
        for (int x = 0; x < MAP_SIZE; x++) {
            if (x == player.x && y == player.y) {
                std::cout << "[P]"; // Player position
            } else if (dungeon.revealed[y][x]) {
                // Show the room type for visited rooms
                switch (dungeon.rooms[y][x].type) {
                    case MONSTER: std::cout << "[M]"; break;
                    case TREASURE: std::cout << "[T]"; break;
                    case POTION: std::cout << "[H]"; break;
                    case PUZZLE: std::cout << "[?]"; break;
                    case TRAP: std::cout << "[!]"; break;
                    case MERCHANT: std::cout << "[$]"; break;
                    case EMPTY: std::cout << "[ ]"; break;
                    case EXIT: std::cout << "[E]"; break;
                    default: std::cout << "[ ]";
                }
            } else {
                std::cout << "[ ]"; // Unexplored room
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Display player status
void displayStatus(const Player& player) {
    std::cout << "\n╔════════════════════════════╗\n";
    std::cout << "║ ❤️  HP: " << player.health << "/" << MAX_HEALTH << " ";
    if (player.health < 30) {
        std::cout << "(DANGER!)";
    }
    for (int i = 0; i < 12 - std::to_string(player.health).length() - std::to_string(MAX_HEALTH).length(); i++) {
        std::cout << " ";
    }
    std::cout << "║\n";
    
    std::cout << "║ 💰 Gold: " << player.gold << "/" << GOLD_TO_ESCAPE;
    for (int i = 0; i < 11 - std::to_string(player.gold).length() - std::to_string(GOLD_TO_ESCAPE).length(); i++) {
        std::cout << " ";
    }
    std::cout << "║\n";
    
    std::cout << "║ 💪 Strength: " << player.strength;
    for (int i = 0; i < 14 - std::to_string(player.strength).length(); i++) {
        std::cout << " ";
    }
    std::cout << "║\n";
    
    std::cout << "║ 🛡️  Defense: " << player.defense;
    for (int i = 0; i < 14 - std::to_string(player.defense).length(); i++) {
        std::cout << " ";
    }
    std::cout << "║\n";
    
    std::cout << "╚════════════════════════════╝\n";
}