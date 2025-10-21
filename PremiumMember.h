#ifndef INCLUDE_PREMIUM_MEMBER_H_
#define INCLUDE_PREMIUM_MEMBER_H_

#include "Member.h"

class PremiumMember : public Member {
 public:
  PremiumMember(const std::string& id, const std::string& password);
  virtual ~PremiumMember() = default;
  void displayDetails() const override;
  bool borrowBook(Book* book) override;
  std::string toFileString() const override;
  std::string getAccountType() const override { return "PremiumMember"; }

 private:
 // Only one copy of this variable in this class
  static const int kMaxBooks_ = 10;
};

#endif
