#include <iostream>
#include "models.h"
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

void lessons(person& p, sqlite3* db);
void newlesson(person& p, sqlite3* db);

void editstudent(person& p, sqlite3* db) {
    person payload;
    cin.ignore();
    cout << "Enter new name: ";
    getline(cin, payload.name);

    cout << "Enter new reshte: ";
    cin >> payload.reshte;

    cout << "Enter new average: ";
    cin >> payload.average;

    payload.id = p.id;
    updateStudent(payload, db);
}

void deletestudent(person& p, sqlite3* db) {
    removeStudent(p.id, db);
}

void editlesson(string name, unsigned long int id, sqlite3* db) {
    lesson payload;
    cin.ignore();
    cout << "Enter new course name: ";
    getline(cin, payload.lesson_name);

    cout << "Enter course grade: ";
    cin >> payload.grade;

    cout << "Enter course vahed: ";
    cin >> payload.vahed;

    payload.student_id = id;
    updateLesson(payload, db);
}

void student(person& p, sqlite3* db) {
    cout << "Welcome " << p.name << endl;
    cout << "---------------------------------------------" << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Lessons list" << endl;
    cout << "2 - Edit student" << endl;
    cout << "3 - Add lesson" << endl;
    cout << "4 - Delete student" << endl;
    short int key;
    cin >> key;
    switch (key) {
        case 1:
            lessons(p, db);
            break;
        case 2:
            editstudent(p, db);
            break;
        case 3:
            newlesson(p, db);
            break;
        case 4:
            deletestudent(p, db);
            break;
        case 0:
            return;
        default:
            cout << "Invalid option!" << endl;
    }
}

void newlesson(person& p, sqlite3* db) {
    lesson payload;
    cin.ignore();
    cout << "Enter course name: ";
    getline(cin, payload.lesson_name);

    cout << "Enter course grade: ";
    cin >> payload.grade;

    cout << "Enter course vahed: ";
    cin >> payload.vahed;

    payload.student_id = p.id;
    addLesson(payload, db);

    // Recalculate average
    p = getPerson(p.id, db); // Refresh the person data
    p.getavg(db);
}

void students(vector<person>& p, sqlite3* db) {
    cout << "--------------------------------------------------" << endl;
    string reshteinp;
    cin.ignore();
    cout << "Choose reshte: ";
    getline(cin, reshteinp);

    cout << left << setw(15) << "Name" << setw(10) << "ID" << setw(15) << "Reshte" << right << setw(10) << "Average" << endl;
    cout << "--------------------------------------------------" << endl;
    for (auto& li : p) {
        cout << left << setw(15) << li.name << setw(10) << li.id << setw(15) << li.reshte << right << setw(7) << li.average << endl;
    }

    unsigned long int inpid;
    cout << "--------------------------------------------------" << endl;
    cout << "Enter the ID of the student (0 to exit): ";
    cin >> inpid;

    if (inpid == 0) {
        return;
    }

    for (auto& li : p) {
        if (li.id == inpid) {
            student(li, db);
            return;
        }
    }
    cout << "Student not found!" << endl;
}

void lessons(person& p, sqlite3* db) {
    auto list = getLessons(p.id, db);
    cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(7) << right << "Vahed" << right << setw(7) << "Grade" << endl;
    cout << "---------------------------------------------" << endl;
    for (auto& li : list) {
        cout << left << setw(10) << li.lesson_id << setw(15) << li.lesson_name << setw(7) << left << li.vahed << left << setw(7) << li.grade << endl;
    }

    cout << "---------------------------------------------" << endl;
    cout << "If you want to edit a lesson, type the lesson ID (or 0 to exit): ";
    unsigned long int inpid;
    cin >> inpid;

    if (inpid == 0) {
        return;
    }

    for (auto& li : list) {
        if (li.lesson_id == inpid) {
            editlesson(li.lesson_name, p.id, db);
            return;
        }
    }
    cout << "Lesson not found!" << endl;
}

void createstudent(sqlite3* db) {
    person payload;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, payload.name);

    cout << "Enter reshte: ";
    cin >> payload.reshte;

    payload.average = 0;
    addStudent(payload, db);
}

void index(sqlite3* db) {
    auto p = getStudents(db);
    int key;
    cout << "Welcome to Student Management App" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Select an option:" << endl;
    cout << "1 - Show students" << endl;
    cout << "2 - Create student" << endl;
    cout << "3 - Exit" << endl;
    cin >> key;

    switch (key) {
        case 1:
            students(p, db);
            index(db);
            break;
        case 2:
            createstudent(db);
            index(db);
            break;
        case 3:
            return;
        default:
            cout << "Invalid input!" << endl;
            index(db);
    }
}