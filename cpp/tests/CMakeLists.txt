# Fetch and include Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Define your test target
add_executable(
    spatial_index_tests
    QuadtreeTests.cpp
    
    PointTests.cpp
 "KDTreeTests.cpp" "BruteForceTests.cpp")

# Link your test target against Google Test and your main application code
target_link_libraries(
    spatial_index_tests
    GTest::gtest_main
    spatial_index_lib  # Link against your main application library target
)

include(GoogleTest)
gtest_discover_tests(spatial_index_tests)
