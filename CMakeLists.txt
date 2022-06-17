cmake_minimum_required (VERSION 3.8)

project (NetControl)

set(SOURCE_EXE src/NetControl.cpp src/core/Windows/WinNetManager.cpp)

add_executable (NetControl ${SOURCE_EXE})
