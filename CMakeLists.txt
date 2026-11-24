cmake_minimum_required(VERSION 3.28)
project(Auto-Cpp LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(Auto-Cpp src/main.c)
target_include_directories(Auto-Cpp PRIVATE include)
target_sources(Auto-Cpp PRIVATE 
    src/fileBuffer.c
    src/generateFile.c
    src/utils.c
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Auto-Cpp)

