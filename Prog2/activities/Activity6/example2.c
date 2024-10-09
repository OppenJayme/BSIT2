#include <stdio.h>
#include <string.h>
#define MAX_BOOKS 100 

typedef struct {
    char title[100]; 
    char author[100]; 
    int year; 
    char isbn[20]; 
} Book;

void createBook(Book books[], int *size, const char *title, const char *author, int year, const char *isbn) {
    strcpy(books[*size].title, title); 
    strcpy(books[*size].author, author); 
    books[*size].year = year; 
    strcpy(books[*size].isbn, isbn); 
    (*size)++;
}

void readBooks(Book books[], int size) {
    for (int i = 0; i < size; i++) { 
        printf("Book %d: Title = %s, Author = %s, Year = %d, ISBN = %s\n", i + 1, books[i].title, books[i].author, books[i].year, books[i].isbn);
    }
}

int findBookByISBN(Book books[], int size, const char *isbn) {
    for (int i = 0; i < size; i++) { 
        if (strcmp(books[i].isbn, isbn) == 0) {
            return i; 
        }
    }
    return -1; 
}

void updateBookByISBN(Book books[], int size, const char *isbn, const char *newTitle, const char *newAuthor, int newYear) {
    int index = findBookByISBN(books, size, isbn); 
    if (index != -1) { 
        strcpy(books[index].title, newTitle); 
        strcpy(books[index].author, newAuthor); 
        books[index].year = newYear; 
        printf("Book with ISBN %s updated successfully.\n", isbn);
    } else {
        printf("Book with ISBN %s not found.\n", isbn);
    }
}

void deleteBookByISBN(Book books[], int *size, const char *isbn) {
    int index = findBookByISBN(books, *size, isbn); 
    if (index != -1) { 
        for (int i = index; i < *size - 1; i++) {
            books[i] = books[i + 1]; 
        }
        (*size)--; 
        printf("Book with ISBN %s deleted successfully.\n", isbn);
    } else {
        printf("Book with ISBN %s not found.\n", isbn);
    }
}

int main() {
    Book books[MAX_BOOKS]; 
    int size = 0; 
    
    while (1){
        printf("BOOK MANAGEMENT OF IVAN JAYMER FR\n");
        printf("1. Create Book.\n");
        printf("2. find book by ISBN\n");
        printf("3. Update book by ISBN\n");
        printf("4. delete book by ISBN\n");
        int choice;
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                
                break;
            
        }
    }
    createBook(books, &size, "The Great Gatsby", "F. Scott Fitzgerald", 1925, "9780743273565");
    createBook(books, &size, "To Kill a Mockingbird", "Harper Lee", 1960, "9780060935467");
    createBook(books, &size, "1984", "George Orwell", 1949, "9780451524935");
    printf("After Adding Books:\n");
    readBooks(books, size);
    updateBookByISBN(books, size, "9780060935467", "To Kill a Mockingbird (Updated)", "Harper Lee", 1961);
    printf("\nAfter Updating To Kill a Mockingbird:\n");
    readBooks(books, size);
    deleteBookByISBN(books, &size, "9780451524935");
    printf("\nAfter Deleting 1984:\n");
    readBooks(books, size);
    deleteBookByISBN(books, &size, "9789999999999");
    return 0;
}
