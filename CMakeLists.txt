cmake_minimum_required(VERSION 3.21.1)

set(BUILD_QDS_COMPONENTS ON CACHE BOOL "Build design studio components")

project(ProtectClientApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


find_package(QT NAMES Qt6 COMPONENTS Gui Qml Quick QuickControls2 Sql)
find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick QuickControls2 Sql)

# To build this application you need Qt 6.2.0 or higher
if (Qt6_VERSION VERSION_LESS 6.2.0)
message(FATAL_ERROR "You need Qt 6.2.0 or newer to build the application.")
endif()

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/data SRC_DATA_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/data/db SRC_DATA_DB_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/util SRC_UTIL_FILES)

qt_add_executable(${CMAKE_PROJECT_NAME}
    ${SRC_FILES}
    ${SRC_DATA_FILES}
    ${SRC_DATA_DB_FILES}
    ${SRC_UTIL_FILES}
)

# qt_standard_project_setup() requires Qt 6.3 or higher. See https://doc.qt.io/qt-6/qt-standard-project-setup.html for details.
if (${QT_VERSION_MINOR} GREATER_EQUAL 3)
qt6_standard_project_setup()
endif()

qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::QuickControls2
    Qt${QT_VERSION_MAJOR}::Sql
)

#add_subdirectory(vender)

#add_dependencies(${CMAKE_PROJECT_NAME} sqlite3)

if (${BUILD_QDS_COMPONENTS})
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif ()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)
