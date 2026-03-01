add_library(UniversityCore STATIC 
    domain/Person.cpp
    ui/PersonFormatter.cpp
    ui/ConsoleView.cpp
    repository/infrastructure/InMemoryPersonRepository.cpp
    services/PersonQueryService.cpp
    domain/PESEL.cpp
)

target_include_directories(UniversityCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(UniversityCore PUBLIC cxx_std_20)

target_compile_options(UniversityCore PUBLIC
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(UniversityApp
    main.cpp
)

target_link_libraries(UniversityApp PRIVATE UniversityCore)