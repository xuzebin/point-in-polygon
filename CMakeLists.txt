cmake_minimum_required(VERSION 2.8)

project(PointInPolygon)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

add_executable(Example example.cpp)
add_executable(Example2 example2.cpp)

target_link_libraries(Example ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(Example2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
