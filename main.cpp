#include <iostream>
#include "control.h"


using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./main [migrate <directory>|run|down]" << endl;
        return 1;
    }

    string command = argv[1];
    sqlite3* db = initDB("test");
    if (!db) {
        return 1;
    }

    if (command == "migrate" && argc > 2) {
        string migpath = argv[2];
        string err = migrate(migpath, db);
        if (!err.empty()) {
            cerr << err << endl;
            closeDB(db);
            return 1;
        }
    } else if (command == "run") {
        // Run the program
        cout << "Running the program..." << endl;
        index(db); // Start the application
    } else if (command == "down") {
        string migpath = "migrations/down";
        string err = migrate(migpath, db);
        if (!err.empty()) {
            cerr << err << endl;
            closeDB(db);
            return 1;
        }
    } else {
        cout << "Invalid command." << endl;
        closeDB(db);
        return 1;
    }

    closeDB(db);
    return 0;
}