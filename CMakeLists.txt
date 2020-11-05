cmake_minimum_required(VERSION 3.17)

project(sqlQt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES

        source/mainwindow.cpp
        source/FactoryWindow.cpp
        source/DropWidget.cpp
        source/MaterialWidget.cpp)

set(HEADER_FILES

        header/mainwindow.h
        header/FactoryWindow.h
        header/DropWidget.h
        header/MaterialWidget.h)


find_package(Qt5 COMPONENTS Widgets Core Sql REQUIRED)

#qt5_wrap_ui(QT_TEST_UI_HEADERS source/main.ui)


add_executable(sqlQt
        main.cpp
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )

target_link_libraries(sqlQt PRIVATE Qt5::Widgets Qt5::Core Qt5::Sql)
