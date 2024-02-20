project(testing)

file(GLOB_RECURSE SOURCES Test*.cpp)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(${CMAKE_PROJECT_NAME}_test ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}_test gtest gtest_main)