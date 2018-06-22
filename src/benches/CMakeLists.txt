include_directories(${GOOGLE_BENCHMARK_PATH}/include/)
link_directories   (${GOOGLE_BENCHMARK_PATH}/out/src/)

add_executable(bench_queues bench_queues.cpp)

target_link_libraries(bench_queues
    benchmark)


