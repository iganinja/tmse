cmake_minimum_required(VERSION 3.5)

add_library(TextEditor
    commands/command.h
    commands/command.cpp
    commands/undoredostack.h
    commands/undoredostack.cpp)

