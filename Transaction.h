#ifndef INCLUDE_TRANSACTION_H_
#define INCLUDE_TRANSACTION_H_

#include <ctime>
#include <string>

#include "Book.h"
#include "Member.h"

class Transaction {
 public:
  Transaction(const std::string& type, Book* book, Member* member);
  std::string toFileString() const;

 private:
  std::string transaction_type_;
  std::string date_;
  Book* book_;
  Member* member_;
};

#endif
