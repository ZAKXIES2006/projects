#ifndef INCLUDE_MEMBER_H_
#define INCLUDE_MEMBER_H_

#include <string>
#include <vector>

#include "Account.h"
#include "Book.h"

class Member : public Account {
 public:
  Member(const std::string& id, const std::string& password);
  virtual ~Member() = default;
  bool checkLogin(const std::string& id,
                  const std::string& password) const override;
  void displayDetails() const override;
  std::string toFileString() const override;
  std::string getAccountType() const override { return "Member"; }
  virtual bool borrowBook(Book* book);
  bool returnBook(Book* book);
  const std::vector<Book*>& getBorrowedBooks() const;
  bool hasBorrowedBook(const std::string& isbn) const;
  void addBorrowedBook(Book* book);

 protected:
  // Vector with pointers to book objects
  std::vector<Book*> currently_borrowed_;
  // Only one copy of this variable in the entire class (static)
  static const int kMaxBooks_ = 5;
};

#endif
