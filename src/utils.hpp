#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

// Function to simulate typing effect
void typeText(const std::string& text, int speed = 20);

// Function to clear screen (works on most terminals)
void clearScreen();

// Function to wait for any key
void waitForKey();

#endif // UTILS_HPP