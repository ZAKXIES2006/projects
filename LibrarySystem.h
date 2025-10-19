#ifndef INCLUDE_LIBRARY_SYSTEM_H_
#define INCLUDE_LIBRARY_SYSTEM_H_

#include <vector>
#include <string>
#include <memory>
#include "Account.h"      // Corrected path
#include "Book.h"         // Corrected path
#include "Transaction.h"  // Corrected path
#include "Member.h"       // Corrected path

class LibrarySystem {
 public:
  LibrarySystem();
  ~LibrarySystem() = default;
  LibrarySystem(const LibrarySystem&) = delete;
  LibrarySystem& operator=(const LibrarySystem&) = delete;
  void run();

 private:
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

#endif  // INCLUDE_LIBRARY_SYSTEM_H_
