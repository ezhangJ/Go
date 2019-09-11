cmake_minimum_required(VERSION 3.0)

project(Go)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/inc)
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

file(COPY ${CMAKE_SOURCE_DIR}/Assets DESTINATION "${CMAKE_SOURCE_DIR}/build")