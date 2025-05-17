# 🗂️ Student Database System (C Project)

This is a simple console-based application written in C that allows users to manage a database of students. It supports adding, viewing, searching, and deleting students, with manual input validation and basic file-based persistence (`fread`/`fwrite`).

---

## 💡 Features

- Add new student records with validation  
- View all students in the database  
- Search students by any combination of fields  
- Delete student records by ID  
- Persistent binary storage using `database.dat`  
- Input validation (age, name, average score, etc.)

---

## 🧠 Technologies Used

- **Language:** C  
- **Storage:** Binary file (`database.dat`)  
- **I/O:** Standard `stdio.h` functions (`fopen`, `fread`, `fwrite`)  
- **Validation:** Manual (name, age, average)  
- **String Handling:** Custom compare and conversion functions

---

## 🚀 How to Run

```bash
    make || gcc main.c -o main.o
./main.o
