include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
    config.cpp
    new_proces.cpp
)

target_link_libraries(unit_tests
    PRIVATE
        auto_formater_lib
        GTest::gtest_main
        yaml-cpp
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
