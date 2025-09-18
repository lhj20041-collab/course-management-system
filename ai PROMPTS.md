## docs/ai_prompts.md

```markdown
# AI Assistance Documentation

## Prompt 1: C++ to Java Conversion
*Prompt:* 
"Convert this C++ console application to Java. The program is a course management system with user authentication and CRUD operations on courses. Use arrays for storage instead of collections. Maintain the same file formats (users.txt and courses.txt). The Java version should be console-based and produce an executable JAR."

*AI Response:*
Suggested using BufferedReader/FileReader for file input and PrintWriter/FileWriter for file output. Recommended using Scanner for console input and Java-style array declarations.

*Decision:* Accepted the overall approach but modified the file I/O implementation to better match the C++ version's behavior.

---

## Prompt 2: Handling Global Arrays in Java
*Prompt:*
"How should I handle the global arrays from C++ in Java without using advanced collections?"

*AI Response:*
Suggested using static arrays in the main class as the equivalent of global arrays in C++.

*Decision:* Accepted this approach as it maintains the same data structure paradigm as the C++ version while following Java conventions.

---

## Prompt 3: File I/O Implementation
*Prompt:*
"What's the best way to implement file reading and writing in Java for text files similar to C++ ifstream and ofstream?"

*AI Response:*
Recommended using try-with-resources statements with BufferedReader and PrintWriter for clean resource management.

*Decision:* Accepted this approach but added additional error handling to match the C++ version's robustness.

---

## Prompt 4: User Input Handling
*Prompt:*
"How to handle console input in Java similar to C++ cin with validation?"

*AI Response:*
Suggested using Scanner class with nextLine() and exception handling for numeric input.

*Decision:* Accepted the Scanner approach but added trim() operations to handle whitespace consistently with the C++ version.

---

## Manual Modifications Made
1. Added more robust error handling for file operations
2. Implemented case-insensitive search functionality
3. Added input validation and trimming for all user inputs
4. Created build scripts for both C++ and Java versions
5. Added comprehensive comments for better code documentation

---

## Lessons Learned
1. Java requires more explicit exception handling than C++
2. String comparison in Java uses .equals() instead of == operator
3. Java's try-with-resources provides cleaner resource management than manual cleanup
4. Java arrays are objects with length property, unlike C++ arrays
5. Cross-language conversion requires careful attention to subtle differences in behavior