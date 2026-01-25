add_executable(Benchmark
    main.cpp
    sort_benchmark.cpp
    search_benchmark.cpp
    generator_benchmark.cpp
)

target_link_libraries(Benchmark PRIVATE UniversityCore)