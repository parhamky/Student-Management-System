#include <fstream>
#include <vector>
#include <sqlite3.h>
#include <filesystem>
#include <iostream>
#include <format>

using namespace std;

// Initialize the database
sqlite3* initDB(string dbname) {
    sqlite3* db;
    const string loc = "databases/" + dbname + ".db";
    int err = sqlite3_open(loc.c_str(), &db);
    if (err) {
        cout << "We have an error: " << sqlite3_errmsg(db) << endl;
        return nullptr;
    } else {
        cout << "DB connected successfully" << endl;
        return db;
    }
}

// Execute an SQL query
string executeSql(const string& sql, sqlite3* ctx) {
    char* errMsg = nullptr;
    int errc = sqlite3_exec(ctx, sql.c_str(), nullptr, nullptr, &errMsg);
    if (errc != SQLITE_OK) {
        string error = errMsg; // Copy the error message
        sqlite3_free(errMsg);  // Free the original error message
        return error;          // Return the copied error message
    }
    return ""; // Return an empty string to indicate success
}

// Read the content of a file
string readFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return "";
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

// Apply a migration from a file
string applyMigration(sqlite3* ctx, const string& file) {
    string script = readFile(file);
    if (script.empty()) {
        return "Error: Could not read migration file: " + file;
    }
    return executeSql(script, ctx); // Execute the SQL script
}

// Apply all migrations in a directory
string migrate(filesystem::path migpath, sqlite3* ctx) {
    // Debug: Print the migration path
    cout << "Migration path: " << migpath << endl;

    // Check if the directory exists
    if (!filesystem::exists(migpath)) {
        return "Error: Directory does not exist: " + migpath.string();
    }

    // Check if the path is a directory
    if (!filesystem::is_directory(migpath)) {
        return "Error: Path is not a directory: " + migpath.string();
    }

    // Apply migrations
    for (const auto& entry : filesystem::directory_iterator(migpath)) {
        if (entry.is_regular_file()) { // Ensure it's a file (not a directory)
            string err = applyMigration(ctx, entry.path().string());
            if (!err.empty()) {
                return "Migration failed: " + err;
            } else {
                cout << "Migration applied successfully: " << entry.path().filename() << endl;
            }
        }
    }
    return ""; // Return an empty string to indicate success
}

// Close the database connection
void closeDB(sqlite3* ctx) {
    cout << "Disconnected successfully" << endl;
    sqlite3_close(ctx);
}