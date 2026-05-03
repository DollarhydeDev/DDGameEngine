cmake_minimum_required(VERSION 3.28)

project(DDEngine LANGUAGES CXX)
find_package(X11 REQUIRED)
add_executable(DDEngine 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/DDEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/DDRenderer.cpp
)

target_include_directories(DDEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/include/renderer
)
target_link_libraries(DDEngine PRIVATE X11::X11)
