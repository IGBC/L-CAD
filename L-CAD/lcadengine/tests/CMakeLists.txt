# Set our source file scope for the library
set(LCADENGINE_TESTS 
    tests.c
)

# Define our library in cmake
add_executable(lcadenginetests ${LCADENGINE_TESTS})

target_link_libraries(lcadenginetests lcadengine)

# Dynamically linked libraries
target_link_libraries(lcadenginetests)

# Include the subdirectories to search for headers
target_include_directories(lcadenginetests PRIVATE ".")

