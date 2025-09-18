@echo off
echo Building Course Management System JAR...

if not exist manifest.txt (
    echo Creating manifest file...
    echo Main-Class: CMS > manifest.txt
)

echo Building JAR file...
jar cfm cms_java.jar manifest.txt *.class

if exist "cms_java.jar" (
    echo Build successful!
    echo.
    echo To run the application:
    echo 1. Double-click cms_java.jar, OR
    echo 2. Run: java -jar cms_java.jar
) else (
    echo Build failed! Make sure:
    echo 1. You've compiled your Java code in BlueJ
    echo 2. The CMS.class file exists in this folder
)

pause