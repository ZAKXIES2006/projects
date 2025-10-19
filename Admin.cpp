#include "Admin.h" // Corrected path
#include <iostream>
#include <sstream>

Admin::Admin(const std::string& id, const std::string& password)
    : Account(id, password) {}

bool Admin::checkLogin(const std::string& id,
                       const std::string& password) const {
  return (user_id_ == id && password_ == password);
}

void Admin::displayDetails() const {
  std::cout << "--- Administrator Account ---\n"
            << "ID: " << user_id_ << "\n"
            << "Role: System Administrator" << std::endl;
}

std::string Admin::toFileString() const {
    std::stringstream ss;
    ss << getAccountType() << "|" << user_id_ << "|" << password_;
    return ss.str();
}
