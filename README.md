# Student Management & Attendance System

A comprehensive C console application designed for automated student record cataloging and daily tracking metrics. This project was developed as an academic assignment for the Bachelor of Computer Applications in Information Technology (BCA-IT) program.

---

## 👨‍💻 Authors
- **Pallav Bhattarai**
- **Aayush Timalsina**
- **Dipesh Dahal**

## 📚 Academic Metadata
- **Course:** BCA-IT (1st Semester)
- **Affiliation:** Purbanchal University
- **Date:** June 2, 2026

---

## 📖 Project Overview

This system acts as a digital replacement for traditional paper classroom logs. It implements core data persistence mechanisms using localized standard structure templates and persistent flat-file tracking architectures.

### Data Structure

```c
typedef struct {
    int roll;               // Unique identification index
    char name[50];          // Full string textual identity array
    float marks;            // Academic performance point tracking
    int attended_days;      // Integer metric for registered presence
    int total_days;         // Total operational lecture instances held
} Student;
```

### ✨ Features

- **Duplicate Insertion Blocking:** Scans existing records to guarantee unique Roll Number allocation.
- **Persistent Flat-File Storage:** Utilizes tab-separated values (`\t`) inside students.txt.
- **Dynamic Percentage Calculations:** Computes real-time presence metrics with crash guards.
- **Targeted Binary Lookups:** Isolates records dynamically using target key variables.
- **Interactive Dashboard:** Provides a continuous terminal UI for straightforward navigation.

### 📂 Files Structure

- `StudentManagementSys.c` - Core implementation script.
- `students.txt` - Persistent database file managed by the program.

### 🚀 Build & Run

Requirements:
- ANSI C compliant toolchains (e.g., gcc or clang).

Build Instructions:
- Compile the source using your terminal:

```bash
gcc StudentManagementSys.c -o StudentManagementSys
```

### Run Instructions:

**Windows:**

```dos
StudentManagementSys.exe
```

**Mac / Linux:**

```bash
./StudentManagementSys
```

### ⚙️ Operational Workflows

- **Add Student:** Registers a new record with validation.
- **View Records:** Displays an aligned tabular representation of all students.
- **Search Records:** Performs a sequential lookup by Roll Number.
- **Delete Records:** Filters and removes targeted elements from the database.
- **Roll Call:** Triggers an incremental loop for attendance logging.

### ⚠️ Current Limitations

- **Fixed Capacity:** Limited to 100 concurrent entries.
- **Volatile Write Cycles:** Overwrites the file entirely during updates.
- **Input Sensitivity:** Basic validation; requires precise character inputs.

### 🔮 Future Roadmaps

- `updateRecord()`: Modify existing records without deletion.
- `calculateAttendanceReport()`: Generate warning lists for low attendance.
- `sortRecords()`: Order students by various metrics.
- `backupData()`: Automatic file recovery routines.
- `import/export CSV()`: Compatibility with spreadsheet software.
- `secureAccess()`: Password-protected admin menu.
- `useDynamicStorage()`: Transition to heap-allocated memory (pointers).

### 🌐 Online Repository

URL: https://github.com/pallavbh/C-Project

### ⚖️ License

This project is designed for educational purposes ( college assignment ) and is open for modification and reference.