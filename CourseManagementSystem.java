import java.io.*;
import java.util.Scanner;

public class CourseManagementSystem {
    // Constants
    private static final int MAX_COURSES = 1000;
    private static final int MAX_USERS = 100;
    
    // Global arrays for courses
    private static String[] courseIds = new String[MAX_COURSES];
    private static String[] titles = new String[MAX_COURSES];
    private static int[] creditHours = new int[MAX_COURSES];
    private static int courseCount = 0;
    
    // Global arrays for users
    private static String[] usernames = new String[MAX_USERS];
    private static String[] passwords = new String[MAX_USERS];
    private static int userCount = 0;
    
    // Scanner for user input
    private static Scanner scanner = new Scanner(System.in);
    
    public static void main(String[] args) {
        // Load data from files
        loadUsers();
        loadCourses();
        
        // Login
        if (!login()) {
            System.out.println("Login failed. Exiting program.");
            return;
        }
        
        // Show menu
        showMenu();
        
        // Close scanner
        scanner.close();
    }
    
    private static void loadUsers() {
        try (BufferedReader reader = new BufferedReader(new FileReader("users.txt"))) {
            String line;
            userCount = 0;
            
            while ((line = reader.readLine()) != null && userCount < MAX_USERS) {
                int commaPos = line.indexOf(',');
                if (commaPos != -1) {
                    usernames[userCount] = line.substring(0, commaPos);
                    passwords[userCount] = line.substring(commaPos + 1);
                    userCount++;
                }
            }
        } catch (IOException e) {
            System.out.println("Warning: users.txt not found. Creating new file.");
        }
    }
    
    private static void loadCourses() {
        try (BufferedReader reader = new BufferedReader(new FileReader("courses.txt"))) {
            String line;
            courseCount = 0;
            
            while ((line = reader.readLine()) != null && courseCount < MAX_COURSES) {
                int firstComma = line.indexOf(',');
                int secondComma = line.indexOf(',', firstComma + 1);
                
                if (firstComma != -1 && secondComma != -1) {
                    courseIds[courseCount] = line.substring(0, firstComma);
                    titles[courseCount] = line.substring(firstComma + 1, secondComma);
                    creditHours[courseCount] = Integer.parseInt(line.substring(secondComma + 1));
                    courseCount++;
                }
            }
        } catch (IOException e) {
            System.out.println("Warning: courses.txt not found. Creating new file.");
        } catch (NumberFormatException e) {
            System.out.println("Error: Invalid number format in courses.txt");
        }
    }
    
    private static boolean login() {
        System.out.println("=== Course Management System ===");
        System.out.print("Username: ");
        String username = scanner.nextLine();
        System.out.print("Password: ");
        String password = scanner.nextLine();
        
        for (int i = 0; i < userCount; i++) {
            if (usernames[i].equals(username) && passwords[i].equals(password)) {
                System.out.println("Login successful!");
                return true;
            }
        }
        
        // If user not found, ask if they want to register
        System.out.print("User not found. Would you like to register? (y/n): ");
        String choice = scanner.nextLine();
        
        if (choice.equalsIgnoreCase("y")) {
            if (userCount < MAX_USERS) {
                usernames[userCount] = username;
                passwords[userCount] = password;
                userCount++;
                
                // Save new user to file
                try (PrintWriter writer = new PrintWriter(new FileWriter("users.txt", true))) {
                    writer.println(username + "," + password);
                    System.out.println("Registration successful!");
                    return true;
                } catch (IOException e) {
                    System.out.println("Error: Could not save user.");
                    return false;
                }
            } else {
                System.out.println("Error: Maximum user limit reached.");
                return false;
            }
        }
        
        return false;
    }
    
    private static void saveCourses() {
        try (PrintWriter writer = new PrintWriter(new FileWriter("courses.txt"))) {
            for (int i = 0; i < courseCount; i++) {
                writer.println(courseIds[i] + "," + titles[i] + "," + creditHours[i]);
            }
        } catch (IOException e) {
            System.out.println("Error: Could not save courses to file.");
        }
    }
    
    private static void addCourse() {
        if (courseCount >= MAX_COURSES) {
            System.out.println("Error: Maximum course limit reached.");
            return;
        }
        
        System.out.print("Enter course ID: ");
        String id = scanner.nextLine();
        
        // Check for duplicate course ID
        for (int i = 0; i < courseCount; i++) {
            if (courseIds[i].equals(id)) {
                System.out.println("Error: Course ID already exists.");
                return;
            }
        }
        
        System.out.print("Enter course title: ");
        String title = scanner.nextLine();
        
        System.out.print("Enter credit hours (1-6): ");
        int hours;
        try {
            hours = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Error: Invalid number format.");
            return;
        }
        
        if (hours < 1 || hours > 6) {
            System.out.println("Error: Credit hours must be between 1 and 6.");
            return;
        }
        
        courseIds[courseCount] = id;
        titles[courseCount] = title;
        creditHours[courseCount] = hours;
        courseCount++;
        
        saveCourses();
        System.out.println("Course added successfully!");
    }
    
