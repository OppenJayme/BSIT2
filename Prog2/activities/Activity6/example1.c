#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
char name[50]; 
int age; 
} Student;

void createStudent(Student students[], int size, const char *name, int age)
{
strcpy(students[size].name, name);
students[size].age = age; 
}
void readStudents(Student students[], int size)
{
for (int i = 0; i < size; i++)
{

printf("Student %d: Name = %s, Age = %d\n", i + 1, students[i].name,
students[i].age);
}
printf("\n");
}

void updateStudent(Student students[], int index, const char *newName, int newAge)
{
strcpy(students[index].name, newName); 
students[index].age = newAge; 
printf("updated successfully\n");
}

void deleteStudent(Student students[], int *size, int index)
{
for (int i = index; i < *size - 1; i++)
{ 
students[i] = students[i + 1]; 
}
(*size)--; 
printf("Deleted successfully\n");
}


int main()
{
Student students[10]; 
int size = 0; 
// Create students (Add)
int choice;

printf("Enter number of students: ");
scanf("%d", &size);

for (int i = 0; i < size; ++i){
    printf("Enter name of student %d: ", i+1);
    scanf("%s", students[i].name);
    printf("Enter age of student %d: ", i+1);
    scanf("%d", &students[i].age);
    createStudent(students, i, students[i].name, students[i].age); 
}
printf("\nAfter Adding Students:\n");
readStudents(students, size);

while(1){
    printf("\nStudent Management...\n");
    printf("1. Update student by index.\n");
    printf("2. Delete Student by index.\n");
    printf("3. Read/Display students.\n");
    printf("4. Exit.\n");
    int choice2;
    printf("Enter option: ");
    scanf("%d", &choice2);
    
    switch(choice2){
        case 1: 
            int index;
            char newName[50];
            int newAge;
            
            printf("Enter index of student: ");
            if (scanf("%d", &index) > size){
                printf("Index is invalid.\n");
            };
            printf("Enter new name of student: ");
            scanf("%s", newName);
            printf("Enter new age: ");
            scanf("%d", &newAge);
            printf("\n");
            updateStudent(students, index, newName, newAge); 
            break;
        case 2:
            int indexer;
            printf("Enter index of student to delete: ");
            if (scanf("%d", &indexer) > size){
                printf("Index is invalid.\n");
            };
            deleteStudent(students, &size, indexer); 
            
            break;
        case 3: 
            readStudents(students, size);
            break;
        case 4:
            printf("Exiting...\n");
            exit(1);
        default:
            printf("Invalid option");
            exit(1);
    }
}

return 0;
}
