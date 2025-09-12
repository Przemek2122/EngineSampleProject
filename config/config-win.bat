@echo OFF

set INITIAL_SAVED_DIR=%CD%

REM Create build dir and switch to it
cd ..
mkdir build
mkdir build\win
cd build\win

REM Use CMAKE to generate project
cmake -G "Visual Studio 17 2022" -A x64 ..\..\Project

cd /d "%INITIAL_SAVED_DIR%"
cd ..

REM Prebuild every engine project so user can skip this.
echo Try to build all necesary engine projects
cmake --build build\win --target BuildAllEngine
echo All engine builds complete!

REM Prebuild every project subprojects so user can skip this.
echo Try to build all necesary projects
cmake --build build\win --target BuildAllProject
echo All builds complete!

REM Finally open Visual Studio
REM Note: You could change this part to IDE of your choice
echo try to open Visual studio
cmake --build build\win --target open_vs
echo Visual studio show now open

PAUSE
