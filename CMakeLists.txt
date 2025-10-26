cmake_minimum_required(VERSION 3.16)
project(FileMonitoring LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC OFF)
set(CMAKE_AUTOUIC OFF)

set(QT_REQUIRED_COMPONENTS Core)
find_package(Qt6 QUIET COMPONENTS ${QT_REQUIRED_COMPONENTS})
if(NOT Qt6_FOUND)
  find_package(Qt5 REQUIRED COMPONENTS ${QT_REQUIRED_COMPONENTS})
  set(QT_VER 5)
else()
  set(QT_VER 6)
endif()

set(SRC
  main.cpp
  consolewriter.cpp
  filemanager.cpp
  logger.cpp
  monitoredfile.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(QT_VER EQUAL 6)
  target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)
endif()

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Копирование resources рядом с exe после сборки
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_CURRENT_SOURCE_DIR}/resources"
          "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
)
