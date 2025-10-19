#ifndef INCLUDE_ADMIN_H_
#define INCLUDE_ADMIN_H_

#include "Account.h" // Corrected path

class Admin : public Account {
 public:
  Admin(const std::string& id, const std::string& password);
  virtual ~Admin() = default;
  bool checkLogin(const std::string& id,
                  const std::string& password) const override;
  void displayDetails() const override;
  std::string toFileString() const override;
  std::string getAccountType() const override { return "Admin"; }
};

#endif  // INCLUDE_ADMIN_H_