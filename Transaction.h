#ifndef INCLUDE_TRANSACTION_H_
#define INCLUDE_TRANSACTION_H_

#include <string>
#include <ctime>
#include "Book.h"   // Corrected path
#include "Member.h" // Corrected path

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

#endif  // INCLUDE_TRANSACTION_H_
