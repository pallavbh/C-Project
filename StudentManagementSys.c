/*
    Date: 2026-05-15 AD { 2083-02-01 BS }
    Author: Pallav Bhattarai
            Aayush Timalsina
            Dipesh Dahal
    Course: BCA-IT { 1st Semester }
    
*/
// Add Students Attendance System in C
/* 
            **Student Management System**
    This program implements a simple student management system in C.
    It allows users to add, display, search, and delete student records.
    Each student record consists of a name, roll number, and marks.
    The program uses a structure, switchCase, FileHandling .
*/


#include <stdio.h>              // For printf() and scanf()
#include <stdlib.h>            // For exit() and file handling functions
#include <string.h>           // For string handling functions

//Alias for the student structure using typedef
typedef struct {
    int roll;
    char name[50];
    float marks;
} Student;

// Function declarations for the student management operations
void addRecord();
void displayRecords();
void searchRecord();
void deleteRecord();

int main() {
    int choice;

    // Infinite loop to keep the program running until the user chooses to exit
    while(1) {  
        printf("\n--- STUDENT MANAGEMENT SYSTEM ---");
        printf("\n1. Add Student");
        printf("\n2. View All Students");
        printf("\n3. Search Student");
        printf("\n4. Delete Student");
        printf("\n5. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addRecord(); break;
            case 2: displayRecords(); break;
            case 3: searchRecord(); break;
            case 4: deleteRecord(); break;
            case 5: exit(0);
            default: printf("\nInvalid option!");
        }
    }
    return 0;
}

void addRecord() {

    //Open file in append mode to add new records without overwriting existing ones
    FILE *fp = fopen("students.txt", "a");  
    Student s;

    if (fp == NULL) {       //Check if the file was opened successfully
        printf("Error: Could not open file.");
        return;
    }

    printf("\nEnter Roll: ");
    scanf("%d", &s.roll);
    
    printf("Enter Full Name: ");
    scanf(" %[^\n]s", s.name);          // %[^\n] allows spaces in name
    
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    // Save data separated by Tabs (\t)
    fprintf(fp, "%d\t%s\t%.2f\n", s.roll, s.name, s.marks);

    // Close file to save data to disk
    fclose(fp);
    printf("Record saved successfully!\n");
}

void displayRecords() {
    // Open file in Read mode
    FILE *fp = fopen("students.txt", "r");
    Student s;

    // Check if file exists
    if (fp == NULL) {
        printf("\nNo records found. Add a record first!");
        return;
    }

    // Print header for the records
    printf("\n%-10s %-20s %-10s", "Roll", "Name", "Marks");
    printf("\n-------------------------------------------");

    // Reading with %[^\t] tells fscanf to read the name until it hits a Tab character
    while (fscanf(fp, "%d\t%[^\t]\t%f\n", &s.roll, s.name, &s.marks) != EOF) {
        printf("\n%-10d %-20s %-10.2f", s.roll, s.name, s.marks);
    }

    // Close file after reading
    fclose(fp);
    printf("\n");
}

void searchRecord() {

    // Open file in Read mode
    FILE *fp = fopen("students.txt", "r");
    Student s;
    int targetRoll, found = 0;      // found acts as a true/false flag

    if (fp == NULL) {
        printf("\nNo records available to search.");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &targetRoll);

    // Scan file line-by-line
    while (fscanf(fp, "%d\t%[^\t]\t%f\n", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll == targetRoll) {
            printf("\nStudent Found!");
            printf("\nRoll: %d\nName: %s\nMarks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;      // Mark as found
            break;          // Stop searching loop
        }
    }

    if (!found) {
        printf("\nStudent with Roll %d not found.\n", targetRoll);
    }

    fclose(fp);
}

void deleteRecord() {
    FILE *fp, *ft;      // fp = original file, ft = temporary file
    Student s;
    int targetRoll, found = 0;

    fp = fopen("students.txt", "r");    // Open original to read
    if (fp == NULL) {
        printf("\nNo records found.");
        return;
    }

    ft = fopen("temp.txt", "w");    // Create temporary file to write

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &targetRoll);

    // Read all records
    while (fscanf(fp, "%d\t%[^\t]\t%f\n", &s.roll, s.name, &s.marks) != EOF) {
        if (s.roll == targetRoll) {

            // Mark found, skip copying (deletes it)
            found = 1;
            printf("\nRecord for Roll %d deleted successfully!", targetRoll);
        } else {

            // Copy non-matching records to temp file
            fprintf(ft, "%d\t%s\t%.2f\n", s.roll, s.name, s.marks);
        }
    }

    fclose(fp);     // Close source
    fclose(ft);     // Close temp

    if (!found) {
        printf("\nRecord not found. Nothing deleted.");
        remove("temp.txt");     // Delete empty temp file
    } else {
        remove("students.txt");     // Wipe out old file
        rename("temp.txt", "students.txt"); // Rename temp to original name
    }
}