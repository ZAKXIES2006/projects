#include "Transaction.h" 
#include <iostream>
#include <sstream>
#include <iomanip>

std::string getCurrentTime() {
    auto t = std::time(nullptr); // Get system time
    auto tm = *std::localtime(&t); // Convert raw time (t) into yyyy-mm-dd hr::min::sec
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); // Format
    return ss.str();
}

Transaction::Transaction(const std::string& type, Book* book, Member* member)
    : transaction_type_(type), book_(book), member_(member) {
        date_ = getCurrentTime();
}

std::string Transaction::toFileString() const {
    std::stringstream ss;
    ss << date_ << "|" << transaction_type_ << "|" << member_->getID() << "|" << book_->getISBN(); // Format
    return ss.str();
}
