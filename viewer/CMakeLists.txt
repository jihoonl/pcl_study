cmake_minimum_required(VERSION 2.8.3)
project(viewer)

find_package(PCL 1.8 REQUIRED)

add_definitions(${PCL_DEFINITIONS})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

include_directories(
  include
  ${PCL_INCLUDE_DIRS}
)

add_library(viewer
  src/viewer/double_viewer.cpp
  src/viewer/image_viewer.cpp
  src/viewer/cloud_viewer.cpp
)
target_link_libraries(viewer ${PCL_LIBRARIES})

add_executable(openni2
  src/main.cpp
)

target_link_libraries(openni2
  viewer
  ${PCL_LIBRARIES}
)
