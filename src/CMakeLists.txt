add_library(UniversityCore INTERFACE)

target_include_directories(UniversityCore INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(UniversityCore INTERFACE cxx_std_20)

target_compile_options(UniversityCore INTERFACE
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(UniversityApp
    main.cpp
)

target_link_libraries(UniversityApp PRIVATE UniversityCore)