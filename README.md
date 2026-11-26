# Auto-Cpp

## What's that

Auto-cpp is a tool that helps you coding in C++. The aim of the tool is to automaticly write .cpp files depening on their header files. When you modify or create a class declaration, it will automaticly write empty definitions in the cpp file, saving time on boring copy/pasting

## Currently

Auto-cpp stands at its 0.1.0 version. In this version, it creates a new cpp file whenever a .h file is created. Header files with .hpp are not yet supported. The newly created file does only have the include line to its header file, and nothing else.

## Install

Clone the project to your computer. Then run : 

`cmake --build build`

Your version of Cmake must be 3.28 or greater

The exetutable will be in here : `build/bin/Auto-cpp`

## How to use it

Before you start coding, open a terminal and run the executable like this

`Auto-cpp path_to_listen_from path_to_modify_from`

Every second, it will detect when a file is modified, added, or deleted in the path you let it listen from. It will output information accordingly in the terminal. It will also apply changes in the path you set to modify, according to the "Currently" topic.


