cmake_minimum_required(VERSION 3.5)

project(unhappy_evolution LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif ()

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
        preview_csv/main_view.cpp preview_csv/main_view.h preview_csv/main_view.ui
        preview_csv/file_getter/file_path_getter.cpp preview_csv/file_getter/file_path_getter.h
        preview_csv/parse_option/parse_option.cpp preview_csv/parse_option/parse_option.h preview_csv/parse_option/parse_option.ui
        preview_csv/data_model/custom_csv_model.cpp preview_csv/data_model/custom_csv_model.h
        tools/csv_line_parser.cpp tools/csv_line_parser.h
        preview_csv/preview_content/preview_content.cpp preview_csv/preview_content/preview_content.h preview_csv/preview_content/preview_content.ui preview_csv/file_summary/file_summary.cpp preview_csv/file_summary/file_summary.h preview_csv/file_summary/file_summary.ui)

## NOTE: Don't include the path in MACOSX_BUNDLE_ICON_FILE -- this is
## the property added to Info.plist
set(MACOSX_BUNDLE_ICON_FILE unhappy_mac_icon.icns)
#
## And this part tells CMake where to find and install the file itself
set(APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/static/unhappy_mac_icon.icns)
set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(unhappy_evolution
            ${PROJECT_SOURCES}
            )
else ()
    if (ANDROID)
        add_library(unhappy_evolution SHARED
                ${PROJECT_SOURCES}
                )
    elseif (MACOSX)
        add_executable(unhappy_evolution
                MACOSX_BUNDLE
                ${PROJECT_SOURCES}
                ${APP_ICON_MACOSX}
                )
    else ()
        add_executable(unhappy_evolution
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()

target_link_libraries(unhappy_evolution PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
