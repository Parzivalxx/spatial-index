# CMakeList.txt : CMake project for spatial-index, include source and define
# project specific logic here.

# Add source files to create a library target
add_library(
    spatial_index_lib
    "Main.h"
    "Main.cpp"
    "Point.h"
    "Point.cpp"
    "QuadtreeNode.h"
    "QuadtreeNode.cpp"
    "Quadtree.h"
    "Quadtree.cpp"
    "KDNode.h"
    "KDTree.h"
    "KDTree.cpp"
    "KDNodeComparator.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET spatial_index_lib PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(spatial_index_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(spatial_index Main.cpp  "KDNode.h" "KDTree.h" "KDTree.cpp")
target_link_libraries(spatial_index PRIVATE spatial_index_lib)