    private static void deleteCourse() {
        System.out.print("Enter course ID to delete: ");
        String id = scanner.nextLine();
        
        for (int i = 0; i < courseCount; i++) {
            if (courseIds[i].equals(id)) {
                // Shift all elements after the deleted course
                for (int j = i; j < courseCount - 1; j++) {
                    courseIds[j] = courseIds[j + 1];
                    titles[j] = titles[j + 1];
                    creditHours[j] = creditHours[j + 1];
                }
                courseCount--;
                
                saveCourses();
                System.out.println("Course deleted successfully!");
                return;
            }
        }
        
        System.out.println("Error: Course not found.");
    }
    
    private static void searchCourse() {
        System.out.print("Search by:\n1. Course ID\n2. Title substring\nEnter choice: ");
        int choice;
        try {
            choice = Integer.parseInt(scanner.nextLine());
        } catch (NumberFormatException e) {
            System.out.println("Invalid choice.");
            return;
        }
        
        if (choice == 1) {
            System.out.print("Enter course ID: ");
            String id = scanner.nextLine();
            
            for (int i = 0; i < courseCount; i++) {
                if (courseIds[i].equals(id)) {
                    System.out.println("Course found:");
                    System.out.println("ID: " + courseIds[i] + ", Title: " + titles[i] + 
                                     ", Credit Hours: " + creditHours[i]);
                    return;
                }
            }
            
            System.out.println("Course not found.");
        } else if (choice == 2) {
            System.out.print("Enter title substring: ");
            String substring = scanner.nextLine();
            
            boolean found = false;
            for (int i = 0; i < courseCount; i++) {
                if (titles[i].contains(substring)) {
                    System.out.println("Course found:");
                    System.out.println("ID: " + courseIds[i] + ", Title: " + titles[i] + 
                                     ", Credit Hours: " + creditHours[i]);
                    found = true;
                }
            }
            
            if (!found) {
                System.out.println("No courses found with that substring.");
            }
        } else {
            System.out.println("Invalid choice.");
        }
    }
    
    private static void updateCourse() {
        System.out.print("Enter course ID to update: ");
        String id = scanner.nextLine();
        
        for (int i = 0; i < courseCount; i++) {
            if (courseIds[i].equals(id)) {
                System.out.print("What would you like to update?\n1. Title\n2. Credit Hours\nEnter choice: ");
                int choice;
                try {
                    choice = Integer.parseInt(scanner.nextLine());
                } catch (NumberFormatException e) {
                    System.out.println("Invalid choice.");
                    return;
                }
                
                if (choice == 1) {
                    System.out.print("Enter new title: ");
                    String newTitle = scanner.nextLine();
                    titles[i] = newTitle;
                } else if (choice == 2) {
                    System.out.print("Enter new credit hours (1-6): ");
                    int newHours;
                    try {
                        newHours = Integer.parseInt(scanner.nextLine());
                    } catch (NumberFormatException e) {
                        System.out.println("Error: Invalid number format.");
                        return;
                    }
                    
                    if (newHours < 1 || newHours > 6) {
                        System.out.println("Error: Credit hours must be between 1 and 6.");
                        return;
                    }
                    
                    creditHours[i] = newHours;
                } else {
                    System.out.println("Invalid choice.");
                    return;
                }
                
                saveCourses();
                System.out.println("Course updated successfully!");
                return;
            }
        }
        
        System.out.println("Error: Course not found.");
    }
    
    private static void listCourses() {
        if (courseCount == 0) {
            System.out.println("No courses available.");
            return;
        }
        
        System.out.println("List of all courses:");
        for (int i = 0; i < courseCount; i++) {
            System.out.println((i + 1) + ". ID: " + courseIds[i] + ", Title: " + titles[i] + 
                             ", Credit Hours: " + creditHours[i]);
        }
    }
    
    private static void showMenu() {
        int choice;
        
        do {
            System.out.println("\n=== Course Management System ===");
            System.out.println("1. Add Course");
            System.out.println("2. Delete Course");
            System.out.println("3. Search Course");
            System.out.println("4. Update Course");
            System.out.println("5. List All Courses");
            System.out.println("6. Logout");
            System.out.print("Enter your choice: ");
            
            try {
                choice = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                choice = 0; // Invalid choice
            }
            
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
                    System.out.println("Logging out. Goodbye!");
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        } while (choice != 6);
    }
}