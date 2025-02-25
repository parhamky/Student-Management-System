# Student Management System

This is the final project for the **Fundamentals of Computer Programming (FCP)** course at the University of Tehran. The project is a **Student Management System** that allows users to manage students, their courses, and grades using a SQLite database.

---

## Features

- **CRUD Operations**:
  - Create, Read, Update, and Delete students and their courses.
- **Database Integration**:
  - Uses SQLite to store student and course data.
- **Migrations**:
  - Supports **up migrations** (applying changes) and **down migrations** (reverting changes).
- **User-Friendly Interface**:
  - A command-line interface (CLI) for interacting with the system.

---

## Prerequisites

Before running the project, ensure you have the following installed:

1. **C++ Compiler**:
   - `g++` or any C++17-compatible compiler.
2. **SQLite3**:
   - Install SQLite3 on your system.
   - On Linux: `sudo apt install sqlite3 libsqlite3-dev`
   - On macOS: `brew install sqlite3`
   - On Windows: Download from [SQLite website](https://www.sqlite.org/download.html).
3. **Make**:
   - Ensure `make` is installed on your system.

---

## Project Structure

The project consists of the following files:

- **`main.cpp`**:
  - The entry point of the application.
- **`db.h`**:
  - Handles database connection, migrations, and SQL execution.
- **`models.h`**:
  - Defines the data structures (`person` and `lesson`) and database operations.
- **`control.h`**:
  - Implements the user interface and application logic.
- **`migrations/`**:
  - Contains SQL scripts for **up migrations** (e.g., creating tables).
- **`down_migrations/`**:
  - Contains SQL scripts for **down migrations** (e.g., dropping tables).
- **`Makefile`**:
  - Automates compilation, migration, and execution.

---

## Setup and Usage

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/student-management-system.git
cd student-management-system
```

### 2. Compile the Program

Use the `Makefile` to compile the program:

```bash
make compile
```

### 3. Apply Migrations

Apply the **up migrations** to set up the database:

```bash
make migrate
```

### 4. Run the Program

Start the application:

```bash
make run
```

### 5. Apply Down Migrations (Optional)

To revert changes, apply the **down migrations**:

```bash
make down
```

### 6. Clean Up

Remove the compiled executable and database file:

```bash
make clean
```

---

## Example Workflow

1. **Add a Student**:
   - Use the CLI to add a new student with their name, field of study (`reshte`), and courses.

2. **Add a Course**:
   - Add courses for a student, including the course name, credit hours (`vahed`), and grade.

3. **Calculate Average**:
   - The system automatically calculates the student's average based on their courses.

4. **View Students**:
   - View a list of students sorted by their average grade.

5. **Edit or Delete**:
   - Edit or delete students and their courses.

---

## Database Schema

The database consists of two tables:

### **`person` Table**
| Column    | Type        | Description                |
|-----------|-------------|----------------------------|
| `id`      | INTEGER     | Primary key (auto-increment)|
| `name`    | TEXT        | Student's name             |
| `reshte`  | TEXT        | Field of study             |
| `average` | REAL        | Student's average grade    |

### **`lesson` Table**
| Column        | Type        | Description                |
|---------------|-------------|----------------------------|
| `lesson_id`   | INTEGER     | Primary key (auto-increment)|
| `lesson_name` | TEXT        | Course name                |
| `student_id`  | INTEGER     | Foreign key (references `person.id`)|
| `vahed`       | INTEGER     | Credit hours               |
| `grade`       | REAL        | Grade for the course       |

---

## Migrations

### Up Migrations
- Located in the `migrations/` directory.
- Example: `001_create_tables.sql` creates the `person` and `lesson` tables.

### Down Migrations
- Located in the `down_migrations/` directory.
- Example: `001_drop_tables.sql` drops the `person` and `lesson` tables.

---

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- **University of Tehran**: For providing the Fundamentals of Computer Programming (FCP) course.
- **SQLite**: For providing a lightweight and powerful database engine.
- **Instructor and TAs**: For their guidance and support throughout the course.

---
Enjoy using the **Student Management System**! 🚀