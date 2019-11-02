include_directories(include)

file(GLOB source_files
    "*.h"
    "kemterdb.cpp"
    "main.cpp"
)

find_package(Boost REQUIRED)
add_executable(kemter ${source_files})
target_link_libraries(kemter PUBLIC pthread)
target_compile_features(kemter PRIVATE cxx_std_17)
# set_target_properties(kemter PROPERTIES CCX /usr/bin/clang++)