cmake_minimum_required(VERSION 3.5)

include_directories(../olagarro/tasks/include)
add_subdirectory(../olagarro/tasks ./tasks_lib)

include_directories(../olagarro/cttasks/include)
add_subdirectory(../olagarro/cttasks ./cttasks_lib)

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
    widgets/mainwindow.h
    widgets/mainwindow.cpp
    widgets/mainmenu.h
    widgets/mainmenu.cpp
    widgets/mainmenuitem.h
    widgets/mainmenuitem.cpp
    widgets/menu.h
    widgets/menu.cpp
    widgets/menuentry.h
    widgets/menuentry.cpp

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

    settings.h
    settings.cpp
    localization.h
    localization.cpp

    document.h
    document.cpp
    fileutilities.h
    fileutilities.cpp)

include_directories(".")

target_link_libraries(TextEditor
  PRIVATE tasks
  PRIVATE cpp-terminal
)
