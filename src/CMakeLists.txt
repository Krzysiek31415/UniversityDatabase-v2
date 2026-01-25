add_library(UniversityCore)

target_sources(UniversityCore PRIVATE
    domain/Student.cpp
)

target_include_directories(UniversityCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(UniversityCore PUBLIC cxx_std_20)

target_compile_options(UniversityCore PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(UniversityApp
    main.cpp
)

target_link_libraries(UniversityApp PRIVATE UniversityCore)