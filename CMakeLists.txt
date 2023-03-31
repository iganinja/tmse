cmake_minimum_required(VERSION 3.5)

project(TMSE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TMSE
    main.cpp)

include(FetchContent)

FetchContent_Declare(terminalcpp
  GIT_REPOSITORY https://github.com/jupyter-xeus/cpp-terminal
)

FetchContent_GetProperties(terminalcpp)
if(NOT terminalcpp_POPULATED)
  FetchContent_Populate(terminalcpp)
  add_subdirectory(${terminalcpp_SOURCE_DIR} ${terminalcpp_BINARY_DIR} EXCLUDE_FROM_ALL)
  include_directories(${terminalcpp_SOURCE_DIR})
endif()

include_directories(./olagarro/tasks/include)

add_subdirectory(src)
include_directories(src)

target_link_libraries(TMSE
  PRIVATE TextEditor
)

set_target_properties(TMSE PROPERTIES LINK_SEARCH_START_STATIC 1)
set_target_properties(TMSE PROPERTIES LINK_SEARCH_END_STATIC 1)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static -lstdc++ -lpthread")

