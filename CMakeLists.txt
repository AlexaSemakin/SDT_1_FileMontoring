cmake_minimum_required(VERSION 3.10)
project(FileManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

# Sources
set(SOURCES
    main.cpp
    filemanager.cpp
    monitoredfile.cpp
    consolewriter.cpp
    logger.cpp
)

set(HEADERS
    filemanager.h
    monitoredfile.h
    consolewriter.h
    logger.h
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)

# Ensure resources directory is available next to the built executable.
# If you don't have a resources/ directory, this step is harmless.
set(SRC_RES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SRC_RES_DIR}"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
    COMMENT "Copying resources to output folder"
)

# Optional: set working directory when running from IDE (Qt Creator)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
