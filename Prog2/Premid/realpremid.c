#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 20
#define MAX_NAME_LEN 30

int bookCount = 0;
char books[MAX_BOOKS][MAX_NAME_LEN];
char bookAuthor[MAX_BOOKS][MAX_NAME_LEN];
float priceBook[MAX_BOOKS];

void initBook(char bookName[], char author[], float *price, char newName[], char newAuthor[], float newPrice);
void addBook(char bookName[], char author[], float price);
void viewBooks();
void searchBook(char name[]);
void deleteBook(char name[]);
void updateBook(char name[], char newName[], char newAuthor[], float newPrice);

int main()
{
    char bookName[MAX_NAME_LEN];
    char author[MAX_NAME_LEN];
    float price;

    initBook(bookName, author, &price, "Chronicles of Ivan Jayme", "Ivan Jayme", 500);
    addBook(bookName, author, price);
    viewBooks();

    searchBook("OTIN");
    searchBook("Chronicles of Ivan Jayme");

    updateBook("Chronicles of Ivan Jayme", "Adventure time", "GwapoJem", 10200);
    viewBooks();

    deleteBook("OTIN");
    deleteBook("Chronicles of Ivan Jayme");
    viewBooks();

    return 0;
}

void initBook(char bookName[], char author[], float *price, char newName[], char newAuthor[], float newPrice)
{
    strcpy(bookName, newName);
    strcpy(author, newAuthor);
    *price = newPrice;
}

void addBook(char bookName[], char author[], float price)
{
    if (bookCount >= MAX_BOOKS)
    {
        printf("Cannot add anymore books!");
        exit(1);
    }
    strcpy(books[bookCount], bookName);
    strcpy(bookAuthor[bookCount], author);

    if (price > 5000)
    {
        printf("Book %s is too expensive! Make sure it is lower than 5000\n", bookName);
        exit(1);
    }

    priceBook[bookCount] = price;

    bookCount++;

    printf("Book %s has been added.\n", bookName);
}

void viewBooks()
{
    if (bookCount == 0)
    {
        printf("There are no books in the inventory.");
        return;
    }
    for (int i = 0; i < bookCount; ++i)
    {
        printf("Book Title: %s | Book Author: %s | Price: %.2f.\n\n", books[i], bookAuthor[i], priceBook[i]);
    }
}

void searchBook(char name[])
{
    if (bookCount >= MAX_BOOKS)
    {
        printf("Cannot add anymore books!");
        exit(1);
    }
    for (int i = 0; i < bookCount; ++i)
    {
        printf("Searching for Book %s...\n", name);
        if (strcmp(books[i], name) == 0)
        {
            printf("BOOK FOUND!\n", name);
            printf("Book Title: %s | Book Author: %s | Price: %.2f.\n\n", books[i], bookAuthor[i], priceBook[i]);
        }
        else
        {
            printf("Book cannot be searched...\n\n");
        }
    }
}

void deleteBook(char name[])
{
    if (bookCount >= MAX_BOOKS)
    {
        printf("Cannot add anymore books!");
        exit(1);
    }
    for (int i = 0; i < bookCount; ++i)
    {
        printf("Deleteing %s...\n", name);
        if (strcmp(books[i], name) == 0)
        {
            strcpy(books[i], books[i + 1]);
            strcpy(bookAuthor[i], bookAuthor[i + 1]);
            priceBook[i] = priceBook[i + 1];
            bookCount--;
            printf("Successfully deleted %s\n", name);
            return;
        }
        else
        {
            printf("Book does not exist in the inventory.\n\n");
        }
    }
}
void updateBook(char name[], char newName[], char newAuthor[], float newPrice)
{
    if (bookCount >= MAX_BOOKS)
    {
        printf("Cannot add anymore books!");
        exit(1);
    }
    for (int i = 0; i < bookCount; ++i)
    {
        printf("Updating %s...\n", name);
        if (strcmp(books[i], name) == 0)
        {
            if (newPrice <= 5000)
            {
                strcpy(books[i], newName);
                strcpy(bookAuthor[i], newAuthor);
                priceBook[i] = newPrice;
                printf("Book successfully updated...\n\n");
                return;
            }
            else
            {
                printf("Book is too expensive cannot update...\n");
                return;
            }
        }
        else
        {
            printf("Book %s cannot be updated...", name);
            return;
        }
    }
}