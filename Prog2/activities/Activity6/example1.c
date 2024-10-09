#include <stdio.h>
#include <string.h>

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
}

void updateStudent(Student students[], int index, const char *newName, int newAge)
{
strcpy(students[index].name, newName); 
students[index].age = newAge; 
}

void deleteStudent(Student students[], int *size, int index)
{
for (int i = index; i < *size - 1; i++)
{ 
students[i] = students[i + 1]; 
}
(*size)--; 
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
    scanf("%s", students[i].age);
    createStudent(students, i, students[i].name, students[i].age); 
}
printf("After Adding Students:\n");
readStudents(students, size);

while(1){
    printf("Student Management...\n");
    printf("1. Update student by index.\n");
    printf("2. Delete Student by index.\n");
    printf("3. Read/Display students.\n");
    printf("4. Exit.\n");
}



updateStudent(students, 1, "Bobby", 23); 
printf("\nAfter Updating Bob's details:\n");
readStudents(students, size);

deleteStudent(students, &size, 0); 
printf("\nAfter Deleting Alice:\n");
readStudents(students, size);
return 0;
}
