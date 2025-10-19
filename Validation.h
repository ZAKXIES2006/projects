#ifndef VALIDATION_H_
#define VALIDATION_H_

#include <string>

namespace util {
int getValidatedInt(const std::string& prompt);
std::string getNonEmptyString(const std::string& prompt);
}

#endif  // VALIDATION_H_
