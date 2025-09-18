#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

// Constants
const int MAX_COURSES = 1000;
const int MAX_USERS = 100;
const string USER_FILE = "users.txt";
const string COURSE_FILE = "courses.txt";

// Global arrays for course data
string courseIds[MAX_COURSES];
string courseTitles[MAX_COURSES];
int courseCredits[MAX_COURSES];
int courseCount = 0;

// Global arrays for user data
string usernames[MAX_USERS];
string passwords[MAX_USERS];
int userCount = 0;

// Function prototypes
void loadUsers();
void loadCourses();
void saveUsers();
void saveCourses();
bool registerUser();
bool login(string& currentUser);
void showMainMenu(string currentUser);
void addCourse();
void deleteCourse();
void searchCourse();
void updateCourse();
void listCourses();
int findCourseById(string courseId);
int findUser(string username);
void toLowerCase(string& str);
string trim(const string& str);

int main() {
    loadUsers();
    loadCourses();
    
    string currentUser = "";
    int choice;
    
    while (true) {
        cout << "\n=== Course Management System ===" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        
        cin.ignore(); // Clear newline character
        
        switch (choice) {
            case 1:
                if (registerUser()) {
                    cout << "Registration successful!" << endl;
                } else {
                    cout << "Registration failed. Username may already exist." << endl;
                }
                break;
            case 2:
                if (login(currentUser)) {
                    cout << "Login successful! Welcome, " << currentUser << "!" << endl;
                    showMainMenu(currentUser);
                    currentUser = ""; // Reset current user after logout
                } else {
                    cout << "Login failed. Invalid credentials." << endl;
                }
                break;
            case 3:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    
    return 0;
}

void loadUsers() {
    ifstream file(USER_FILE);
    if (!file.is_open()) {
        return; // File doesn't exist yet
    }
    
    string line;
    userCount = 0;
    while (getline(file, line) && userCount < MAX_USERS) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            usernames[userCount] = trim(line.substr(0, commaPos));
            passwords[userCount] = trim(line.substr(commaPos + 1));
            userCount++;
        }
    }
    
    file.close();
}

void loadCourses() {
    ifstream file(COURSE_FILE);
    if (!file.is_open()) {
        return; // File doesn't exist yet
    }
    
    string line;
    courseCount = 0;
    while (getline(file, line) && courseCount < MAX_COURSES) {
        size_t firstComma = line.find(',');
        size_t secondComma = line.find(',', firstComma + 1);
        
        if (firstComma != string::npos && secondComma != string::npos) {
            courseIds[courseCount] = trim(line.substr(0, firstComma));
            courseTitles[courseCount] = trim(line.substr(firstComma + 1, secondComma - firstComma - 1));
            
            string creditStr = trim(line.substr(secondComma + 1));
            try {
                courseCredits[courseCount] = stoi(creditStr);
            } catch (...) {
                courseCredits[courseCount] = 0; // Default value if conversion fails
            }
            
            courseCount++;
        }
    }
    
    file.close();
}

void saveUsers() {
    ofstream file(USER_FILE);
    if (!file.is_open()) {
        cout << "Error saving users!" << endl;
        return;
    }
    
    for (int i = 0; i < userCount; i++) {
        file << usernames[i] << "," << passwords[i] << endl;
    }
    
    file.close();
}

void saveCourses() {
    ofstream file(COURSE_FILE);
    if (!file.is_open()) {
        cout << "Error saving courses!" << endl;
        return;
    }
    
    for (int i = 0; i < courseCount; i++) {
        file << courseIds[i] << "," << courseTitles[i] << "," << courseCredits[i] << endl;
    }
    
    file.close();
}

bool registerUser() {
    string username, password;
    
    cout << "Enter username: ";
    getline(cin, username);
    username = trim(username);
    
    if (username.empty()) {
        cout << "Username cannot be empty." << endl;
        return false;
    }
    
    // Check if username already exists
    if (findUser(username) != -1) {
        return false;
    }
    
    cout << "Enter password: ";
    getline(cin, password);
    password = trim(password);
    
    if (password.empty()) {
        cout << "Password cannot be empty." << endl;
        return false;
    }
    
    if (userCount < MAX_USERS) {
        usernames[userCount] = username;
        passwords[userCount] = password;
        userCount++;
        saveUsers();
        return true;
    }
    
    return false;
}

bool login(string& currentUser) {
    string username, password;
    
    cout << "Username: ";
    getline(cin, username);
    username = trim(username);
    
    cout << "Password: ";
    getline(cin, password);
    password = trim(password);
    
    int userIndex = findUser(username);
    if (userIndex != -1 && passwords[userIndex] == password) {
        currentUser = username;
        return true;
    }
    
    return false;
}

int findUser(string username) {
    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == username) {
            return i;
        }
    }
    return -1;
}

