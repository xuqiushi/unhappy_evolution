cmake_minimum_required(VERSION 3.5)

project(unhappy_evolution LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES unhappy_evolution_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        Unhappy.cpp
        Unhappy.h
        unhappy.ui
        ${TS_FILES}
        file_encoding_transform/drag_in.cpp file_encoding_transform/drag_in.h file_encoding_transform/drag_in.ui file_encoding_transform/drag_in_style.h
        file_encoding_transform/result_view.cpp file_encoding_transform/result_view.h file_encoding_transform/result_view.ui
        file_encoding_transform/main_view.cpp file_encoding_transform/main_view.h file_encoding_transform/main_view.ui
        preview_csv/main_view.cpp preview_csv/main_view.h preview_csv/main_view.ui)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(unhappy_evolution
            ${PROJECT_SOURCES}
            )
else ()
    if (ANDROID)
        add_library(unhappy_evolution SHARED
                ${PROJECT_SOURCES}
                )
    else ()
        add_executable(unhappy_evolution
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()

target_link_libraries(unhappy_evolution PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
