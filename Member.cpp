#include "Member.h"

#include <algorithm>
#include <iostream>
#include <sstream>

Member::Member(const std::string& id, const std::string& password)
    : Account(id, password) {}

bool Member::checkLogin(const std::string& id,
                        const std::string& password) const {
  return (user_id_ == id && password_ == password);
}

void Member::displayDetails() const {
  std::cout << "\n--- Member Account ---\n"
            << "ID: " << user_id_ << "\n"
            << "Status: Standard Member\n"
            << "Books Borrowed (" << currently_borrowed_.size() << "/"
            << kMaxBooks_ << "):\n";
  if (currently_borrowed_.empty()) {  // If no books borrowed
    std::cout << "  (None)\n";
  } else {
    for (const auto* book : currently_borrowed_) {  // Loop through every book
                                                    // in currently_borrowed
      // Print the book's ISBN and title
      std::cout << "  - " << book->getTitle() << " (ISBN: " << book->getISBN()
                << ")\n";
    }
  }
}

bool Member::borrowBook(Book* book) {
  if (currently_borrowed_.size() >=
      kMaxBooks_) {  // If member has reached their borrowing capacity
    return false;
  }
  // Otherwise proceed
  currently_borrowed_.push_back(book);  // Append book to currently_borrowed_
  book->borrowBook();                   // Mark book as borrowed
  return true;
}

bool Member::returnBook(Book* book) {
  // Find and store an iterator pointing to the book's position in
  // currently_borrowed_
  auto it =
      std::find(currently_borrowed_.begin(), currently_borrowed_.end(), book);
  if (it !=
      currently_borrowed_.end()) {  // if the iterator does not equal ned(),
                                    // book was found currently_borrowed_
    currently_borrowed_.erase(it);  // Remove the book pointer
    book->returnBook();             // Mark book as returned
    return true;
  }
  return false;
}

bool Member::hasBorrowedBook(const std::string& isbn) const {
  for (const auto* book :
       currently_borrowed_) {  // Loop through every book in currently_borrowed_
    if (book->getISBN() == isbn) {
      return true;
    }
  }
  return false;
}

const std::vector<Book*>& Member::getBorrowedBooks() const {
  return currently_borrowed_;
}

void Member::addBorrowedBook(Book* book) {
  currently_borrowed_.push_back(book);
}

std::string Member::toFileString() const {
  std::stringstream ss;
  ss << getAccountType() << "|" << user_id_ << "|" << password_
     << "|";  // Format of the string stream
  for (size_t i = 0; i < currently_borrowed_.size();
       ++i) {                                 // Loop through borrowed books
    ss << currently_borrowed_[i]->getISBN();  // Add each ISBN to the string
    if (i < currently_borrowed_.size() - 1) {
      ss << ",";  // If not the last book, add a comma
    }
  }
  return ss.str();
}