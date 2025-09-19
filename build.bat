@echo off
echo === Compiling Java files ===
javac *.java

if %errorlevel% neq 0 (
    echo Compilation failed. Check your code for errors.
    pause
    exit /b %errorlevel%
)

echo === Compilation successful ===
echo === Running the program ===
java main
pause