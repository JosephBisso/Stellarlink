cmake_minimum_required(VERSION 3.14)

project(Stellarlink VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Qml gui LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Qml gui LinguistTools REQUIRED)

FIND_PACKAGE(Qt5QuickCompiler QUIET)
IF(Qt5QuickCompiler_FOUND AND NOT CMAKE_BUILD_TYPE MATCHES Debug AND NOT CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
  QTQUICK_COMPILER_ADD_RESOURCES(RESOURCES qml.qrc)
ELSE()
  SET(RESOURCES qml.qrc)
ENDIF()

set(TS_FILES Stellarlink_en_DE.ts)

set(PROJECT_SOURCES
        src/main.cpp
        qml.qrc
        src/touchable.h
        src/touchable.cpp
        src/ball.h
        src/ball.cpp
        src/stellarlink.h
        src/stellarlink.cpp
        src/STElement.cpp
        src/floor.h
        src/floor.cpp
        src/stellarengine.h
        src/stellarengine.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Stellarlink
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${RESOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Stellarlink APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Stellarlink SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Stellarlink
          ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

include_directories(src qml)

target_compile_definitions(Stellarlink
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(Stellarlink
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Qml)

target_include_directories(Stellarlink PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )

set_target_properties(Stellarlink PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(Stellarlink)
    qt_finalize_executable(Stellarlink)
endif()
