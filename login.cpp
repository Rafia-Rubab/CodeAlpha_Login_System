#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <conio.h>   // for_getch()

using namespace std;

// Hidden Password Function (Windows only)
string getHiddenPassword() {
    string password = "";
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 13) { // Enter key
            break;
        }
        else if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password += ch;
            cout << "*";
        }
    }
    cout << endl;
    return password;
}

// Check if user already exists
bool userExists(string username) {
    ifstream file("users.txt");
    string line, user;

    while (getline(file, line)) {
        int pos = line.find('|');
        if (pos != string::npos) {
            user = line.substr(0, pos);
            if (user == username) {
                return true;
            }
        }
    }
    return false;
}

// Registration Function
void registerUser() {
    string username, password;

    cout << "\n--- Registration ---\n";

    cout << "Enter username: ";
    getline(cin, username);

    // Validation
    if (username.empty()) {
        cout << "Error: Username cannot be empty!\n";
        return;
    }

    if (username.find('|') != string::npos) {
        cout << "Error: '|' character not allowed!\n";
        return;
    }

    if (userExists(username)) {
        cout << "Error: Username already exists!\n";
        return;
    }

    cout << "Enter password: ";
    password = getHiddenPassword();

    if (username.length() < 3 || password.length() < 4) {
        cout << "Error: Username >=3 and password >=4 characters required!\n";
        return;
    }

    ofstream file("users.txt", ios::app);
    file << username << "|" << password << endl;

    cout << "Registration Successful!\n";
}

// Login Function
void loginUser() {
    string username, password;
    string line, user, pass;
    bool found = false;

    cout << "\n--- Login ---\n";

    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password: ";
    password = getHiddenPassword();

    ifstream file("users.txt");

    while (getline(file, line)) {
        int pos = line.find('|');

        if (pos != string::npos) {
            user = line.substr(0, pos);
            pass = line.substr(pos + 1);

            if (user == username && pass == password) {
                found = true;
                break;
            }
        }
    }

    if (found) {
        cout << "Login Successful! Welcome " << username << "!\n";
    } else {
        cout << "Error: Invalid username or password!\n";
    }
}

// Main Function
int main() {
    int choice;

    do {
        cout << "\n===== LOGIN SYSTEM =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        // FIX: Clear input buffer before getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 3);

    return 0;
}
