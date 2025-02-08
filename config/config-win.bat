@echo OFF
cd ..
mkdir build
mkdir build\win
cd build\win
cmake -G "Visual Studio 17 2022" -A x64 ..\..\Project

PAUSE
