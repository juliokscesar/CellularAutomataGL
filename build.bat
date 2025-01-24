@echo off
rem Create the "build" directory if it doesn't exist
if not exist build (
    mkdir build
)


rem Change to the "build" directory
cd build

rem Run CMake to generate the build files
cmake -A x64 -S ..

rem Build the project using CMake with 6 parallel jobs
cmake --build . -- /maxcpucount:6 
