cmake_minimum_required(VERSION 3.28)

project(DDGameEngine LANGUAGES CXX)

add_executable(DDGameEngine
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/DDVector2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/DDGameEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/DDGameWorld.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/DDGameObject.cpp
)

target_include_directories(DDGameEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/core
    ${CMAKE_CURRENT_SOURCE_DIR}/include/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/include/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/include/renderer
)

target_compile_features(DDGameEngine PRIVATE cxx_std_17)

if(WIN32)
    target_sources(DDGameEngine PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/DDPlatformWindows.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/DDRendererWindows.cpp
    )

    target_link_libraries(DDGameEngine PRIVATE
        user32
        gdi32
    )
elseif(UNIX)
    find_package(X11 REQUIRED)

    target_sources(DDGameEngine PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/DDPlatformLinux.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/DDRendererLinux.cpp
    )

    target_link_libraries(DDGameEngine PRIVATE
        X11::X11
    )
else()
    message(FATAL_ERROR "Unsupported platform")
endif()