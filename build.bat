@echo off
echo Building Course Management System (C++)...

:: Check if g++ compiler is available
g++ --version >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: g++ compiler not found!
    echo Please install MinGW or add it to your PATH.
    pause
    exit /b 1
)

:: Compile the C++ program
echo Compiling main.cpp...
g++ -std=c++11 -O2 -o cms_cpp.exe main.cpp

:: Check if compilation was successful
if %errorlevel% equ 0 (
    echo Compilation successful!
    echo.
    echo To run the program:
    echo   cms_cpp.exe
    echo.
    echo Running the program now...
    echo ========================================
    cms_cpp.exe
) else (
    echo Compilation failed! Please check your code for errors.
)

pause