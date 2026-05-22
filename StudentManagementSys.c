/*
    Date: 2026-05-15 AD { 2083-02-01 BS }
    Author: Pallav Bhattarai
            Aayush Timalsina
            Dipesh Dahal
    Course: BCA-IT { 1st Semester }
    
*/
// Student Management & Attendance System in C
/* 
            **Student Management System**
    This program implements a simple student management system in C.
    It allows users to add, display, search, and delete student records.
    Each student record consists of a name, roll number, marks, and attendance.
    The program uses a structure, switchCase, FileHandling .
*/

#include <stdio.h>              // Standard Input/Output library for printf() and scanf()
#include <stdlib.h>             // Standard Library for exit() and file management functions
#include <string.h>             // String manipulation library for handling name strings

// Alias for the student structure using typedef
typedef struct {
    int roll;                   // Stores the unique ID/Roll number of the student
    char name[50];              // Character array (string) to hold the student's full name
    float marks;                // Stores total or percentage marks achieved
    float attendance;           // Stores the student's attendance percentage (0.00% to 100.00%)
} Student;

// User-defined function prototypes (tells the compiler these exist later in the file)
void addRecord();
void displayRecords();
void searchRecord();
void deleteRecord();

int main() {
    int choice;                 // Variable to store the user's menu selection

    // Infinite loop to keep the system active until option 5 (Exit) is intentionally chosen
    while(1) {  
        // Displaying User Interface Menu options
        printf("\n--- STUDENT MANAGEMENT SYSTEM ---");
        printf("\n1. Add Student & Attendance");
        printf("\n2. View All Students");
        printf("\n3. Search Student");
        printf("\n4. Delete Student");
        printf("\n5. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);   // Read user choice from console

        // Divert program execution based on user selection
        switch(choice) {
            case 1: 
                addRecord();       // Call function to insert a new student entry
                break;
            case 2: 
                displayRecords();  // Call function to print all records on screen
                break;
            case 3: 
                searchRecord();    // Call function to look up a specific roll number
                break;
            case 4: 
                deleteRecord();    // Call function to wipe a student record
                break;
            case 5: 
                printf("\nExiting system. Goodbye!\n");
                exit(0);           // Cleanly terminate the console program execution
            default: 
                printf("\nInvalid option! Please enter a number between 1 and 5.");
        }
    }
    return 0;                   // Standard return statement indicating successful execution
}

void addRecord() {
    // Open "students.txt" in Append mode ("a") to add text data safely without wiping previous entries
    FILE *fp = fopen("students.txt", "a");  
    Student s;                  // Create a local structure instance to hold user inputs

    // Safety check: Verify if the storage file can be accessed/created on disk
    if (fp == NULL) {       
        printf("Error: Could not open or create the database file.");
        return;                 // Stop execution and return to main menu
    }

    // Input collection from user console
    printf("\nEnter Roll: ");
    scanf("%d", &s.roll);
    
    printf("Enter Full Name: ");
    // " %[^\n]s" reads input text until a newline (Enter key) is encountered, allowing spaces
    scanf(" %[^\n]s", s.name);          
    
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    printf("Enter Attendance Percentage (%%): ");
    scanf("%f", &s.attendance);

    // Save structured data cleanly separated by Tabs (\t) and ending with a clear newline (\n)
    fprintf(fp, "%d\t%s\t%.2f\t%.2f\n", s.roll, s.name, s.marks, s.attendance);

    // Explicitly close file buffer to push data from temporary memory RAM directly to disk storage
    fclose(fp);
    printf("Record saved successfully!\n");
}

void displayRecords() {
    // Open "students.txt" in Read mode ("r")
    FILE *fp = fopen("students.txt", "r");
    Student s;                  // Temporary structure instance to hold data read from file

    // Safety check: Check if file doesn't exist or is empty
    if (fp == NULL) {
        printf("\nNo records found. Add a record first!");
        return;                 // Stop function execution
    }

    // Print out visual column headers safely formatted with left alignment padding (%-X)
    printf("\n%-10s %-20s %-10s %-12s", "Roll", "Name", "Marks", "Attendance");
    printf("\n-----------------------------------------------------------");

    /* 
       File Reading loop:
       - %d\t parses the roll number up to the first tab character
       - %[^\t]\t reads the string until it encounters the next tab character (keeps spaces intact)
       - %f\t%f\n parses the numeric floats up to the end of the line
       Loop runs continuously until End Of File (EOF) is flagged.
    */
    while (fscanf(fp, "%d\t%[^\t]\t%f\t%f\n", &s.roll, s.name, &s.marks, &s.attendance) != EOF) {
        // Output row formatted matching column layouts perfectly; %% renders a single % symbol
        printf("\n%-10d %-20s %-10.2f %-10.2f%%", s.roll, s.name, s.marks, s.attendance);
    }

    // Close the file buffer cleanly to release system resources
    fclose(fp);
    printf("\n");
}

void searchRecord() {
    // Open database file in Read mode
    FILE *fp = fopen("students.txt", "r");
    Student s;
    int targetRoll;             // Holds user input for target roll number lookup
    int found = 0;              // Flag variable acting as a true/false condition tracking status

    // Safety check: File absence check
    if (fp == NULL) {
        printf("\nNo records available to search.");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &targetRoll);

    // Scan database line-by-line using structured field configurations
    while (fscanf(fp, "%d\t%[^\t]\t%f\t%f\n", &s.roll, s.name, &s.marks, &s.attendance) != EOF) {
        // Match found condition logic
        if (s.roll == targetRoll) {
            printf("\nStudent Found!");
            printf("\nRoll: %d\nName: %s\nMarks: %.2f\nAttendance: %.2f%%\n", s.roll, s.name, s.marks, s.attendance);
            found = 1;          // Set status flag to true
            break;              // Immediate exit loop optimization (no need to scan remaining records)
        }
    }

    // Context handler when matching target targetRoll is completely missing
    if (!found) {
        printf("\nStudent with Roll %d not found.\n", targetRoll);
    }

    // Close open stream
    fclose(fp);
}

void deleteRecord() {
    FILE *fp;                   // File pointer pointing to the original active data document
    FILE *ft;                   // File pointer pointing to a transient placeholder staging document
    Student s;
    int targetRoll;             // Holds input roll identity flag for target removal
    int found = 0;              // State flag variable tracking deletion success status

    fp = fopen("students.txt", "r");    // Open source file to review contents line-by-line
    if (fp == NULL) {
        printf("\nNo records found.");
        return;
    }

    ft = fopen("temp.txt", "w");        // Establish/Overwrite blank temporary database to clone survivors

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &targetRoll);

    // Parse loop evaluating elements within active database
    while (fscanf(fp, "%d\t%[^\t]\t%f\t%f\n", &s.roll, s.name, &s.marks, &s.attendance) != EOF) {
        if (s.roll == targetRoll) {
            found = 1;          // Target row picked up, flag set to true, skip writing to filter out
            printf("\nRecord for Roll %d deleted successfully!", targetRoll);
        } else {
            // Write matching survivors safely over onto the temporary workspace cache
            fprintf(ft, "%d\t%s\t%.2f\t%.2f\n", s.roll, s.name, s.marks, s.attendance);
        }
    }

    // Always release system lock pointers before invoking file mutations (remove/rename)
    fclose(fp);     
    fclose(ft);     

    if (!found) {
        printf("\nRecord not found. Nothing deleted.");
        remove("temp.txt");     // Wipe clean the obsolete, untouched temporary work staging file
    } else {
        remove("students.txt"); // Erase old master version file housing the targeted item
        rename("temp.txt", "students.txt"); // Swap identity names converting temp back into standard master layout
    }
}