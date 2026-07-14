cmake_minimum_required(VERSION 4.2)

project(
    auto-formater
    VERSION 0.8.0
    DESCRIPTION "C++ project that loads your formatter into an active project"
    LANGUAGES CXX
)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(
        CMAKE_BUILD_TYPE Debug
        CACHE STRING "Choose the build type"
        FORCE
    )

    set_property(
        CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel
    )
endif()

option(DEV_MODE "Enable debug printing" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/log.cpp
    src/processInfo.cpp
    src/project_type.cpp
    src/stringHelper.cpp
    src/programs.cpp
    src/templateLoader.cpp
    src/config.cpp
    src/language.cpp
    src/gitignore.cpp
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
    GIT_TAG master
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(yaml-cpp)

# Shared warning settings for this project's targets
add_library(project_warnings INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(project_warnings INTERFACE
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
    $<$<CONFIG:Debug>:-O0>
    $<$<CONFIG:Debug>:-g3>
    )
endif()

# Application logic
add_library(auto_formater_lib STATIC
    src/processInfo.cpp
    src/project_type.cpp
    src/stringHelper.cpp
    src/programs.cpp
    src/templateLoader.cpp
    src/config.cpp
    src/language.cpp
    src/gitignore.cpp
    src/log.cpp
    src/helper.cpp
)

target_compile_features(auto_formater_lib
    PUBLIC
        cxx_std_23
)

target_include_directories(auto_formater_lib
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)

target_compile_definitions(auto_formater_lib
    PRIVATE
        $<$<BOOL:${DEV_MODE}>:DEV_MODE>
)

target_link_libraries(auto_formater_lib
    PUBLIC
        yaml-cpp::yaml-cpp
    PRIVATE
        project_warnings
)

################
# Executable
################
add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        $<$<BOOL:${DEV_MODE}>:DEV_MODE>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        auto_formater_lib
        project_warnings
)
##########
# Tests
##########
include(CTest)

# if(BUILD_TESTING)
#     add_subdirectory(tests)
# endif()

###################
# Installation
###################
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Packaging
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VENDOR "Kronborg")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")

set(
    CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}"
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CPACK_GENERATOR "TGZ;ZIP;DEB")
else()
    set(CPACK_GENERATOR "TGZ;ZIP")
endif()

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kronborg")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
