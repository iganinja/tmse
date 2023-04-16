cmake_minimum_required(VERSION 3.5)

include_directories(../olagarro/tasks/include)
add_subdirectory(../olagarro/tasks ./tasks_lib)

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

FetchContent_Declare(utf8cpp
  GIT_REPOSITORY https://github.com/nemtrif/utfcpp
)

FetchContent_GetProperties(utf8cpp)
if(NOT utf8cpp_POPULATED)
  FetchContent_Populate(utf8cpp)
  set(UTF8_INSTALL OFF CACHE BOOL "" FORCE)
  add_subdirectory(${utf8cpp_SOURCE_DIR} ${utf8cpp_BINARY_DIR} EXCLUDE_FROM_ALL)
  include_directories(${utf8cpp_SOURCE_DIR}/source)
endif()

add_library(TextEditor STATIC
    commands/command.h
    commands/command.cpp
    commands/undoredostack.h
    commands/undoredostack.cpp

    widgets/widget.h
    widgets/widget.cpp
    widgets/layouts.h
    widgets/layouts.cpp
    widgets/fillerbox.h
    widgets/fillerbox.cpp
    widgets/mainmenu.h
    widgets/mainmenu.cpp
    widgets/mainmenuitem.h
    widgets/mainmenuitem.cpp
    widgets/menu.h
    widgets/menu.cpp
    widgets/menuentry.h
    widgets/menuentry.cpp
    widgets/welcomebackground.h
    widgets/welcomebackground.cpp
    widgets/filestabs.h
    widgets/filestabs.cpp

    utils/vector2d.h
    utils/size.h
    utils/terminalutils.h
    utils/terminalutils.cpp
    utils/exception.h
    utils/exception.cpp
    utils/event.h

    tasks/mainmenutasks.h
    tasks/mainmenutasks.cpp
    tasks/waitkey.h
    tasks/waitkey.cpp
    tasks/tasksutils.h
    tasks/tasksutils.cpp
    tasks/menutasks.h
    tasks/menutasks.cpp
    tasks/mainwindowtasks.h
    tasks/mainwindowtasks.cpp
    tasks/waitevent.h

    settings.h
    settings.cpp
    localization.h
    localization.cpp

    document.h
    document.cpp
    fileutilities.h
    fileutilities.cpp
    mainwindow.h
    mainwindow.cpp)

include_directories(".")

target_link_libraries(TextEditor
  PRIVATE tasks
  PRIVATE cpp-terminal
)
