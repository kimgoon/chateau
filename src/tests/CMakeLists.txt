
set(GOOGLE_TEST_PATH "${PROJECT_SOURCE_DIR}/../benchmark/googletest/")
include_directories(${GOOGLE_TEST_PATH}/googletest/include)
link_directories   (${GOOGLE_BENCHMARK_PATH}/out/googletest/googlemock/gtest)

add_executable(test_myqueue test_myqueue.cpp)
add_executable(test_threading test_threading.cpp)
add_executable(test_smartpointers test_smartpointers.cpp)
add_executable(test_lambdas test_lambdas.cpp)
add_executable(test_allocs test_allocs.cpp)
#add_executable(test_streamserver test_streamserver.cpp)

