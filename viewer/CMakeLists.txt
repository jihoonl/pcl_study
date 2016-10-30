cmake_minimum_required(VERSION 2.8.3)
project(viewer)

find_package(PCL 1.8 REQUIRED)

add_definitions(${PCL_DEFINITIONS})

include_directories(
  include
  ${PCL_INCLUDE_DIRS}
)

add_executable(viewer
  src/viewer.cpp
)

add_executable(openni2
  src/openni2_viewer.cpp
)
target_link_libraries(openni2
  ${PCL_LIBRARIES}
)

target_link_libraries(viewer
  ${PCL_LIBRARIES}
)
