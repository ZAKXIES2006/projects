#ifndef INCLUDE_ACCOUNT_H_
#define INCLUDE_ACCOUNT_H_

#include <iostream>
#include <string>

class Account {
 public:
  virtual ~Account() = default;
  virtual bool checkLogin(
      const std::string& id,
      const std::string& password) const = 0;      // Pure virtual
  virtual void displayDetails() const = 0;         // Pure virtual
  virtual std::string toFileString() const = 0;    // Pure virtual
  virtual std::string getAccountType() const = 0;  // Pure virtual
  std::string getID() const { return user_id_; }

 protected:
  Account(const std::string& id, const std::string& password)
      : user_id_(id), password_(password) {}
  std::string user_id_;
  std::string password_;
};

#endif
