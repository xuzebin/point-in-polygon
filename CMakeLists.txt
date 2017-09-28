cmake_minimum_required(VERSION 2.8)

project(PointInPolygon)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

add_executable(Example example.cpp)

target_link_libraries(Example ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
