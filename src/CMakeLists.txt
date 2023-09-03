# CMakeList.txt : CMake project for spatial-index, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (spatial-index "Main.cpp" "Main.h" "Point.h" "Point.cpp" "QuadtreeNode.h" "QuadtreeNode.cpp" "Quadtree.h" "Quadtree.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET spatial-index PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
