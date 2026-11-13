cmake_minimum_required(VERSION 3.30)
project(practice_final2_microbial_ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(practice_final2_microbial_
        main.cpp
        Biologist.cpp
        Biologist.h
        Bacterium.cpp
        Bacterium.h
        Repository.cpp
        Repository.h
        Subject.cpp
        Subject.h
        Observer.cpp
        Observer.h
        Service.cpp
        Service.h
        biologistwindow.cpp
        biologistwindow.h
        biologistwindow.ui
)

target_link_libraries(practice_final2_microbial_ PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

if (WIN32)
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms"
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms"
    )

    foreach(QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        )
    endforeach()
endif()