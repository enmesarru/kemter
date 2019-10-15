cmake_minimum_required(VERSION 3.14.0)
project(kemter VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(src) # source files for the test

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tests)

#link_libraries(stdc++fs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
