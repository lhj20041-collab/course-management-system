#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

// Constants
const int MAX_COURSES = 1000;
const int MAX_USERS = 100;
const int MAX_STRING_LENGTH = 100;

// Global arrays for courses
string courseIds[MAX_COURSES];
string titles[MAX_COURSES];
int creditHours[MAX_COURSES];
int courseCount = 0;

// Global arrays for users
string usernames[MAX_USERS];
string passwords[MAX_USERS];
int userCount = 0;

// Function declarations
void loadUsers();
void loadCourses();
bool login();
void saveCourses();
void addCourse();
void deleteCourse();
void searchCourse();
void updateCourse();
void listCourses();
void showMenu();

int main() {
    // Load data from files
    loadUsers();
    loadCourses();

    // Login
    if (!login()) {
        cout << "Login failed. Exiting program." << endl;
        return 1;
    }

    // Show menu
    showMenu();

    return 0;
}

void loadUsers() {
    ifstream file("users.txt");
    string line;
    userCount = 0;

    if (file.is_open()) {
        while (getline(file, line) && userCount < MAX_USERS) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                usernames[userCount] = line.substr(0, commaPos);
                passwords[userCount] = line.substr(commaPos + 1);
                userCount++;
            }
        }
        file.close();
    } else {
        cout << "Warning: users.txt not found. Creating new file." << endl;
    }
}

void loadCourses() {
    ifstream file("courses.txt");
    string line;
    courseCount = 0;

    if (file.is_open()) {
        while (getline(file, line) && courseCount < MAX_COURSES) {
            size_t firstComma = line.find(',');
            size_t secondComma = line.find(',', firstComma + 1);

            if (firstComma != string::npos && secondComma != string::npos) {
                courseIds[courseCount] = line.substr(0, firstComma);
                titles[courseCount] = line.substr(firstComma + 1, secondComma - firstComma - 1);
                creditHours[courseCount] = stoi(line.substr(secondComma + 1));
                courseCount++;
            }
        }
        file.close();
    } else {
        cout << "Warning: courses.txt not found. Creating new file." << endl;
    }
}

bool login() {
    string username, password;

    cout << "=== Course Management System ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == username && passwords[i] == password) {
            cout << "Login successful!" << endl;
            return true;
        }
    }

    // If user not found, ask if they want to register
    cout << "User not found. Would you like to register? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        if (userCount < MAX_USERS) {
            usernames[userCount] = username;
            passwords[userCount] = password;
            userCount++;

            // Save new user to file
            ofstream file("users.txt", ios::app);
            if (file.is_open()) {
                file << username << "," << password << endl;
                file.close();
                cout << "Registration successful!" << endl;
                return true;
            } else {
                cout << "Error: Could not save user." << endl;
                return false;
            }
        } else {
            cout << "Error: Maximum user limit reached." << endl;
            return false;
        }
    }

    return false;
}

void saveCourses() {
    ofstream file("courses.txt");

    if (file.is_open()) {
        for (int i = 0; i < courseCount; i++) {
            file << courseIds[i] << "," << titles[i] << "," << creditHours[i] << endl;
        }
        file.close();
    } else {
        cout << "Error: Could not save courses to file." << endl;
    }
}

void addCourse() {
    if (courseCount >= MAX_COURSES) {
        cout << "Error: Maximum course limit reached." << endl;
        return;
    }

    string id, title;
    int hours;

    cout << "Enter course ID: ";
    cin >> id;

    // Check for duplicate course ID
    for (int i = 0; i < courseCount; i++) {
        if (courseIds[i] == id) {
            cout << "Error: Course ID already exists." << endl;
            return;
        }
    }

    cout << "Enter course title: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter credit hours (1-6): ";
    cin >> hours;

    if (hours < 1 || hours > 6) {
        cout << "Error: Credit hours must be between 1 and 6." << endl;
        return;
    }

    courseIds[courseCount] = id;
    titles[courseCount] = title;
    creditHours[courseCount] = hours;
    courseCount++;

    saveCourses();
    cout << "Course added successfully!" << endl;
}

void deleteCourse() {
    string id;
    cout << "Enter course ID to delete: ";
    cin >> id;

    for (int i = 0; i < courseCount; i++) {
        if (courseIds[i] == id) {
            // Shift all elements after the deleted course
            for (int j = i; j < courseCount - 1; j++) {
                courseIds[j] = courseIds[j + 1];
                titles[j] = titles[j + 1];
                creditHours[j] = creditHours[j + 1];
            }
            courseCount--;

            saveCourses();
            cout << "Course deleted successfully!" << endl;
            return;
        }
    }

    cout << "Error: Course not found." << endl;
}

void searchCourse() {
    int choice;
    cout << "Search by:\n1. Course ID\n2. Title substring\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        string id;
        cout << "Enter course ID: ";
        cin >> id;

        for (int i = 0; i < courseCount; i++) {
            if (courseIds[i] == id) {
                cout << "Course found:" << endl;
                cout << "ID: " << courseIds[i] << ", Title: " << titles[i]
                     << ", Credit Hours: " << creditHours[i] << endl;
                return;
            }
        }

        cout << "Course not found." << endl;
    } else if (choice == 2) {
        string substring;
        cout << "Enter title substring: ";
        cin.ignore();
        getline(cin, substring);

        bool found = false;
        for (int i = 0; i < courseCount; i++) {
            if (titles[i].find(substring) != string::npos) {
                cout << "Course found:" << endl;
                cout << "ID: " << courseIds[i] << ", Title: " << titles[i]
                     << ", Credit Hours: " << creditHours[i] << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No courses found with that substring." << endl;
        }
    } else {
        cout << "Invalid choice." << endl;
    }
}

void updateCourse() {
    string id;
    cout << "Enter course ID to update: ";
    cin >> id;

    for (int i = 0; i < courseCount; i++) {
        if (courseIds[i] == id) {
            int choice;
            cout << "What would you like to update?\n1. Title\n2. Credit Hours\nEnter choice: ";
            cin >> choice;

            if (choice == 1) {
                string newTitle;
                cout << "Enter new title: ";
                cin.ignore();
                getline(cin, newTitle);
                titles[i] = newTitle;
            } else if (choice == 2) {
                int newHours;
                cout << "Enter new credit hours (1-6): ";
                cin >> newHours;

                if (newHours < 1 || newHours > 6) {
                    cout << "Error: Credit hours must be between 1 and 6." << endl;
                    return;
                }

                creditHours[i] = newHours;
            } else {
                cout << "Invalid choice." << endl;
                return;
            }

            saveCourses();
            cout << "Course updated successfully!" << endl;
            return;
        }
    }

    cout << "Error: Course not found." << endl;
}

void listCourses() {
    if (courseCount == 0) {
        cout << "No courses available." << endl;
        return;
    }

    cout << "List of all courses:" << endl;
    for (int i = 0; i < courseCount; i++) {
        cout << i + 1 << ". ID: " << courseIds[i] << ", Title: " << titles[i]
             << ", Credit Hours: " << creditHours[i] << endl;
    }
}

void showMenu() {
    int choice;

    do {
        cout << "\n=== Course Management System ===" << endl;
        cout << "1. Add Course" << endl;
        cout << "2. Delete Course" << endl;
        cout << "3. Search Course" << endl;
        cout << "4. Update Course" << endl;
        cout << "5. List All Courses" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addCourse();
                break;
            case 2:
                deleteCourse();
                break;
            case 3:
                searchCourse();
                break;
            case 4:
                updateCourse();
                break;
            case 5:
                listCourses();
                break;
            case 6:
                cout << "Logging out. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}
