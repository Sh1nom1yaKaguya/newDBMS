cmake_minimum_required(VERSION 3.25)
project(dbmsxzc)

set(CMAKE_CXX_STANDARD 17)
#包含当前目录
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#调用moc，uic，rcc编译qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
#设置qt的cmake目录
#这个目录包含了所有qt模块编译所需的cmake文件
set(CMAKE_PREFIX_PATH D:/QT5.14/5.14.2/mingw73_64)

#从上面的目录下寻找对应的qt模块
#find_package(Qt5Core)
#find_package(Qt5Quick)
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
#include_directories(.)

add_executable(dbmsxzc
        analysissql.cpp
        analysissql.h
        createdatabase.cpp
        createdatabase.h
        creattable.cpp
        creattable.h
        dataoperation.cpp
        dataoperation.h
        dbmanager.cpp
        dbmanager.h
        deletedatabase.cpp
        deletedatabase.h
        deletetable.cpp
        deletetable.h
        fieldmanager.cpp
        fieldmanager.h
        indexmanager.cpp
        indexmanager.h
        landing.cpp
        landing.h
        logdialog.cpp
        logdialog.h
        login.cpp
        login.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        managedatabysql.cpp
        managedatabysql.h
        managefieldbysql.cpp
        managefieldbysql.h
        managetablebysql.cpp
        managetablebysql.h
        privilegemanager.cpp
        privilegemanager.h
        registerw.cpp
        registerw.h
        resetpassword.cpp
        resetpassword.h
        selectdatabase.cpp
        selectdatabase.h
        tablemanageload.cpp
        tablemanageload.h
        tablemanager.cpp
        tablemanager.h)
#add_executable(untitled2 main.cpp)
target_link_libraries(dbmsxzc
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )
if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
