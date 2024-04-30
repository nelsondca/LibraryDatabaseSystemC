# LibraryC

#Purpose:
The software allows users to add books, view book details, adjust book prices, and save library data to a file, among other actions. It is designed to manage a library of books.


#Key characteristics:
Struct Definition:The program creates a book structure with the following attributes: book number, title, author, and price.

File handling: Users can load an existing database or create a new one by reading and writing book data to a text file.

User authentication: The program has a straightforward login system that distinguishes between users and administrators. Administrators have access to extra features.

Users are given a menu from which to select the following actions: show a book, add a book, edit a book, and save the library.



#Functions:
addBook(book* libptr, int size): Allows the user to add a new book to the library, providing book details.

displayBook(book* libptr, int size): Searches for a book by its number and displays its details if found.

editBook(book* libptr, int size): Edits the price of a book by specifying its number.

saveBook(book* libptr, int size): Saves the library data to a file.



#Flow:
Users can log in as either a regular user or an admin using a password.
They can choose to create a new library database or load an existing one.
Once in the main menu, users can perform various actions related to book management.



#Note:
The program uses dynamic memory allocation (malloc) to manage the array of books.
It includes basic input validation and error handling.
This program can serve as a foundation for a more extensive library management system and is a good example of file handling and menu-driven console applications in C.
