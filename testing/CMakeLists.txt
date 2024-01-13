project(testing)

file(GLOB_RECURSE SOURCES Test*.cpp)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(Google_Tests_run ${SOURCES})

target_link_libraries(Google_Tests_run gtest gtest_main)