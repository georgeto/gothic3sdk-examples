cmake_minimum_required(VERSION 3.16...3.24)

project(
  g3sdk-examples
  DESCRIPTION "Gothic 3 SDK Examples"
  LANGUAGES CXX)

# Use C++ 17.
set (CMAKE_CXX_STANDARD 17)

# Include and configure CPM package manager.
set(CPM_USE_NAMED_CACHE_DIRECTORIES ON)
include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)

# Fetch and setup gothic3sdk.
CPMAddPackage(
  NAME gothic3sdk
  OPTIONS
    "G3SDK_HEADER_ONLY OFF"
  GITHUB_REPOSITORY georgeto/gothic3sdk
  GIT_TAG 4296b8691d3eb5f18200cc528fd622ca4196a38e
)
include(${gothic3sdk_SOURCE_DIR}/cmake/Setup.cmake)

add_subdirectory(examples)

add_subdirectory(thirdparty EXCLUDE_FROM_ALL)
