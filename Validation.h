#ifndef VALIDATION_H_
#define VALIDATION_H_

#include <string>

namespace util {
int getValidatedInt(const std::string& prompt); // Request input untill a valid int is entered
std::string getNonEmptyString(const std::string& prompt); // Request input untill a non empty string is entered
}

#endif
