#include<bits/stdc++.h>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool is_checked_out;

    Book(int id, string title, std::string author)
        :id(id),title(title),author(author),is_checked_out(false) {}
};

class Patron {
public:
    int id;
    string name;

    Patron(int id,string name):id(id),name(name){}
};

class Library {
private:
    vector<Book> books;
    vector<Patron> patrons;

public:
    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
    }

    void addPatron(int id, string name) {
        patrons.push_back(Patron(id, name));
    }

    void displayBooks() {
        for (const auto& book : books) {
           cout<<"ID: "<<book.id<< ",Title:"<<book.title 
                      << ", Author: " <<book.author 
                      << ",Checked Out: "<<(book.is_checked_out?"Yes":"No") 
                      << endl;
        }
    }

    void checkOutBook(int bookId, int patronId) {
        for (auto& book:books) {
            if (book.id==bookId&&!book.is_checked_out) {
                book.is_checked_out=true;
                cout <<"Book ID "<<bookId<<" checked out by Patron ID "<<patronId<<endl;
                return;
            }
        }
        cout<< "Book ID "<<bookId<<" is not available for checkout."<<endl;
    }

    void returnBook(int bookId) {
        for (auto& book:books) {
            if (book.id==bookId&&book.is_checked_out) {
                book.is_checked_out=false;
                cout<< "Book ID "<<bookId<<" returned."<< endl;
                return;
            }
        }
        cout<<"Book ID "<<bookId<<" was not checked out."<< endl;
    }

    void displayPatrons() {
        for (const auto& patron : patrons) {
            cout<<"ID: "<<patron.id<<", Name: "<<patron.name<< endl;
        }
    }
};

int main() {
    Library library;

    library.addBook(1, "1980", "George Washington");
    library.addBook(2, "To Obliged a meaningful word", "Obs garden");

    library.addPatron(1, "Mary");
    library.addPatron(2, "Lopa");

    cout << "Books in the Library:"<<endl;
    library.displayBooks();

    cout << "\nPatrons in the Library:"<<endl;
    library.displayPatrons();

    cout << "\nChecking out Book ID 1 to Patron ID 1:"<<endl;
    library.checkOutBook(1, 1);

    cout << "\nBooks in the Library after checkout:"<<endl;
    library.displayBooks();

    cout << "\nReturning Book ID 1:"<<endl;
    library.returnBook(1);

    cout << "\nBooks in the Library after return:" <<endl;
    library.displayBooks();

    return 0;
}
