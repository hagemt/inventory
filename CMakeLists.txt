cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
project(Inventory C CXX)

## SETUP

# Force a build type to be declared
set(CMAKE_BUILD_TYPES "(None|Debug|Release|RelWithDebInfo|MinSizeRel)")
if(NOT CMAKE_BUILD_TYPE MATCHES "${CMAKE_BUILD_TYPES}")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "${CMAKE_BUILD_TYPES}" FORCE)
endif(NOT CMAKE_BUILD_TYPE MATCHES "${CMAKE_BUILD_TYPES}")
# Specify some default directories
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
# Include some default directories
include_directories("${CMAKE_BINARY_DIR}")
include_directories("${CMAKE_SOURCE_DIR}")

# Versioning info
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 1)
set(VERSION_TWEAK 0)
set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK}")
# Find git and fetch a hash
find_program(GIT_EXECUTABLE git)
if(GIT_EXECUTABLE)
  execute_process(COMMAND "${GIT_EXECUTABLE}" rev-parse -q HEAD
                  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                  OUTPUT_VARIABLE BUILD_HASH
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND "${GIT_EXECUTABLE}" submodule
                  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                  OUTPUT_VARIABLE BUILD_SUBMODULES
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
else(GIT_EXECUTABLE)
  set(BUILD_HASH "GIT_NOT_FOUND")
endif(GIT_EXECUTABLE)
# And warn about missing submodules
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/tclap/include")
  message(WARNING "You should fetch the submodules. Required: ${BUILD_SUBMODULES}")
  message("From ${CMAKE_SOURCE_DIR}, run: git submodule update --init")
endif(NOT EXISTS "${CMAKE_SOURCE_DIR}/tclap/include")

## CONFIGURATION

configure_file(inventory_constants.h.in "${CMAKE_BINARY_DIR}/inventory_constants.h")
configure_file(inventory_qt_interface.ui.in "${CMAKE_BINARY_DIR}/inventory_qt_interface.ui")
include_directories("${CMAKE_SOURCE_DIR}/tclap/include")
set(QT_MIN_VERSION 4.6.2)
list(APPEND QT_COMPONENTS "QtCore")
list(APPEND QT_COMPONENTS "QtGui")
if(BUILD_TESTING)
  list(APPEND QT_COMPONENTS "QtTest")
endif(BUILD_TESTING)
find_package(Qt4 ${QT_MIN_VERSION} COMPONENTS ${QT_COMPONENTS} REQUIRED)
set(QT_DONT_USE_QTCORE FALSE)
set(QT_DONT_USE_QTGUI FALSE)
if(BUILD_TESTING)
  set(QT_USE_QTTESTING TRUE)
endif(BUILD_TESTING)
include("${QT_USE_FILE}")
include_directories("${QT_INCLUDE_DIR}")

## COMPILE
  
# Source, headers to moc, UI, and resource files need prep
set(inventory_qt_interface_HEADERS inventory_qt_interface.h)
set(inventory_qt_interface_SOURCES inventory_qt_interface.cpp)
set(inventory_qt_interface_UI "${CMAKE_BINARY_DIR}/inventory_qt_interface.ui")
set(inventory_qt_interface_QRC inventory_qt_interface.qrc)
# Prepare each type of code
qt4_wrap_cpp(inventory_qt_interface_MOC_SOURCES ${lirch_qt_interface_HEADERS})
qt4_wrap_ui(inventory_qt_interface_UI_SOURCES ${lirch_qt_interface_UI})
qt4_add_resources(inventory_qt_interface_QRC_SOURCES ${lirch_qt_interface_QRC})
# Add details for this target
add_executable(inventory
        ${inventory_qt_interface_SOURCES}
	${inventory_qt_interface_MOC_SOURCES}
	${inventory_qt_interface_UI_SOURCES}
	${inventory_qt_interface_QRC_SOURCES})
target_link_libraries(inventory ${QT_LIBRARIES})
install(TARGETS inventory DESTINATION bin)

## EXTRA

# Include testing and packing facilities
include(CTest)
if(BUILD_TESTING)
  set(CTEST_PROJECT_NAME ${CMAKE_PROJECT_NAME})
endif(BUILD_TESTING)
include(CPack)
