#include "lib.h"
void addStudent(Student students[], int *count)
{
    printf("Enter student ID: ");
    scanf("%d", &students[*count].id);
    printf("Enter student name: ");
    scanf(" %[^\n]", students[*count].name);
    printf("Enter course: ");
    scanf(" %[^\n]", students[*count].course);
    printf("Enter grade: ");
    scanf("%f", &students[*count].grade);
    (*count)++;
    printf("Student added successfully!\n");
}

void viewStudents(Student students[], int count)
{
    if (count == 0)
    {
        printf("\nNo records to display.\n");
        return;
    }
    printf("\nStudent Records:\n");
    for (int i = 0; i < count; i++)
    {
        printf("ID: %d, Name: %s, Course: %s, Grade: %.2f\n",
               students[i].id, students[i].name, students[i].course, students[i].grade);
    }
}

void searchStudent(Student students[], int count)
{
    int id, found = 0;
    printf("Enter student id to search: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            printf("Student found: id: %d, Name: %s, Course: %s, Grade: %.2f\n", students[i].id, students[i].name, students[i].course, students[i].grade);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Student not found.\n");
    }
}

void deleteStudent(Student students[], int *count)
{
    int id, found = 0;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < *count; i++)
    {
        if (students[i].id == id)
        {
            for (int j = i; j < *count - 1; j++)
            {
                students[j] = students[j + 1];
            }
            (*count)--;
            found = 1;
            printf("Student deleted successfully!\n");
            break;
        }
    }
    if (!found)
    {
        printf("Student not found.\n");
    }
}

void updateStudent(Student students[], int count)
{
    int id, found = 0;
    printf("Enter student ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            printf("Enter new name: ");
            scanf(" %[^\n]", students[i].name);
            printf("Enter new course: ");
            scanf(" %[^\n]", students[i].course);
            printf("Enter new grade: ");
            scanf("%f", &students[i].grade);
            found = 1;
            printf("Student record updated successfully!\n");
            break;
        }
    }
    if (!found)
        printf("Student not found.\n");
}

void saveToFile(Student students[], int count)
{
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
    printf("Data saved successfully!\n");
}

void loadFromFile(Student students[], int *count)
{
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL)
    {
        printf("No data file found, starting fresh.\n");
        return;
    }
    fread(count, sizeof(int), 1, file);
    fread(students, sizeof(Student), *count, file);
    fclose(file);
    printf("Data loaded successfully!\n");
}

int main()
{
    Student students[Max];
    int count = 0;
    int choice;

    loadFromFile(students, &count);

    while (1)
    {
        printf("\nStudent Record System\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent(students, &count);
            break;
        case 2:
            viewStudents(students, count);
            break;
        case 3:
            searchStudent(students, count);
            break;
        case 4:
            deleteStudent(students, &count);
            break;
        case 5:
            updateStudent(students, count);
            break;
        case 6:
            saveToFile(students, count);
            exit(0);
        default:
            printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}
