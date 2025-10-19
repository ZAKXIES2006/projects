#include "Transaction.h" // Corrected path
#include <iostream>
#include <sstream>
#include <iomanip>

std::string getCurrentTime() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

Transaction::Transaction(const std::string& type, Book* book, Member* member)
    : transaction_type_(type), book_(book), member_(member) {
        date_ = getCurrentTime();
}

std::string Transaction::toFileString() const {
    std::stringstream ss;
    ss << date_ << "|" << transaction_type_ << "|" << member_->getID() << "|" << book_->getISBN();
    return ss.str();
}
