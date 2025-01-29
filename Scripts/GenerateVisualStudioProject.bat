cd ..
mkdir VisualStudio
cd VisualStudio

REM Generate VS 2022
cmake -G "Visual Studio 17" ../Project

PAUSE