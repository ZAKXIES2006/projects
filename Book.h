#ifndef INCLUDE_BOOK_H_
#define INCLUDE_BOOK_H_

#include <iostream>
#include <string>

class Book {
 public:
  Book(const std::string& isbn, const std::string& title,
       const std::string& author);
  std::string getISBN() const;
  std::string getTitle() const;
  std::string getAuthor() const;
  bool isAvailable() const;
  void printDetails() const;
  bool borrowBook();
  void returnBook();
  std::string toFileString() const;

 private:
  std::string isbn_;
  std::string title_;
  std::string author_;
  bool is_available_;
};

#endif
