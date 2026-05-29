# Student Management & Attendance System

A compact C console application designed for automated student record management and daily attendance tracking. This project was developed as a BCA-IT 1st-semester academic assignment.

## 📋 Project Overview

This system acts as a digital replacement for traditional paper registers. It uses file-based storage (`students.txt`) to maintain persistent data across sessions, allowing for CRUD (Create, Read, Update, Delete) operations on student records and a sequential roll-call system.

## 🛠️ Data Architecture

The system organizes information using a structured data block:

```c
typedef struct {
    int roll;            // Unique identification index
    char name[50];       // Student name
    float marks;         // Academic performance
    int attended_days;   // Presence counter
    int total_days;      // Total lectures held
} Student;
```

## � Files Structure

- `StudentManagementSys.c` - Core implementation with all functions.
- `students.txt` - Persistent database file (tab-separated format).
  - Format: `roll\tname\tmarks\tattended_days\ttotal_days`
  - Example: `101\tJohn Doe\t85.5\t20\t22`

## 🧭 Program Menu

The system provides these options:

1. **Add New Student** - Register a new student with validation for duplicate roll numbers.
2. **View All Students** - Display all records in a formatted table with attendance percentages.
3. **Search Student** - Look up a student by roll number.
4. **Delete Student Record** - Remove a student and rewrite the file.
5. **Take Daily Roll Call** - Mark attendance for all students and update the file.
6. **Exit** - Close the program.

## �🚀 Key Features

- **Duplicate Prevention:** Validates roll numbers during registration to ensure uniqueness.
- **Persistent Storage:** Uses tab-separated values in `students.txt` for reliable data retention.
- **Dynamic Metrics:** Automatically calculates attendance percentages with division-by-zero protection.
- **Interactive UI:** A user-friendly switch-case dashboard for navigation.

## 🏗️ System Limitations

- **Fixed Capacity:** Currently hardcoded for a maximum of 100 students due to static array allocation.
- **Write Cycle Risks:** Overwrites the data file entirely during updates; a power failure during the write-cycle could potentially corrupt the file.
- **Input Sensitivity:** Standard `scanf` implementation lacks deep error trapping for non-integer inputs.
- **Case Sensitivity:** Search functions perform exact string matching, requiring precise casing.

## 🔮 Future Development Roadmap

1. **Edit Student Record:** Allow updating student name and marks without deletion/re-entry.
2. **Generate Attendance Report:** Export list of students with low attendance for follow-up.
3. **Dynamic Memory Allocation:** Implement Linked Lists or `realloc()` to move away from the 100-record cap.
4. **Safe File Handling:** Implement temporary staging files (`temp.txt`) to protect against data loss during write cycles.
5. **Enhanced Search:** Implement case-insensitive logic and partial name matching.

## 🛠️ Build & Run

### Compilation

```bash
gcc StudentManagementSys.c -o StudentManagementSys
```

### Execution

- **Windows:** `StudentManagementSys.exe`
- **Linux/macOS:** `./StudentManagementSys`

## 🌐 Repository

https://github.com/pallavbh/C-Project

## 👨‍💻 Authors

- Pallav Bhattarai
- Aayush Timalsina
- Dipesh Dahal

## ⚖️ License

This project is open-source and was created as an assignment for college coursework. It is free to modify and reference for educational purposes.