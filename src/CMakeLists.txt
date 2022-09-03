cmake_minimum_required(VERSION 3.5)

include_directories(../olagarro/tasks/include)
add_subdirectory(../olagarro/tasks ./lib)

include(FetchContent)

FetchContent_Declare(terminalcpp
  GIT_REPOSITORY https://github.com/jupyter-xeus/cpp-terminal
)

FetchContent_GetProperties(terminalcpp)
if(NOT terminalcpp_POPULATED)
  FetchContent_Populate(terminalcpp)
  add_subdirectory(${terminalcpp_SOURCE_DIR} ${terminalcpp_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_library(TextEditor STATIC
    commands/command.h
    commands/command.cpp
    commands/undoredostack.h
    commands/undoredostack.cpp
    texteditor.h
    texteditor.cpp
    document.h
    document.cpp
    fileutilities.h
    fileutilities.cpp
    view.h
    view.cpp)

target_link_libraries(TextEditor
  PRIVATE tasks
  PRIVATE cpp-terminal
)
