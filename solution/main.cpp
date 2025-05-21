#include "game_types.hpp"
#include "utils.hpp"
#include "room_generator.hpp"
#include "display_functions.hpp"
#include "room_handlers.hpp"
#include <iostream>
#include <limits>


void playGame() {
    clearScreen();
    typeText("🏰 Welcome to the Dungeon Crawl! 🏰", 30);
    typeText("You've been trapped in a cursed dungeon filled with monsters and mysteries.");
    typeText("To escape, you must collect " + std::to_string(GOLD_TO_ESCAPE) + " gold to buy your freedom.");
    typeText("Navigate carefully - death awaits the unwary!\n");
    waitForKey();
    
    // Initialize player and dungeon
    Player player;
    DungeonMap dungeon = initializeDungeon();
    
    // Reveal starting position
    dungeon.revealed[player.y][player.x] = true;
    dungeon.rooms[player.y][player.x].visited = true;
    
    bool gameOver = false;
    
    // Initial room description
    clearScreen();
    typeText("You find yourself in a dimly lit chamber. Exits lead in several directions.");
    
    while (!gameOver) {
        // Display current state
        displayMap(dungeon, player);
        displayStatus(player);
        
        // Movement options
        std::cout << "\n➡️ Where will you go?\n";
        std::cout << "W - North (Up)\n";
        std::cout << "S - South (Down)\n";
        std::cout << "A - West (Left)\n";
        std::cout << "D - East (Right)\n";
        std::cout << "I - Check Inventory\n";
        std::cout << "Q - Quit Game\n";
        std::cout << "Choice: ";
        
        // Check input buffer before getting choice
        std::cin.clear();
        while (std::cin.get() != '\n') {
            // Clear input buffer
            if (std::cin.eof()) break;
        }
        char choice;
        std::cin >> choice;
        choice = tolower(choice);
        
        // Handle movement
        int newX = player.x;
        int newY = player.y;
        
        switch (choice) {
            case 'w': // North
                if (player.y > 0) newY--;
                else std::cout << "You can't go that way.\n";
                break;
            case 's': // South
                if (player.y < MAP_SIZE - 1) newY++;
                else std::cout << "You can't go that way.\n";
                break;
            case 'a': // West
                if (player.x > 0) newX--;
                else std::cout << "You can't go that way.\n";
                break;
            case 'd': // East
                if (player.x < MAP_SIZE - 1) newX++;
                else std::cout << "You can't go that way.\n";
                break;
            case 'i': // Inventory
                std::cout << "\n📦 Inventory:\n";
                if (player.inventory.empty()) {
                    std::cout << "Your backpack is empty.\n";
                } else {
                    int healthPotions = 0;
                    for (ItemType item : player.inventory) {
                        if (item == HEALTH_POTION) healthPotions++;
                    }
                    if (healthPotions > 0) {
                        std::cout << "Health Potions: " << healthPotions << " (use during combat)\n";
                    }
                }
                waitForKey();
                continue;
            case 'q': // Quit
                std::cout << "\nAre you sure you want to quit? (y/n): ";
                char confirm;
                std::cin >> confirm;
                if (tolower(confirm) == 'y') {
                    gameOver = true;
                    std::cout << "\nThanks for playing Dungeon Crawl! 🐉\n";
                }
                continue;
            default:
                std::cout << "Invalid choice. Try again.\n";
                continue;
        }
        
        // Check if movement is valid
        if (newX == player.x && newY == player.y) {
            continue;  // No movement occurred
        }
        
        // Move player
        player.x = newX;
        player.y = newY;
        
        // Reveal the new room on the map
        dungeon.revealed[player.y][player.x] = true;
        
        // Process room if not visited before
        Room& currentRoom = dungeon.rooms[player.y][player.x];
        
        clearScreen();
        if (!currentRoom.visited) {
            typeText("\n➡️ You enter a new area...");
            typeText(currentRoom.description);
            
            // Handle room based on type
            switch (currentRoom.type) {
                case MONSTER:
                    handleMonsterRoom(currentRoom, player);
                    break;
                    
                case TREASURE:
                    typeText("\n💰 You found a treasure chest!");
                    player.gold += currentRoom.goldAmount;
                    typeText("You collect " + std::to_string(currentRoom.goldAmount) + " gold!");
                    break;
                    
                case POTION:
                    typeText("\n🧪 You found a healing potion!");
                    player.health += currentRoom.healthAmount;
                    if (player.health > MAX_HEALTH) player.health = MAX_HEALTH;
                    typeText("You drink it and heal " + std::to_string(currentRoom.healthAmount) + " HP.");
                    break;
                    
                case PUZZLE:
                    handlePuzzleRoom(currentRoom, player);
                    break;
                    
                case TRAP:
                    typeText("\n⚠️ It's a trap!");
                    player.health -= currentRoom.damageAmount;
                    typeText("You take " + std::to_string(currentRoom.damageAmount) + " damage!");
                    break;
                    
                case MERCHANT:
                    handleMerchantRoom(player);
                    break;
                    
                case EMPTY:
                    typeText("\n🔕 This room seems safe... for now.");
                    break;
                    
                case EXIT:
                    if (player.gold >= GOLD_TO_ESCAPE) {
                        typeText("\n🚪 You've found the exit!");
                        typeText("You deposit your " + std::to_string(GOLD_TO_ESCAPE) + " gold into the door's mechanism...");
                        typeText("With a thunderous rumble, the door swings open, revealing daylight beyond!");
                        player.gold -= GOLD_TO_ESCAPE;
                        typeText("\n🎉 CONGRATULATIONS! You've escaped the dungeon with " + std::to_string(player.gold) + " extra gold!");
                        gameOver = true;
                    } else {
                        typeText("\n🚪 You've found the exit, but it's sealed with a magical lock.");
                        typeText("An inscription reads: \"Only those who offer " + std::to_string(GOLD_TO_ESCAPE) + " gold may pass.\"");
                        typeText("You need " + std::to_string(GOLD_TO_ESCAPE - player.gold) + " more gold to escape!");
                    }
                    break;
            }
            
            currentRoom.visited = true;
        } else {
            typeText("\n🔄 You've been here before. The room is now empty.");
        }
        
        // Check for player death
        if (player.health <= 0) {
            typeText("\n💀 Your wounds are too severe. You collapse to the ground...");
            typeText("The dungeon claims another victim. Game Over!");
            gameOver = true;
        }
        
        waitForKey();
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    playGame();
    
    return 0;
}