cmake_minimum_required(VERSION 3.24)
project(setup
    VERSION 0.1.0
    LANGUAGES CXX
)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
option(DEV_MODE "Enbale debug print" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}
    src/processInfo.cpp
    src/project_type.cpp
    src/stringHelper.cpp
    src/programs.cpp
    src/templateLoader.cpp
    src/config.cpp
    src/main.cpp
    src/language.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<BOOL:${DEV_MODE}>:DEV_MODE>
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/formatter
)

include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
)
FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp) # The library or executable that require yaml-cpp library


target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2

        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

