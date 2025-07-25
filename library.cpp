#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm> // Needed for std::remove

using namespace std;

// Structure to store book information
struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable;
};

// Structure to store borrower information
struct Borrower {
    string name;
    string borrowerID;
    string borrowedISBN;
    tm dueDate;

    // Equality operator to compare two Borrower objects (required for std::remove)
    bool operator==(const Borrower& other) const {
        return borrowerID == other.borrowerID && borrowedISBN == other.borrowedISBN;
    }
};

// Function to add days to a given date
tm addDaysToDate(const tm& date, int days) {
    tm newDate = date;
    const time_t ONE_DAY = 24 * 60 * 60;
    time_t date_seconds = mktime(&newDate) + (days * ONE_DAY);
    localtime_r(&date_seconds, &newDate);
    return newDate;
}

// Class to manage the library system
class LibrarySystem {
public:
    void addBook(const string &title, const string &author, const string &ISBN) {
        books.push_back({title, author, ISBN, true});
    }

    void searchBook() {
        int choice;
        string query;
        cout << "\nSearch by: 1. Title 2. Author 3. ISBN\nEnter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character left by cin
        switch (choice) {
            case 1:
                cout << "Enter title: ";
                getline(cin, query);
                searchByTitle(query);
                break;
            case 2:
                cout << "Enter author: ";
                getline(cin, query);
                searchByAuthor(query);
                break;
            case 3:
                cout << "Enter ISBN: ";
                getline(cin, query);
                searchByISBN(query);
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    }

    void checkoutBook() {
        string borrowerName, borrowerID, ISBN;
        cout << "\nEnter borrower name: ";
        cin.ignore();
        getline(cin, borrowerName);
        cout << "Enter borrower ID: ";
        getline(cin, borrowerID);
        cout << "Enter book ISBN: ";
        getline(cin, ISBN);

        for (auto &book : books) {
            if (book.ISBN == ISBN && book.isAvailable) {
                book.isAvailable = false;

                time_t now = time(0);
                tm now_tm;
                localtime_r(&now, &now_tm);
                tm dueDate = addDaysToDate(now_tm, 7); // 1 week from now

                borrowers.push_back({borrowerName, borrowerID, ISBN, dueDate});
                cout << "Book checked out successfully. Due date: "
                     << (dueDate.tm_mon + 1) << '/' << dueDate.tm_mday << '/' << (dueDate.tm_year + 1900) << endl;
                cout <<"Fine after Due Date Rs. 5 per day\n";
                return;
            }
        }
        cout << "Book not available or invalid ISBN." << endl;
    }

    void returnBook() {
        string ISBN;
        cout << "Enter book ISBN to return: ";
        cin.ignore();
        getline(cin, ISBN);

        for (auto it = borrowers.begin(); it != borrowers.end(); ++it) {
            if (it->borrowedISBN == ISBN) {
                time_t now = time(0);
                tm now_tm;
                localtime_r(&now, &now_tm);

                time_t dueDate_seconds = mktime(&it->dueDate);
                time_t now_seconds = mktime(&now_tm);
                if (now_seconds > dueDate_seconds) {
                    double fine = difftime(now_seconds, dueDate_seconds) / (24 * 60 * 60) * 5.0; // ₹5 per day overdue
                    cout << "Book is overdue. Fine: ₹" << fine << endl;
                }
                updateBookStatus(ISBN, true);
                borrowers.erase(it); // Erase the borrower
                cout << "\n\t\tBOOK RETURNED SUCCESSFULLY.\n" << endl;
                return;
            }
        }
        cout << "\nInvalid ISBN or book not checked out." << endl;
    }

private:
    vector<Book> books;
    vector<Borrower> borrowers;

    void searchByTitle(const string &title) {
        for (const auto &book : books) {
            if (book.title.find(title) != string::npos) {
                displayBookInfo(book);
            }
        }
    }

    void searchByAuthor(const string &author) {
        for (const auto &book : books) {
            if (book.author.find(author) != string::npos) {
                displayBookInfo(book);
            }
        }
    }

    void searchByISBN(const string &ISBN) {
        for (const auto &book : books) {
            if (book.ISBN == ISBN) {
                displayBookInfo(book);
            }
        }
    }

    void displayBookInfo(const Book &book) {
        cout << "\nTitle: " << book.title << ", Author: " << book.author
             << ", ISBN: " << book.ISBN << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
    }

    void updateBookStatus(const string &ISBN, bool isAvailable) {
        for (auto &book : books) {
            if (book.ISBN == ISBN) {
                book.isAvailable = isAvailable;
                return;
            }
        }
    }
};

// Display the menu options to the user
void showMenu() {
    cout << "\t\t1. Add Book" << endl;
    cout << "\t\t2. Search Book" << endl;
    cout << "\t\t3. Checkout Book" << endl;
    cout << "\t\t4. Return Book" << endl;
    cout << "\t\t5. Exit" << endl;
    cout << "\t\tEnter your choice: ";
}

int main() {
    LibrarySystem librarySystem;
    int choice;
    string title, author, ISBN;

    cout << "\n\t\t=====LIBRARY MANAGEMENT SYSTEM=====" << endl;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ISBN: ";
                getline(cin, ISBN);
                librarySystem.addBook(title, author, ISBN);
                cout << "\n\t\tBOOK ADDED SUCCESSFULLY.\n" << endl;
                break;
            case 2:
                librarySystem.searchBook();
                break;
            case 3:
                librarySystem.checkoutBook();
                break;
            case 4:
                librarySystem.returnBook();
                break;
            case 5:
                cout << "\n\t\tExiting the program." << endl;
                return 0;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    }

    return 0;
}