void showMainMenu(string currentUser) {
    int choice;
    
    while (true) {
        cout << "\n=== Main Menu ===" << endl;
        cout << "Logged in as: " << currentUser << endl;
        cout << "1. Add Course" << endl;
        cout << "2. Delete Course" << endl;
        cout << "3. Search Course" << endl;
        cout << "4. Update Course" << endl;
        cout << "5. List All Courses" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        
        cin.ignore(); // Clear newline character
        
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
                cout << "Logging out..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void addCourse() {
    if (courseCount >= MAX_COURSES) {
        cout << "Maximum course limit reached!" << endl;
        return;
    }
    
    string id, title;
    int credits;
    
    cout << "Enter course ID: ";
    getline(cin, id);
    id = trim(id);
    
    if (id.empty()) {
        cout << "Course ID cannot be empty." << endl;
        return;
    }
    
    // Check for duplicate course ID
    if (findCourseById(id) != -1) {
        cout << "Course with this ID already exists." << endl;
        return;
    }
    
    cout << "Enter course title: ";
    getline(cin, title);
    title = trim(title);
    
    if (title.empty()) {
        cout << "Course title cannot be empty." << endl;
        return;
    }
    
    cout << "Enter credit hours (1-6): ";
    if (!(cin >> credits)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Credit hours must be a number." << endl;
        return;
    }
    
    cin.ignore(); // Clear newline character
    
    if (credits < 1 || credits > 6) {
        cout << "Credit hours must be between 1 and 6." << endl;
        return;
    }
    
    courseIds[courseCount] = id;
    courseTitles[courseCount] = title;
    courseCredits[courseCount] = credits;
    courseCount++;
    
    saveCourses();
    cout << "Course added successfully!" << endl;
}

void deleteCourse() {
    string id;
    
    cout << "Enter course ID to delete: ";
    getline(cin, id);
    id = trim(id);
    
    int index = findCourseById(id);
    if (index == -1) {
        cout << "Course not found." << endl;
        return;
    }
    
    // Shift all elements after the found index to the left
    for (int i = index; i < courseCount - 1; i++) {
        courseIds[i] = courseIds[i + 1];
        courseTitles[i] = courseTitles[i + 1];
        courseCredits[i] = courseCredits[i + 1];
    }
    
    courseCount--;
    saveCourses();
    cout << "Course deleted successfully!" << endl;
}

void searchCourse() {
    int choice;
    string searchTerm;
    
    cout << "\nSearch by:" << endl;
    cout << "1. Course ID" << endl;
    cout << "2. Title keyword" << endl;
    cout << "Enter your choice: ";
    
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input." << endl;
        return;
    }
    
    cin.ignore(); // Clear newline character
    
    if (choice != 1 && choice != 2) {
        cout << "Invalid choice." << endl;
        return;
    }
    
    cout << "Enter search term: ";
    getline(cin, searchTerm);
    searchTerm = trim(searchTerm);
    
    if (searchTerm.empty()) {
        cout << "Search term cannot be empty." << endl;
        return;
    }
    
    bool found = false;
    string searchTermLower = searchTerm;
    toLowerCase(searchTermLower);
    
    cout << "\nSearch results:" << endl;
    cout << "----------------------------------------" << endl;
    
    for (int i = 0; i < courseCount; i++) {
        string compareField;
        
        if (choice == 1) {
            compareField = courseIds[i];
        } else {
            compareField = courseTitles[i];
        }
        
        string compareFieldLower = compareField;
        toLowerCase(compareFieldLower);
        
        if (compareFieldLower.find(searchTermLower) != string::npos) {
            cout << "ID: " << courseIds[i] << " | Title: " << courseTitles[i] 
                 << " | Credits: " << courseCredits[i] << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No courses found matching your search." << endl;
    }
    
    cout << "----------------------------------------" << endl;
}

void updateCourse() {
    string id;
    
    cout << "Enter course ID to update: ";
    getline(cin, id);
    id = trim(id);
    
    int index = findCourseById(id);
    if (index == -1) {
        cout << "Course not found." << endl;
        return;
    }
    
    cout << "Current title: " << courseTitles[index] << endl;
    cout << "Enter new title (press Enter to keep current): ";
    string newTitle;
    getline(cin, newTitle);
    newTitle = trim(newTitle);
    
    if (!newTitle.empty()) {
        courseTitles[index] = newTitle;
    }
    
    cout << "Current credit hours: " << courseCredits[index] << endl;
    cout << "Enter new credit hours (1-6, enter 0 to keep current): ";
    int newCredits;
    
    if (!(cin >> newCredits)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Credit hours not updated." << endl;
    } else {
        cin.ignore(); // Clear newline character
        
        if (newCredits >= 1 && newCredits <= 6) {
            courseCredits[index] = newCredits;
        } else if (newCredits != 0) {
            cout << "Invalid credit hours. Must be between 1 and 6. Credit hours not updated." << endl;
        }
    }
    
    saveCourses();
    cout << "Course updated successfully!" << endl;
}

void listCourses() {
    if (courseCount == 0) {
        cout << "No courses available." << endl;
        return;
    }
    
    cout << "\nList of all courses:" << endl;
    cout << "----------------------------------------" << endl;
    
    for (int i = 0; i < courseCount; i++) {
        cout << "ID: " << courseIds[i] << " | Title: " << courseTitles[i] 
             << " | Credits: " << courseCredits[i] << endl;
    }
    
    cout << "----------------------------------------" << endl;
    cout << "Total courses: " << courseCount << endl;
}

int findCourseById(string courseId) {
    for (int i = 0; i < courseCount; i++) {
        if (courseIds[i] == courseId) {
            return i;
        }
    }
    return -1;
}

void toLowerCase(string& str) {
    for (char& c : str) {
        c = tolower(c);
    }
}

string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}