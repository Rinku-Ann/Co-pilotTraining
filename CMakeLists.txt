cmake_minimum_required(VERSION 3.14)

project(StudentManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(StudentApp
    main.cpp
    Student.cpp
    StudentManager.cpp
    StudentInput.cpp
)
target_include_directories(StudentApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
        GIT_SHALLOW TRUE
    )

    if(WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    FetchContent_MakeAvailable(googletest)

    add_executable(StudentTests
        tests/StudentTests.cpp
        tests/StudentManagerTests.cpp
        tests/StudentInputMockTests.cpp
        Student.cpp
        StudentManager.cpp
        StudentInput.cpp
    )
    target_include_directories(StudentTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    target_link_libraries(StudentTests PRIVATE
        GTest::gmock
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(StudentTests)
endif()
