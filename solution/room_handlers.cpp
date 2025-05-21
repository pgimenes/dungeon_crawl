#include "room_handlers.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <string>

// Handle monster encounters
void handleMonsterRoom(Room& room, Player& player) {
    std::string monsterName;
    int monsterHealth;
    int monsterDamage;
    int goldReward;
    
    switch (room.monsterLevel) {
        case EASY:
            monsterName = "Goblin";
            monsterHealth = 25;
            monsterDamage = 8;
            goldReward = rand() % 16 + 5; // 5-20 gold
            break;
        case MEDIUM:
            monsterName = "Orc";
            monsterHealth = 40;
            monsterDamage = 12;
            goldReward = rand() % 21 + 15; // 15-35 gold
            break;
        case HARD:
            monsterName = "Troll";
            monsterHealth = 60;
            monsterDamage = 18;
            goldReward = rand() % 31 + 30; // 30-60 gold
            break;
    }
    
    typeText("\n🗡️  A " + monsterName + " approaches! Prepare to fight!");
    
    while (monsterHealth > 0 && player.health > 0) {
        std::cout << "\n" << monsterName << " Health: " << monsterHealth << std::endl;
        std::cout << "Your Health: " << player.health << std::endl;
        
        std::cout << "\nWhat will you do?\n";
        std::cout << "1. Attack\n";
        std::cout << "2. Use Health Potion (if available)\n";
        std::cout << "3. Try to Run (50% chance)\n";
        std::cout << "Choice: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                // Player attacks
                int damage = player.strength + (rand() % 10);
                typeText("\nYou attack the " + monsterName + " for " + std::to_string(damage) + " damage!");
                monsterHealth -= damage;
                
                // Monster attacks if still alive
                if (monsterHealth > 0) {
                    int incomingDamage = std::max(1, monsterDamage - player.defense / 2 + (rand() % 5));
                    player.health -= incomingDamage;
                    typeText("The " + monsterName + " strikes back for " + std::to_string(incomingDamage) + " damage!");
                }
                break;
            }
            case 2: {
                // Check if player has health potions
                bool hasPotion = false;
                for (size_t i = 0; i < player.inventory.size(); i++) {
                    if (player.inventory[i] == HEALTH_POTION) {
                        hasPotion = true;
                        player.inventory.erase(player.inventory.begin() + i);
                        break;
                    }
                }
                
                if (hasPotion) {
                    int healAmount = rand() % 21 + 20; // 20-40 healing
                    player.health += healAmount;
                    if (player.health > MAX_HEALTH) player.health = MAX_HEALTH;
                    typeText("\nYou drink a health potion and heal " + std::to_string(healAmount) + " HP!");
                    
                    // Monster still attacks
                    int incomingDamage = std::max(1, monsterDamage - player.defense / 2 + (rand() % 5));
                    player.health -= incomingDamage;
                    typeText("The " + monsterName + " strikes for " + std::to_string(incomingDamage) + " damage!");
                } else {
                    typeText("\nYou don't have any health potions!");
                    continue;
                }
                break;
            }
            case 3: {
                // Try to run
                if (rand() % 100 < 50) {
                    typeText("\nYou successfully flee from the " + monsterName + "!");
                    return;
                } else {
                    typeText("\nYou failed to escape! The " + monsterName + " attacks!");
                    int incomingDamage = std::max(1, monsterDamage - player.defense / 2 + (rand() % 8));
                    player.health -= incomingDamage;
                    typeText("The " + monsterName + " hits you for " + std::to_string(incomingDamage) + " damage!");
                }
                break;
            }
            default:
                std::cout << "Invalid choice. Try again.\n";
                continue;
        }
    }
    
    if (player.health <= 0) {
        typeText("\n⚔️ You were defeated by the " + monsterName + "!");
    } else {
        typeText("\n🎯 You defeated the " + monsterName + "!");
        player.gold += goldReward;
        typeText("You found " + std::to_string(goldReward) + " gold on the corpse!");
    }
}

// Handle puzzle rooms
bool handlePuzzleRoom(Room& room, Player& player) {
    typeText("\n🧩 " + room.description);
    typeText("\"" + room.puzzleQuestion + "\"");
    
    std::cout << "\nYour answer: ";
    std::string answer;
    std::cin >> answer;
    
    // Convert answer to lowercase
    for (char& c : answer) {
        c = tolower(c);
    }
    
    if (answer == room.puzzleAnswer) {
        typeText("\n🎊 Correct! The room shimmers with magic...");
        int reward = rand() % 31 + 20; // 20-50 gold
        player.gold += reward;
        typeText("A hidden compartment opens, revealing " + std::to_string(reward) + " gold!");
        return true;
    } else {
        typeText("\n❌ Incorrect! The room grows dim...");
        int damage = rand() % 16 + 5; // 5-20 damage
        player.health -= damage;
        typeText("Magical energy zaps you, dealing " + std::to_string(damage) + " damage!");
        return false;
    }
}

// Handle merchant rooms
void handleMerchantRoom(Player& player) {
    typeText("\n🛒 \"Welcome, traveler! Care to peruse my wares?\" the merchant says.");
    
    bool shopping = true;
    while (shopping && player.gold > 0) {
        std::cout << "\nMerchant's Inventory:\n";
        std::cout << "1. Health Potion (Heals 20-40 HP) - 30 gold\n";
        std::cout << "2. Strength Potion (+2 Strength) - 40 gold\n";
        std::cout << "3. Shield (+3 Defense) - 50 gold\n";
        std::cout << "4. Exit Shop\n";
        std::cout << "Your gold: " << player.gold << "\n";
        std::cout << "Choice: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                if (player.gold >= 30) {
                    player.gold -= 30;
                    player.inventory.push_back(HEALTH_POTION);
                    typeText("\"A fine choice! This potion will restore your vitality.\"");
                } else {
                    typeText("\"I'm afraid you can't afford that, friend.\"");
                }
                break;
            case 2:
                if (player.gold >= 40) {
                    player.gold -= 40;
                    player.strength += 2;
                    typeText("\"Ah, the essence of giants! Your strikes will be mightier now.\"");
                } else {
                    typeText("\"Come back when your purse is heavier.\"");
                }
                break;
            case 3:
                if (player.gold >= 50) {
                    player.gold -= 50;
                    player.defense += 3;
                    typeText("\"This shield has saved many lives before. May it serve you well.\"");
                } else {
                    typeText("\"Perhaps after you've found more treasure.\"");
                }
                break;
            case 4:
                typeText("\"Safe travels, adventurer! May we meet again.\"");
                shopping = false;
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
    
    if (player.gold <= 0) {
        typeText("\"You seem to be out of coin. Come back when you're richer!\"");
    }
}