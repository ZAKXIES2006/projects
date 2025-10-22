#include <iostream>
#include <stdexcept>

#include "LibrarySystem.h"

int main() {
  try {  // If anything throws an exception when running jump to one of catch
         // blocks
    // Instantiate a LibrarySystem object then call the run method
    LibrarySystem library;
    library.run();
  } catch (const std::exception& e) {  // Catch any standard C++ exception
    // Print the error message from the exception
    std::cerr << "\n[FATAL ERROR] A critical and unexpected error occurred: "
              << e.what() << std::endl;
    return 1;
  } catch (...) {  // Catch any non standard exceptions
    // Print error message
    std::cerr << "\n[FATAL ERROR] An unknown critical error occurred."
              << std::endl;
    return 1;
  }
  return 0;
}
