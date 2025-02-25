-- Create lesson table
CREATE TABLE IF NOT EXISTS lesson (
                                      lesson_id INTEGER PRIMARY KEY AUTOINCREMENT,
                                      lesson_name TEXT NOT NULL,
                                      student_id INTEGER NOT NULL,
                                      vahed INTEGER NOT NULL,
                                      grade REAL NOT NULL,
                                      FOREIGN KEY (student_id) REFERENCES person(id)
    );