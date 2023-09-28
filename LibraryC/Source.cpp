#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int number;
	char title[30];
	char author[25];
	float price;
}book;

void addBook(book* libptr, int size);
void displayBook(book* libptr, int size);
void editBook(book* libptr, int size);
void saveBook(book* libptr, int size);
FILE* fp;

void main() {
	//Initialization
	char filename[20], password[20], correctPassword[20];
	book* library;
	FILE* v;
	int libSize = 0, option = -1, createOrLoad, login, succesfulLogin = 0, numinputs = 0;


	do {
		printf(" = LOGIN = \n 1. Log in as User\n 2. Log in as Admin\n * Enter selection: ");
		scanf("%d", &login);

		if (login != 2 && login != 1)
			printf(" * Invalid selection!\n\n");

		if (login == 2)
		{
			v = fopen("login.txt", "r");
			printf(" * Please enter admin password: ");
			scanf("%s", password);
			fscanf(v, " %s", correctPassword);
			if (strcmp(correctPassword, password) == 0) //Compare entered password to file password.
			{
				succesfulLogin = 1;
				printf(" * Password Verified. Welcome.\n\n");
			}
			else
			{
				succesfulLogin = 0;
				printf(" ! Incorrect Password.\n");
			}
			fclose(v);
		}
	} while ((login != 1) && (login != 2) && (succesfulLogin == 1));




	do {
		printf("\n = LIBRARY = \n 1. Load an existing database\n 2. Create a new database\n * Enter selection: ");
		scanf("%d", &createOrLoad);

		if (createOrLoad != 2 && createOrLoad != 1)
			printf(" * Invalid selection!\n\n");

		if (login == 1 && createOrLoad == 2)
		{
			printf(" * This option is only available for Admins!\n\n");
			createOrLoad = 0;
		}
	} while (createOrLoad != 2 && createOrLoad != 1);

	// Read from the file
	if (createOrLoad == 1)
	{
		printf(" * Enter the name of the existing database: ");
		scanf("%s", filename);
		strcat(filename, ".txt");

		fp = fopen(filename, "r");

		if (fp == NULL)
		{
			printf(" ! Invalid file, exiting...\n");
			exit(0);
		}
		else //Read the file.
		{
			fscanf(fp, "%d", &libSize);
			library = (book*)malloc(libSize * sizeof(book));
			//Read in all books from file
			for (int i = 0; i < libSize; i++)
			{
				numinputs = fscanf(fp, "%d %s %s %f", &(library + i)->number, (library + i)->title, (library + i)->author, &(library + i)->price);
			}
			fclose(fp);
			fp = fopen(filename, "w");
		}
	}

	// Write into a file
	else if (createOrLoad == 2)
	{
		printf(" * Enter the name of the new database: ");
		scanf("%s", filename);
		strcat(filename, ".txt");

		fp = fopen(filename, "w");

		printf(" * Enter the size of the library: ");
		scanf("%d", &libSize);
		library = (book*)malloc(libSize * sizeof(book));

		//Set every book number to 0 to initialize the array.
		for (int i = 0; i < libSize; i++)
			(library + i)->number = 0;

	}

	//Main Code
	do {
		printf("\n === Main Menu ===\n\n  1. Display a Book\n  2. Add a Book\n  3. Edit a Book\n  4. Save Library\n -1. Exit Menu\n\n -> Enter one of the above options: ");
		scanf("%d", &option);

		switch (option)
		{
		case(1):
			printf("\n = BOOK DISPLAY = \n");
			displayBook(library, libSize);
			break;
		case(2):
			printf("\n = ADD A BOOK = \n");
			addBook(library, libSize);
			break;
		case(3):
			if (login == 2)
			{
				printf("\n = EDIT BOOK = \n");
				editBook(library, libSize);
			}
			else
			{
				printf(" * You are not logged in as an Admin!\n");
			}
			break;
		case(4):
			printf("\n = SAVE LIBRARY = \n");
			saveBook(library, libSize);
			printf(" * Library saved to %s.\n", filename);
			break;
		case(-1):
			printf("\n -> Exiting...\n\n");
			break;
		}
	} while (option != -1);

	fclose(fp);
}

//Prompts user to enter the details of the book and adds it to the first empty space in the array.
void addBook(book* libptr, int size)
{
	int newNum;

	do {
		printf(" -> Please enter the book number of the new book (cannot be 0): ");
		scanf("%d", &newNum);

		if (newNum == 0)
			printf(" -> Book Number cannot be zero!\n");
	} while (newNum == 0);

	for (int i = 0; i < size; i++)
	{
		if ((libptr + i)->number == 0)
		{
			(libptr + i)->number = newNum;

			printf(" -> Please enter the title of the new book: ");
			scanf("%s", (libptr + i)->title);

			printf(" -> Please enter the author of the new book: ");
			scanf("%s", (libptr + i)->author);

			printf(" -> Please enter the price of the new book: ");
			scanf("%f", &(libptr + i)->price);

			printf(" -> Book added at position %d!\n\n", i);

			return;
		}
	}
	printf(" -> [ERROR] No space remaining in array! Book could not be added!\n\n");
}

//Prompts user to enter a number and searches for & displays the corresponding book.
void displayBook(book* libptr, int size)
{
	int search;
	int booksFound = 0;
	printf(" -> Enter book number you'd like to search for: ");
	scanf("%d", &search);

	//Find and display from input
	for (int i = 0; i < size; i++)
	{
		if ((libptr + i)->number == search)
		{
			printf("\n == BOOK FOUND AT POSITION %d ==\n", i);
			printf(" -> Book Number: %d\n -> Book Name: %s\n -> Book Author: %s\n -> Book Price: %.2f\n\n",
				(libptr + i)->number, (libptr + i)->title, (libptr + i)->author, (libptr + i)->price);
			booksFound++;
		}
	}

	if (booksFound == 0)
		printf("\n == NO BOOKS FOUND WITH NUMBER %d ==\n", search);
}

//user enter a number and searches/edits the corresponding book's price.
void editBook(book* libptr, int size)
{
	int editnum;

	printf(" -> Enter the book number of the book you would like to edit: ");
	scanf("%d", &editnum);

	//Find book
	for (int i = 0; i < size; i++)
	{
		if ((libptr + i)->number == editnum)
		{
			//Book edit
			printf(" -> What should the new price of book %d (%s) be?: ", (libptr + i)->number, (libptr + i)->title);
			scanf("%f", &(libptr + i)->price);
			printf(" -> New price of book %d is %.2f!\n\n", (libptr + i)->number, (libptr + i)->price);
		}
	}
}

//Saves the book details
void saveBook(book* libptr, int size)
{
	fprintf(fp, "%d\n", size);

	for (int i = 0; i < size; i++)
	{
		if ((libptr + i)->number == 0)
		{
			fprintf(fp, "0 0 0 0\n");
		}
		else
		{
			fprintf(fp, "%d %s %s %.2f\n", (libptr + i)->number, (libptr + i)->title, (libptr + i)->author, (libptr + i)->price);
		}
	}
}