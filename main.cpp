#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Check if user exists
bool userExists(string username) {
    ifstream file("users.txt");
    string user, pass;

    while (file >> user >> pass) {
        if (user == username) {
            return true;
        }
    }
    return false;
}

// Registration
void registerUser() {
    string username, password;

    cout << "\n--- Registration ---\n";

    cin.ignore(); // IMPORTANT FIX

    cout << "Enter username: ";
    getline(cin, username);

    if (userExists(username)) {
        cout << "Error: Username already exists!\n";
        return;
    }

    cout << "Enter password: ";
    getline(cin, password);

    if (username.length() < 3 || password.length() < 4) {
        cout << "Error: Invalid input length!\n";
        return;
    }

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;

    cout << "Registration Successful!\n";
}

// Login
void loginUser() {
    string username, password;
    string user, pass;
    bool found = false;

    cout << "\n--- Login ---\n";

    cin.ignore(); // IMPORTANT FIX

    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password: ";
    getline(cin, password);

    ifstream file("users.txt");

    while (file >> user >> pass) {
        if (user == username && pass == password) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Login Successful! Welcome " << username << "!\n";
    } else {
        cout << "Error: Invalid username or password!\n";
    }
}

// Main
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
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 3);

    return 0;
}
