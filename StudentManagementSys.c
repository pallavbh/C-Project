/*
    Date: 2026-05-15 AD { 2083-02-01 BS }
    Done By: Pallav Bhattarai, Aayush Timalsina, Dipesh Dahal
    Course: BCA-IT { 1st Semester }
    Project: Student Management & Attendance System
*/

/* 
    **Student Management & Attendance System**
    A simple C project to manage student details and record daily attendance.
    Features: Registering entries, viewing records, searching, dropping records, 
    and a sequential batch roll-call system. Uses Structures and File handling.
*/

#include <stdio.h>              // For standard screen input and output
#include <stdlib.h>             // For exit() and system operations
#include <string.h>             // For handling names/strings

// Structure template for single student record
typedef struct {
    int roll;
    char name[50];
    float marks;
    int attended_days;          // Classes attended
    int total_days;             // Total classes held
} Student;

// Main operational functions
void addRecord();
void displayRecords();
void searchRecord();
void markAttendance();          
void deleteRecord();

int main() {
    int choice;

    // Continuous user interactive dashboard menu
    while(1) {  
        printf("\n--- STUDENT MANAGEMENT & ATTENDANCE SYSTEM ---");
        printf("\n1. Add New Student");
        printf("\n2. View All Students");
        printf("\n3. Search Student");
        printf("\n4. Delete Student Record");
        printf("\n5. Take Daily Roll Call (Attendance)"); 
        printf("\n6. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addRecord(); break;
            case 2: displayRecords(); break;
            case 3: searchRecord(); break;
            case 4: deleteRecord(); break;
            case 5: markAttendance(); break; 
            case 6: printf("\nExiting system...\n"); exit(0);
            default: printf("\nInvalid option! Try again.");
        }
    }
    return 0;
}

// 1. Adds a new student record to the file
void addRecord() {
    FILE *fp;
    Student s, temp;
    int rollExists = 0;

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    // Read file to check if roll number is already taken
    fp = fopen("students.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d\t%[^\t]\t%f\t%d\t%d\n", &temp.roll, temp.name, &temp.marks, &temp.attended_days, &temp.total_days) != EOF) {
            if (temp.roll == s.roll) {
                rollExists = 1; // Duplicate match found
                break;
            }
        }
        fclose(fp);
    }

    // Stop execution if roll number is a duplicate
    if (rollExists == 1) {
        printf("Error: Roll Number %d already exists! Entry blocked.\n", s.roll);
        return;
    }

    // Open file in Append ("a") mode to save new entry safely
    fp = fopen("students.txt", "a");  
    if (fp == NULL) {       
        printf("Error: Could not open file.");
        return;
    }

    printf("Enter Full Name: ");
    scanf(" %[^\n]s", s.name);  // Reads full string including white spaces
    
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    // Initialize clean slate counters for new student tracking
    s.attended_days = 0;
    s.total_days = 0;

    // Save fields using clean Tab (\t) separations
    fprintf(fp, "%d\t%s\t%.2f\t%d\t%d\n", s.roll, s.name, s.marks, s.attended_days, s.total_days);
    fclose(fp);

    printf("Record saved successfully!\n");
}

// 2. Prints formatted table of all students from the file
void displayRecords() {
    FILE *fp = fopen("students.txt", "r");
    Student s;
    float attendance_percentage = 0.0;

    if (fp == NULL) {
        printf("\nNo records found. Add a student first!");
        return;
    }

    // Display aligned column layout labels
    printf("\n%-7s %-20s %-7s %-12s %%", "Roll", "Name", "Marks", "Attendance");
    printf("\n-----------------------------------------------------------");

    // Read lines consecutively up to the end of the file
    while (fscanf(fp, "%d\t%[^\t]\t%f\t%d\t%d\n", &s.roll, s.name, &s.marks, &s.attended_days, &s.total_days) != EOF) {
        // Prevent math crash (division by zero) if no classes have run yet
        if (s.total_days > 0) {
            attendance_percentage = ((float)s.attended_days / s.total_days) * 100.0;
        } else {
            attendance_percentage = 0.0;
        }

        printf("\n%-7d %-20s %-7.1f %d/%-9d %.1f%%", s.roll, s.name, s.marks, s.attended_days, s.total_days, attendance_percentage);
    }
    fclose(fp);
    printf("\n");
}

