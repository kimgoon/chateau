
add_executable(test_myqueue test_myqueue.cpp)

set(GOOGLE_BENCHMARK_PATH "${PROJECT_SOURCE_DIR}/../benchmark")
include_directories(${GOOGLE_BENCHMARK_PATH}/include/)
link_directories   (${GOOGLE_BENCHMARK_PATH}/out/src/)

add_executable(bench_queues bench_queues.cpp)

target_link_libraries(bench_queues
    benchmark)

set(GOOGLE_TEST_PATH "${PROJECT_SOURCE_DIR}/../benchmark/googletest/")
include_directories(${GOOGLE_TEST_PATH}/googletest/include)
link_directories   (${GOOGLE_BENCHMARK_PATH}/out/googletest/googlemock/gtest)

add_executable(test_threading test_threading.cpp)
add_executable(test_smartpointers test_smartpointers.cpp)
add_executable(test_lambdas test_lambdas.cpp)
add_executable(test_allocs test_allocs.cpp)
#add_executable(test_streamserver test_streamserver.cpp)
