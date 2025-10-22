#include "Admin.h"

#include <iostream>
#include <sstream>

Admin::Admin(const std::string& id, const std::string& password)
    : Account(id, password) {}

bool Admin::checkLogin(const std::string& id,
                       const std::string& password) const {
                        // Check whether provided id and password match the stored ones
  return (user_id_ == id && password_ == password);
}

void Admin::displayDetails() const {
  std::cout << "--- Administrator Account ---\n"
            << "ID: " << user_id_ << "\n"
            << "Role: System Administrator" << std::endl;
}

std::string Admin::toFileString() const {
  std::stringstream ss;
  ss << getAccountType() << "|" << user_id_ << "|" << password_; // Format
  return ss.str();
}
