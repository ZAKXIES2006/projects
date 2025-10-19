#include <iostream>
#include <stdexcept>
#include "LibrarySystem.h" // Corrected path

int main() {
  try {
    LibrarySystem library;
    library.run();
  } catch (const std::exception& e) {
    std::cerr << "\n[FATAL ERROR] A critical and unexpected error occurred: "
              << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "\n[FATAL ERROR] An unknown critical error occurred." << std::endl;
    return 1;
  }
  return 0;
}
