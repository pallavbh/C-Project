# Student Management & Attendance System

A C console application for managing student records and daily attendance.
This project was developed as a first-semester assignment for the College of Information Technology and Engineering.

## Authors
- Pallav Bhattarai
- Aayush Timalsina
- Dipesh Dahal

## Project Overview
This program stores student details in a text file and provides a simple menu-driven interface to:
- add new student records
- view all stored records
- search for a student by roll number
- delete a student record
- take daily attendance with sequential roll call

## Features
- File-based storage using `students.txt`
- Student record structure with roll number, name, marks, attendance count, and total class days
- Duplicate roll number validation on insertion
- Attendance percentage display
- Interactive console menu

## Files
- `StudentManagementSys.c` - main C source file
- `students.txt` - data file used to persist student records

## Requirements
- C compiler such as `gcc` or `clang`
- Windows command prompt or any terminal supporting compiled executables

## Build Instructions
Open a terminal in the project folder and run:

```bash
gcc StudentManagementSys.c -o StudentManagementSys
```

If you are using MinGW on Windows, the same command applies.

## Run Instructions
After building, run the program from the terminal:

```bash
./StudentManagementSys
```

or on Windows:

```bash
StudentManagementSys.exe
```

## Usage
1. Choose an option from the menu.
2. Add new students by entering roll number, full name, and marks.
3. View all student records to check attendance and stored details.
4. Search a student using roll number.
5. Delete a record if needed.
6. Use "Daily Roll Call" to mark each listed student as present or absent.

## Future Plans
1. `updateRecord()` - Change a student’s roll number, name, or marks.
2. `calculateAttendanceReport()` - Show attendance percentages and list students below a target.
3. `sortRecords()` - Order students by roll, name, marks, or attendance.
4. `backupData()` - Save a copy of `students.txt` before big changes.
5. `importFromCsv()` / `exportToCsv()` - Read and write student data in CSV files.
6. `bulkAddStudents()` - Add many students at once.
7. `viewAbsentStudents()` - See only students who were absent in the last roll call.
8. `resetAttendance()` - Set attendance counters back to zero for a new term.
9. `viewTopStudents()` - Show the highest-scoring students.
10. `secureAccess()` - Add a simple password to protect the menu.
11. `useGUI()` - Add a graphical interface instead of the console menu.
12. `useDynamicStorage()` - Replace the fixed 100-student limit with dynamic lists.
13. `validateInput()` - Check typed input for mistakes before saving it.
14. `safeSaveWithTempFile()` - Write to a temporary file first, then rename it after success.
15. `advancedSearch()` - Allow partial name matching and case-insensitive search.

## Notes
- `students.txt` is created automatically when a new student record is added.
- Attendance is updated for all students during each roll-call session.
- `marks` are stored as floating-point values with two decimal precision.

## License
This project is a college assignment and can be modified for learning purposes.

