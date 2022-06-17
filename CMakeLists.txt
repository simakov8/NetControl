cmake_minimum_required (VERSION 3.8)

project ("NetControl")

add_executable (NetControl "src/NetControl.cpp"  "interfaces/NetManager.h" "src/core/Windows/WinNetManager.cpp" "include/core/Windows/WinNetManager.h")
