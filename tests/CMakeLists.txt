include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(UniversityTests
    person_and_traits_tests.cpp
)

target_link_libraries(UniversityTests PRIVATE
    gtest_main
    UniversityCore
)

include(GoogleTest)
gtest_discover_tests(UniversityTests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)