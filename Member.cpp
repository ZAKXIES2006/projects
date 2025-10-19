#include "Member.h" // Corrected path
#include <iostream>
#include <sstream>
#include <algorithm>

Member::Member(const std::string& id, const std::string& password)
    : Account(id, password) {}

bool Member::checkLogin(const std::string& id,
                        const std::string& password) const {
  return (user_id_ == id && password_ == password);
}

void Member::displayDetails() const {
  std::cout << "--- Member Account ---\n"
            << "ID: " << user_id_ << "\n"
            << "Status: Standard Member\n"
            << "Books Borrowed (" << currently_borrowed_.size() << "/"
            << kMaxBooks_ << "):\n";
  if (currently_borrowed_.empty()) {
    std::cout << "  (None)\n";
  } else {
    for (const auto* book : currently_borrowed_) {
      std::cout << "  - " << book->getTitle() << " (ISBN: " << book->getISBN()
                << ")\n";
    }
  }
}

bool Member::borrowBook(Book* book) {
  if (currently_borrowed_.size() >= kMaxBooks_) {
    return false;
  }
  currently_borrowed_.push_back(book);
  book->borrowBook();
  return true;
}

bool Member::returnBook(Book* book) {
  auto it = std::find(currently_borrowed_.begin(), currently_borrowed_.end(), book);
  if (it != currently_borrowed_.end()) {
      currently_borrowed_.erase(it);
      book->returnBook();
      return true;
  }
  return false;
}

bool Member::hasBorrowedBook(const std::string& isbn) const {
    for (const auto* book : currently_borrowed_) {
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
    ss << getAccountType() << "|" << user_id_ << "|" << password_ << "|";
    for (size_t i = 0; i < currently_borrowed_.size(); ++i) {
        ss << currently_borrowed_[i]->getISBN();
        if (i < currently_borrowed_.size() - 1) {
            ss << ",";
        }
    }
    return ss.str();
}