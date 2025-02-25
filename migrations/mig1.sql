CREATE TABLE IF NOT EXISTS person (
                                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                                      name TEXT NOT NULL,
                                      reshte TEXT NOT NULL,
                                      average REAL DEFAULT 0
);

CREATE TABLE IF NOT EXISTS lesson (
                                      lesson_id INTEGER PRIMARY KEY AUTOINCREMENT,
                                      lesson_name TEXT NOT NULL,
                                      student_id INTEGER NOT NULL,
                                      vahed INTEGER NOT NULL,
                                      grade REAL NOT NULL,
                                      FOREIGN KEY (student_id) REFERENCES person(id)
    );