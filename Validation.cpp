#include "Validation.h"

#include <iostream>
#include <limits>

int util::getValidatedInt(const std::string& prompt) {
  int value;
  while (true) {            // Runs untill valid int is entered
    std::cout << prompt;    // Print prompt
    std::cin >> value;      // Read and store user input
    if (std::cin.good()) {  // If input worked correctly
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n');  // Ignore newline and and input buffer
      return value;
    } else {
      std::cout << "Invalid input. Please enter a whole number.\n";
      std::cin.clear();  // Reset stream
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n');  // Remove invalid input
    }
  }
}

std::string util::getNonEmptyString(const std::string& prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;            // Print prompt
    std::getline(std::cin, input);  // Read and store input
    if (!input.empty()) {           // If not an empty string
      return input;
    } else {
      std::cout << "Input cannot be empty. Please try again.\n";
    }
  }
}