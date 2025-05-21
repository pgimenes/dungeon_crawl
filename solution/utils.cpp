#include "utils.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>

// Function to simulate typing effect
void typeText(const std::string& text, int speed) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
    std::cout << std::endl;
}

// Function to clear screen (works on most terminals)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to wait for any key
void waitForKey() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}