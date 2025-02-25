#include <string>
#include <vector>
#include <iostream>
#include "db.h"

using namespace std;

struct lesson {
    unsigned int lesson_id;
    string lesson_name;
    unsigned int student_id;
    short unsigned int vahed;
    float grade;
};

struct person {
    string name;
    unsigned int id;
    string reshte;
    vector<lesson> lessons;
    float average;

    float getavg(sqlite3* db) {
        if (lessons.empty()) {
            average = 0;
            return 0;
        }

        float avg = 0;
        int vahedcount = 0;
        for (auto& li : lessons) {
            avg += (li.vahed * li.grade);
            vahedcount += li.vahed;
        }
        avg = avg / vahedcount;
        average = avg;

        // Update the average in the database
        string sql = "UPDATE person SET average = " + to_string(avg) + " WHERE id = " + to_string(id) + ";";
        executeSql(sql, db);

        return avg;
    }
};

inline bool compare(person& a, person& b) {
    return a.average > b.average;
}



// Database functions
void addStudent(person& p, sqlite3* db) {
    string sql = "INSERT INTO person (name, reshte, average) VALUES ('" +
                 p.name + "', '" + p.reshte + "', " + to_string(p.average) + ");";
    executeSql(sql, db);
}

void removeStudent(unsigned long int id, sqlite3* db) {
    string sql = "DELETE FROM person WHERE id = " + to_string(id) + ";";
    executeSql(sql, db);
}

void updateStudent(person& p, sqlite3* db) {
    string sql = "UPDATE person SET name = '" + p.name + "', reshte = '" + p.reshte +
                 "', average = " + to_string(p.average) + " WHERE id = " + to_string(p.id) + ";";
    executeSql(sql, db);
}

void addLesson(lesson& l, sqlite3* db) {
    string sql = "INSERT INTO lesson (lesson_name, student_id, vahed, grade) VALUES ('" +
                 l.lesson_name + "', " + to_string(l.student_id) + ", " +
                 to_string(l.vahed) + ", " + to_string(l.grade) + ");";
    executeSql(sql, db);
}

void removeLesson(unsigned long int lesson_id, sqlite3* db) {
    string sql = "DELETE FROM lesson WHERE lesson_id = " + to_string(lesson_id) + ";";
    executeSql(sql, db);
}

void updateLesson(lesson& l, sqlite3* db) {
    string sql = "UPDATE lesson SET lesson_name = '" + l.lesson_name + "', vahed = " +
                 to_string(l.vahed) + ", grade = " + to_string(l.grade) +
                 " WHERE lesson_id = " + to_string(l.lesson_id) + ";";
    executeSql(sql, db);
}
vector<lesson> getLessons(unsigned long int student_id, sqlite3* db) {
    vector<lesson> lessons;
    string sql = "SELECT * FROM lesson WHERE student_id = " + to_string(student_id) + ";";
    sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colNames) -> int {
        vector<lesson>* lessons = static_cast<vector<lesson>*>(data);
        lesson l;
        l.lesson_id = stoi(argv[0]);
        l.lesson_name = argv[1];
        l.student_id = stoi(argv[2]);
        l.vahed = stoi(argv[3]);
        l.grade = stof(argv[4]);
        lessons->push_back(l);
        return 0;
    }, &lessons, nullptr);
    return lessons;
}
vector<person> getStudents(sqlite3* db) {
    vector<person> students;
    string sql = "SELECT * FROM person;";
    sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colNames) -> int {
        vector<person>* students = static_cast<vector<person>*>(data);
        person p;
        p.id = stoi(argv[0]);
        p.name = argv[1];
        p.reshte = argv[2];
        p.average = stof(argv[3]);
        students->push_back(p);
        return 0;
    }, &students, nullptr);

    for (auto& p : students) {
        p.lessons = getLessons(p.id, db);
    }
    return students;
}


// Fetch a person by ID
person getPerson(unsigned long int id, sqlite3* db) {
    person p;
    string sql = "SELECT * FROM person WHERE id = " + to_string(id) + ";";
    sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colNames) -> int {
        person* p = static_cast<person*>(data);
        p->id = stoi(argv[0]);
        p->name = argv[1];
        p->reshte = argv[2];
        p->average = stof(argv[3]);
        return 0;
    }, &p, nullptr);

    // Fetch lessons for this person
    p.lessons = getLessons(p.id, db);
    return p;
}