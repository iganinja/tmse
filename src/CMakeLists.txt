cmake_minimum_required(VERSION 3.5)

add_library(TextEditor STATIC
    commands/command.h
    commands/command.cpp
    commands/undoredostack.h
    commands/undoredostack.cpp
    texteditor.h
    texteditor.cpp)

include_directories(../olagarro/tasks/include)

add_subdirectory(../olagarro/tasks ./lib)

target_link_libraries(TextEditor
  PRIVATE tasks
)
