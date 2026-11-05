cmake_minimum_required(VERSION 3.14)

project(StudentManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(StudentManagementSystem
    src/main.cpp
    src/Student.cpp
    src/StudentManagement.cpp
    src/StudentManagementApp.cpp
)
target_include_directories(StudentManagementSystem PRIVATE include)

include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
        GIT_SHALLOW TRUE
    )

    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    FetchContent_MakeAvailable(googletest)

    add_executable(StudentManagementTests
        tests/StudentTests.cpp
        tests/StudentManagerTests.cpp
        tests/StudentManagementMockTests.cpp
        src/Student.cpp
        src/StudentManagement.cpp
        src/StudentManagementApp.cpp
    )
    target_include_directories(StudentManagementTests PRIVATE include tests)
    target_link_libraries(StudentManagementTests PRIVATE GTest::gmock GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(StudentManagementTests)
endif()