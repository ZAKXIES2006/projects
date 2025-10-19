#include "PremiumMember.h" // Corrected path
#include <iostream>
#include <sstream>

PremiumMember::PremiumMember(const std::string& id, const std::string& password)
    : Member(id, password) {}

void PremiumMember::displayDetails() const {
  std::cout << "--- Premium Member Account ---\n"
            << "ID: " << user_id_ << "\n"
            << "Status: *PREMIUM MEMBER*\n"
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

bool PremiumMember::borrowBook(Book* book) {
  if (currently_borrowed_.size() >= kMaxBooks_) {
    return false;
  }
  currently_borrowed_.push_back(book);
  book->borrowBook();
  return true;
}

std::string PremiumMember::toFileString() const {
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