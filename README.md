[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=12466885)
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
