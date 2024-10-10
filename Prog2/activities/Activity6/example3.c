#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char title[100];
    char author[100];
    int year;
    char isbn[20];
} Book;

Book *createBookList(int *size)
{
    *size = 0;
    Book *books = (Book *)malloc(100 * sizeof(Book));
    return books;
}

void addBook(Book *books, int *size, const char *title, const char *author, int year, const char *isbn)
{
    strcpy(books[*size].title, title);
    strcpy(books[*size].author, author);
    books[*size].year = year;
    strcpy(books[*size].isbn, isbn);
    (*size)++;
}

void readBooks(Book *books, int size)
{
    if (size == 0)
    {
        printf("No books found.\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        printf("Book %d: Title = %s, Author = %s, Year = %d, ISBN = %s\n", i + 1, books[i].title, books[i].author, books[i].year, books[i].isbn);
    }
}

int findBookByISBN(Book *books, int size, const char *isbn)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(books[i].isbn, isbn) == 0)
        {
            return i;
        }
    }
    return -1;
}

void updateBook(Book *books, int size, const char *isbn, const char *newTitle, const char *newAuthor, int newYear)
{
    int index = findBookByISBN(books, size, isbn);
    if (index != -1)
    {
        strcpy(books[index].title, newTitle);
        strcpy(books[index].author, newAuthor);
        books[index].year = newYear;
        printf("Book with ISBN %s updated successfully.\n", isbn);
    }
    else
    {
        printf("Book with ISBN %s not found.\n", isbn);
    }
}

void deleteBook(Book *books, int *size, const char *isbn)
{
    int index = findBookByISBN(books, *size, isbn);
    if (index != -1)
    {
        for (int i = index; i < *size - 1; i++)
        {
            books[i] = books[i + 1];
        }
        (*size)--;
        printf("Book with ISBN %s deleted successfully.\n", isbn);
    }
    else
    {
        printf("Book with ISBN %s not found.\n", isbn);
    }
}

int main()
{
    int size;
    Book *books = createBookList(&size);
    int choice;

    while (1)
    {
        printf("\nBOOK MANAGEMENT SYSTEM\n");
        printf("1. Add Book\n");
        printf("2. Update Book by ISBN\n");
        printf("3. Delete Book by ISBN\n");
        printf("4. View All Books\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
        {
            char title[100];
            char author[100];
            int year;
            char isbn[20];

            printf("Enter Title: ");
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = '\0';

            printf("Enter Author: ");
            fgets(author, sizeof(author), stdin);
            author[strcspn(author, "\n")] = '\0';

            printf("Enter Year: ");
            scanf("%d", &year);
            getchar();

            printf("Enter ISBN: ");
            fgets(isbn, sizeof(isbn), stdin);
            isbn[strcspn(isbn, "\n")] = '\0';

            addBook(books, &size, title, author, year, isbn);
            break;
        }
        case 2:
        {
            char isbn[20];
            char newTitle[100];
            char newAuthor[100];
            int newYear;

            printf("Enter ISBN to update: ");
            fgets(isbn, sizeof(isbn), stdin);
            isbn[strcspn(isbn, "\n")] = '\0';

            printf("Enter new Title: ");
            fgets(newTitle, sizeof(newTitle), stdin);
            newTitle[strcspn(newTitle, "\n")] = '\0';

            printf("Enter new Author: ");
            fgets(newAuthor, sizeof(newAuthor), stdin);
            newAuthor[strcspn(newAuthor, "\n")] = '\0';

            printf("Enter new Year: ");
            scanf("%d", &newYear);
            getchar();

            updateBook(books, size, isbn, newTitle, newAuthor, newYear);
            break;
        }
        case 3:
        {
            char isbn[20];
            printf("Enter ISBN to delete: ");
            fgets(isbn, sizeof(isbn), stdin);
            isbn[strcspn(isbn, "\n")] = '\0';

            deleteBook(books, &size, isbn);
            break;
        }
        case 4:
        {
            readBooks(books, size);
            break;
        }
        case 5:
        {
            printf("Exiting...\n");
            free(books);
            return 0;
        }
        default:
        {
            printf("Invalid choice. Please try again.\n");
            break;
        }
        }
    }
}