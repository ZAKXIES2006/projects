#include "Book.h"

#include <iostream>
#include <sstream>

Book::Book(const std::string& isbn, const std::string& title,
           const std::string& author)
    : isbn_(isbn), title_(title), author_(author), is_available_(true) {}
std::string Book::getISBN() const { return isbn_; }
std::string Book::getTitle() const { return title_; }
std::string Book::getAuthor() const { return author_; }
bool Book::isAvailable() const { return is_available_; }

void Book::printDetails() const {
  std::cout << "  > ISBN: " << isbn_ << "\n"
            << "  > Title: " << title_ << "\n"
            << "  > Author: " << author_ << "\n"
            << "  > Status: " << (is_available_ ? "Available" : "Borrowed")
            << std::endl;
}
bool Book::borrowBook() { // Change the availability status of the book when borrowed
  if (is_available_) {
    is_available_ = false;
    return true;
  }
  return false;
}
void Book::returnBook() { is_available_ = true; }
std::string Book::toFileString() const {
  std::stringstream ss;
  ss << isbn_ << "|" << title_ << "|" << author_ << "|" << is_available_;
  return ss.str();
}
