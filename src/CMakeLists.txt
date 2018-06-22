# set some convenience variables
set(GOOGLE_BENCHMARK_PATH "${PROJECT_SOURCE_DIR}/../benchmark")
set(GOOGLE_TEST_PATH "${PROJECT_SOURCE_DIR}/../benchmark/googletest/")

# include current top level dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# add child directories
add_subdirectory(benches)
add_subdirectory(tests)