// 3. Search a single record using Roll Number lookup boundaries
void searchRecord() {
    FILE *fp = fopen("students.txt", "r");
    Student s;
    int targetRoll, found = 0;

    if (fp == NULL) {
        printf("\nNo records found.");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &targetRoll);

    // Scan lines to check for matching targets
    while (fscanf(fp, "%d\t%[^\t]\t%f\t%d\t%d\n", &s.roll, s.name, &s.marks, &s.attended_days, &s.total_days) != EOF) {
        if (s.roll == targetRoll) {
            printf("\nStudent Found!");
            printf("\nRoll: %d\nName: %s\nMarks: %.1f\nAttendance: %d out of %d classes\n", s.roll, s.name, s.marks, s.attended_days, s.total_days);
            found = 1;
            break;              // Drop lookup loop early once found
        }
    }

    if (!found) {
        printf("\nStudent with Roll %d not found.\n", targetRoll);
    }
    fclose(fp);
}

// 4. Batch Roll Call: Loops through all students sequentially to log tracking metrics
void markAttendance() {
    FILE *fp;
    Student list[100];          // Buffer array cache to hold entries in RAM memory
    int count = 0, status;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("\nNo student database found. Add records first!\n");
        return;
    }

    // Step A: Load entire document lines inside storage caching array
    while (fscanf(fp, "%d\t%[^\t]\t%f\t%d\t%d\n", &list[count].roll, list[count].name, &list[count].marks, &list[count].attended_days, &list[count].total_days) != EOF) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("\nNo students registered yet.\n");
        return;
    }

    printf("\n--- DAILY ATTENDANCE ROLL CALL ---");
    printf("\nEnter (1) for Present | (0) for Absent\n");

    // Step B: Loop through every loaded student row for interactive verification
    for (int i = 0; i < count; i++) {
        list[i].total_days += 1; // Increment school working days conducted count

        printf("Roll %d: %-20s -> ", list[i].roll, list[i].name);
        scanf("%d", &status);

        if (status == 1) {
            list[i].attended_days += 1; // Increment specific presence counter tracker
        }
    }

    // Step C: Re-open file in Write ("w") mode to completely overwrite with updated values
    fp = fopen("students.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d\t%s\t%.2f\t%d\t%d\n", list[i].roll, list[i].name, list[i].marks, list[i].attended_days, list[i].total_days);
    }
    fclose(fp);

    printf("\nAttendance sheet saved successfully!\n");
}

// 5. Deletes a record by rewriting the file and skipping the targeted item
void deleteRecord() {
    FILE *fp;
    Student list[100];          // Local processing cache placeholder layout
    int count = 0, targetRoll, found = 0;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("\nNo records found to delete.");
        return;
    }

    // Step A: Load current file structure cleanly inside system memory
    while (fscanf(fp, "%d\t%[^\t]\t%f\t%d\t%d\n", &list[count].roll, list[count].name, &list[count].marks, &list[count].attended_days, &list[count].total_days) != EOF) {
        count++;
    }
    fclose(fp);

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &targetRoll);

    // Step B: Overwrite file back from scratch using Write ("w") rules, filtering target
    fp = fopen("students.txt", "w"); 
    for (int i = 0; i < count; i++) {
        if (list[i].roll == targetRoll) {
            found = 1;          // Flag matching element dropped safely
        } else {
            // Rewrite data of non-matching structural items safely back down
            fprintf(fp, "%d\t%s\t%.2f\t%d\t%d\n", list[i].roll, list[i].name, list[i].marks, list[i].attended_days, list[i].total_days);
        }
    }
    fclose(fp);

    if (found) {
        printf("Record deleted successfully!\n");
    } else {
        printf("Record with Roll %d not found.\n", targetRoll);
    }
}



/* 
    ============================================================================
    💡 NOTE: SCALABILITY & MEMORY ARCHITECTURE
    ============================================================================
    Current Setup: 
    - Uses a fixed static array buffer: "Student list[100];" 
    - Perfect for small, predictable academic collections.

    Real-World / Production Scalability Alternative:
    To handle thousands of records without hardcoded limits, the architecture 
    can be upgraded from Stack Memory to Dynamic Heap Allocation using pointers:

    * DYNAMIC POINTER LAYOUT: 
      Replace the fixed array with a dynamic pointer reference: 
      "Student *list = NULL;"

    * INITIAL HEAP ALLOCATION: 
      Allocate a flexible starting block in runtime memory:
      "list = (Student *)malloc(initial_capacity * sizeof(Student));"

    * AUTO-SCALING OVERFLOW PROTECTION: 
      Use "realloc()" to dynamically double the available RAM space 
      the exact moment the loop count hits the capacity threshold.

    * CLEAN RESOURCE CLEANUP: 
      Use "free(list);" before exiting functions to release memory back 
      to the OS and guarantee zero system memory leaks.

    Benefit: Eliminates buffer overflow risks and allows the file-scanning 
    engine to scale seamlessly to any database size.
    ============================================================================
*/