file(GLOB source_files
    "*.h"
    "*.cpp"
)

include_directories(include)

add_executable(kemter ${source_files})