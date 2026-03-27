#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <conio.h>   // for _getch()
using namespace std;

// ?? Hidden Password Function
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

// ?? Check if user exists
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

// ?? Registration
void registerUser() {
    string username, password;

    cout << "\n--- Registration ---\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter username: ";
    getline(cin, username);

    if (userExists(username)) {
        cout << "Error: Username already exists!\n";
        return;
    }

    cout << "Enter password: ";
    password = getHiddenPassword();

    if (username.length() < 3 || password.length() < 4) {
        cout << "Error: Username must be >=3 and password >=4 characters!\n";
        return;
    }

    ofstream file("users.txt", ios::app);
    file << username << "|" << password << endl;

    cout << "Registration Successful!\n";
}

// ?? Login
void loginUser() {
    string username, password;
    string line, user, pass;
    bool found = false;

    cout << "\n--- Login ---\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

// ?? Main Menu
int main() {
    int choice;

    do {
        cout << "\n===== LOGIN SYSTEM =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

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
