#include "Validation.h" // Corrected path
#include <iostream>
#include <limits>

int util::getValidatedInt(const std::string& prompt) {
  int value;
  while (true) {
    std::cout << prompt;
    std::cin >> value;
    if (std::cin.good()) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return value;
    } else {
      std::cout << "Invalid input. Please enter a whole number.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

std::string util::getNonEmptyString(const std::string& prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input);
    if (!input.empty()) {
      return input;
    } else {
      std::cout << "Input cannot be empty. Please try again.\n";
    }
  }
}