-- Create person table
CREATE TABLE IF NOT EXISTS person (
                                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                                      name TEXT NOT NULL,
                                      reshte TEXT NOT NULL,
                                      average REAL DEFAULT 0
);