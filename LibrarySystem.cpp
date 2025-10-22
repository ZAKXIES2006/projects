#include "LibrarySystem.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

#include "Admin.h"
#include "Member.h"
#include "PremiumMember.h"
#include "Validation.h"

const std::string BOOKS_FILE = "data/books.dat";
const std::string ACCOUNTS_FILE = "data/accounts.dat";
const std::string TRANSACTIONS_FILE = "data/transactions.log";

LibrarySystem::LibrarySystem() {
  loadState();
  if (findAccountByID("admin") == nullptr) {
    std::cout << "No 'admin' account found. Creating a default admin.\n"
              << ">> Username: admin, Password: password\n";
    accounts_.push_back(std::make_unique<Admin>(
        "admin", "password"));  // Create an admin account
  }
}

void LibrarySystem::run() {
  bool running = true;
  while (running) {
    if (current_user_ == nullptr) { 
      showMainMenu();
      int choice = util::getValidatedInt("Enter choice: ");
      switch (choice) {
        case 1:
          handleLogin();
          break;
        case 2:
          running = false;
          break;
        default:
          std::cout << "Invalid choice. Please try again.\n";
      }
    } else {
      if (dynamic_cast<Admin*>(current_user_)) {
        showAdminMenu();
      } else if (dynamic_cast<Member*>(current_user_)) {
        showMemberMenu();
      }
    }
  }
  std::cout << "Saving state and shutting down. Goodbye!\n";
  saveState();
}

void LibrarySystem::showMainMenu() {
  std::cout << "\n===== Library Main Menu =====\n"
            << "1. Login\n"
            << "2. Exit\n"
            << "===========================\n";
}

void LibrarySystem::showAdminMenu() {
  std::cout << "\n===== Admin Menu (Logged in as " << current_user_->getID()
            << ") =====\n"
            << "1. Add New Book\n"
            << "2. Add New Member Account\n"
            << "3. View All Member Details\n"
            << "4. Logout\n"
            << "==========================================\n";
  int choice = util::getValidatedInt("Enter choice: ");
  switch (choice) { // Admin menu functionality
    case 1:
      adminAddBook();
      break;
    case 2:
      adminAddMember();
      break;
    case 3:
      adminViewAllMembers();
      break;
    case 4:
      handleLogout();
      break;
    default:
      std::cout << "Invalid choice. Please try again.\n";
  }
}

void LibrarySystem::showMemberMenu() {
  std::cout << "\n===== Member Menu (Logged in as " << current_user_->getID()
            << ") =====\n"
            << "1. Borrow a Book\n"
            << "2. Return a Book\n"
            << "3. View My Account Details\n"
            << "4. Logout\n"
            << "==========================================\n";

  int choice = util::getValidatedInt("Enter choice: ");
  switch (choice) { // Member menu functionality
    case 1:
      memberBorrowBook();
      break;
    case 2:
      memberReturnBook();
      break;
    case 3:
      memberViewMyBooks();
      break;
    case 4:
      handleLogout();
      break;
    default:
      std::cout << "Invalid choice. Please try again.\n";
  }
}

void LibrarySystem::handleLogin() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::string id = util::getNonEmptyString("Enter User ID: ");
  std::string pw = util::getNonEmptyString("Enter Password: ");
  Account* user = findAccountByID(id);
  if (user != nullptr && user->checkLogin(id, pw)) { // If the account exists and credentials are valid login successful
    current_user_ = user;
    std::cout << "Login successful. Welcome, " << current_user_->getID()
              << "!\n";
  } else {
    std::cout << "Error: Invalid User ID or Password.\n";
  }
}

void LibrarySystem::handleLogout() {
  std::cout << "Logging out " << current_user_->getID() << ".\n";
  current_user_ = nullptr;
}

void LibrarySystem::adminAddBook() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::string isbn = util::getNonEmptyString("Enter book ISBN: ");
  if (findBookByISBN(isbn) != nullptr) { // Check if book already exists
    std::cout << "Error: A book with ISBN " << isbn << " already exists.\n";
    return;
  }
  std::string title = util::getNonEmptyString("Enter book title: ");
  std::string author = util::getNonEmptyString("Enter book author: ");
  books_.push_back(std::make_unique<Book>(isbn, title, author)); // Instantiate a book object with input parameters and append it to books_
  std::cout << "Success: Book '" << title << "' has been added.\n";
}

void LibrarySystem::adminAddMember() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::string id = util::getNonEmptyString("Enter new member ID: ");
  if (findAccountByID(id) != nullptr) { // Check if the account with this id already exists
    std::cout << "Error: An account with ID '" << id << "' already exists.\n";
    return;
  }
  std::string pw = util::getNonEmptyString("Enter new member's password: ");
  int type =
      util::getValidatedInt("Enter account type (1=Standard, 2=Premium): ");
  if (type == 2) {
    // Instantiate a PremiumMember object and append to accounts_
    accounts_.push_back(std::make_unique<PremiumMember>(id, pw));
    std::cout << "Success: Premium Member '" << id << "' created.\n";
  } else {
    // Instantiate a Member object and append to accounts_
    accounts_.push_back(std::make_unique<Member>(id, pw));
    std::cout << "Success: Standard Member '" << id << "' created.\n";
  }
}

