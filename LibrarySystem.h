#ifndef INCLUDE_LIBRARY_SYSTEM_H_
#define INCLUDE_LIBRARY_SYSTEM_H_

#include <memory>
#include <string>
#include <vector>

#include "Account.h"
#include "Book.h"
#include "Member.h"
#include "Transaction.h"

class LibrarySystem {
 public:
  LibrarySystem();
  ~LibrarySystem() = default;
  LibrarySystem(const LibrarySystem&) =
      delete;  // Prevent making a copy of a LibrarySystem object
  LibrarySystem& operator=(const LibrarySystem&) =
      delete;  // Prevent assigning one LibrarySystem object't data to another
  void run();

 private:
  // Vectors with smart pointers to Book, Account, and Transaction objects
  std::vector<std::unique_ptr<Book>> books_;
  std::vector<std::unique_ptr<Account>> accounts_;
  std::vector<std::unique_ptr<Transaction>> transactions_;

  Account* current_user_ = nullptr;
  void loadState();
  void saveState() const;
  void loadBooks();
  void loadAccounts();
  void saveBooks() const;
  void saveAccounts() const;
  void saveTransactions() const;
  void showMainMenu();
  void showAdminMenu();
  void showMemberMenu();
  void handleLogin();
  void handleLogout();
  void adminAddBook();
  void adminRemoveBook();
  void adminAddMember();
  void adminViewAllMembers() const;
  void memberBorrowBook();
  void memberReturnBook();
  void memberViewMyBooks() const;
  Book* findBookByISBN(const std::string& isbn) const;
  Account* findAccountByID(const std::string& id) const;
  void recordTransaction(const std::string& type, Book* book, Member* member);
};

#endif 
