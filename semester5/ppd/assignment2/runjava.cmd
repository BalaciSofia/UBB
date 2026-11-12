@echo off
rem uses the JDK 25 downloaded by IntelliJ (in %USERPROFILE%\.jdks), because the default java here is version 8
set "JAVA_EXE=java"
for /d %%d in ("%USERPROFILE%\.jdks\*25*") do set "JAVA_EXE=%%d\bin\java.exe"
"%JAVA_EXE%" -cp out\production\assignment2 Main %*