void LibrarySystem::adminViewAllMembers() const {
  std::cout << "\n--- All Member Accounts ---\n";
  bool found = false;
  for (const auto& acc : accounts_) { 
    if (dynamic_cast<Member*>(acc.get())) {
      acc->displayDetails();
      std::cout << "---------------------------\n";
      found = true;
    }
  }
  if (!found) {
    std::cout << "No member accounts in the system.\n";
  }
}

void LibrarySystem::memberBorrowBook() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::string isbn =
      util::getNonEmptyString("Enter ISBN of the book to borrow: ");
  try {
    Book* book = findBookByISBN(isbn);
    if (book == nullptr) throw std::runtime_error("Book not found."); // If book doesn't exist throw error
    if (!book->isAvailable())
      throw std::runtime_error("Book is already borrowed by someone else.");
    Member* current_member = dynamic_cast<Member*>(current_user_);
    if (current_member && current_member->borrowBook(book)) {
      std::cout << "Success: You have borrowed '" << book->getTitle() << "'.\n";
      recordTransaction("Borrow", book, current_member);
    } else {
      throw std::runtime_error("You have reached your borrowing limit.");
    }
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << "\n";
  }
}

void LibrarySystem::memberReturnBook() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::string isbn =
      util::getNonEmptyString("Enter ISBN of the book to return: ");
  try {
    Book* book = findBookByISBN(isbn);
    if (book == nullptr)
      throw std::runtime_error("Book not found in the system.");
    Member* current_member = dynamic_cast<Member*>(current_user_);
    if (current_member && current_member->returnBook(book)) {
      std::cout << "Success: You have returned '" << book->getTitle() << "'.\n";
      recordTransaction("Return", book, current_member);
    } else {
      throw std::runtime_error("You have not borrowed this book.");
    }
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << "\n";
  }
}

void LibrarySystem::memberViewMyBooks() const {
  if (current_user_) {
    current_user_->displayDetails();
  }
}

Book* LibrarySystem::findBookByISBN(const std::string& isbn) const {
  for (const auto& book : books_) {
    if (book->getISBN() == isbn) return book.get();
  }
  return nullptr;
}

Account* LibrarySystem::findAccountByID(const std::string& id) const {
  for (const auto& acc : accounts_) {
    if (acc->getID() == id) return acc.get();
  }
  return nullptr;
}

void LibrarySystem::recordTransaction(const std::string& type, Book* book,
                                      Member* member) {
  transactions_.push_back(std::make_unique<Transaction>(type, book, member));
}

void LibrarySystem::loadState() {
  loadBooks();
  loadAccounts();
  std::cout << "System loaded " << books_.size() << " books and "
            << accounts_.size() << " accounts from file.\n";
}

void LibrarySystem::saveState() const {
  saveBooks();
  saveAccounts();
  saveTransactions();
  std::cout << "System state has been saved to data files.\n";
}

void LibrarySystem::loadBooks() {
  std::ifstream file(BOOKS_FILE);
  if (!file) {
    return;
  }
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string isbn, title, author, available_str;
    if (std::getline(ss, isbn, '|') && std::getline(ss, title, '|') &&
        std::getline(ss, author, '|') && std::getline(ss, available_str)) {
      auto book = std::make_unique<Book>(isbn, title, author);
      if (available_str == "0") book->borrowBook();
      books_.push_back(std::move(book));
    }
  }
}

void LibrarySystem::loadAccounts() {
  std::ifstream file(ACCOUNTS_FILE);
  if (!file) {
    return;
  }
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string type, id, pw, borrowed_isbns;
    if (std::getline(ss, type, '|') && std::getline(ss, id, '|') &&
        std::getline(ss, pw, '|')) {
      std::unique_ptr<Account> acc;
      if (type == "Admin") {
        acc = std::make_unique<Admin>(id, pw);
      } else if (type == "Member") {
        acc = std::make_unique<Member>(id, pw);
      } else if (type == "PremiumMember") {
        acc = std::make_unique<PremiumMember>(id, pw);
      }
      if (acc) {
        if (std::getline(ss, borrowed_isbns)) {
          Member* member = dynamic_cast<Member*>(acc.get());
          if (member) {
            std::stringstream isbn_ss(borrowed_isbns);
            std::string isbn;
            while (std::getline(isbn_ss, isbn, ',')) {
              Book* book = findBookByISBN(isbn);
              if (book) member->addBorrowedBook(book);
            }
          }
        }
        accounts_.push_back(std::move(acc));
      }
    }
  }
}

void LibrarySystem::saveBooks() const {
  std::ofstream file(BOOKS_FILE);
  if (!file) {
    std::cerr << "Error: Could not open " << BOOKS_FILE << " for writing.\n";
    return;
  }
  for (const auto& book : books_) {
    file << book->toFileString() << "\n";
  }
}

void LibrarySystem::saveAccounts() const {
  std::ofstream file(ACCOUNTS_FILE);
  if (!file) {
    std::cerr << "Error: Could not open " << ACCOUNTS_FILE << " for writing.\n";
    return;
  }
  for (const auto& acc : accounts_) {
    file << acc->toFileString() << "\n";
  }
}

void LibrarySystem::saveTransactions() const {
  std::ofstream file(TRANSACTIONS_FILE, std::ios::app);
  if (!file) {
    std::cerr << "Error: Could not open " << TRANSACTIONS_FILE
              << " for writing.\n";
    return;
  }
  for (const auto& tr : transactions_) {
    file << tr->toFileString() << "\n";
  }
}