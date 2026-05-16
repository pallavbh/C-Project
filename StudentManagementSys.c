/*
    Date: 2026-05-15
    Author: Pallav Bhattarai
    BCA-IT 1st Semester
    Registration No: 024-3-2-07345-2025
    Symbol Number: 312794
*/

/* 
            **Student Management System**
    This program implements a simple student management system in C.
    It allows users to add, display, search, and delete student records.
    Each student record consists of a name, roll number, and marks.
    The program uses a structure, switchCase, FileHandling .
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Using typedef struct to define a Student structure with alias 'Student'
typedef struct {
    char name[50];
    int roll;
    float marks;
} Student;

//prototype declarations
void addRecord();
void displayRecords();
void searchRecord();
void deleteRecord();
