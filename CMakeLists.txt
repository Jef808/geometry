set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_EXTENSIONS OFF)

# This will enable all analysis and treat warnings as errors
set(ENABLE_DEVELOPER_MODE TRUE CACHE BOOL "Enable 'developer mode'")

# Turn this off to let warnings be warnings
set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)

include(FetchContent)

# Neat packaging of all kinds of cumbersome things to config
FetchContent_Declare(_project_options
  URL https://github.com/cpp-best-practices/project_options/archive/refs/tags/v0.15.1.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

project(
  geometry
  VERSION 0.0.1
  DESCRIPTION "Examples and ideas I thought I should explore"
  HOMEPAGE_URL "https://github.com/Jef808/geometry"
  LANGUAGE CXX)

get_property(BUILDING_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(BUILDING_MULTI_CONFIG)
  if(NOT CMAKE_BUILD_TYPE)
    message(TRACE "Setting up multi-config build types")
    set(CMAKE_CONFIGURATION_TYPES
      Debug
      Release
      RelWithDebInfo
      CACHE_STRING "Enabled build types" FORCE)
  else()
    message(TRACE "Only one build type is considered")
    set(CMAKE_CONFIGURATION_TYPES
      ${CMAKE_BUILD_TYPE}
      CACHE STRING "Enabled build types" FORCE)
  endif()
endif()

include(${_project_options_SOURCE_DIR}/src/DynamicProjectOptions.cmake)

dynamic_project_options(
  # A list of headers to precompile
  PCH_HEADERS
  <vector>
  <string>
)


target_compile_features(project_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

# configure everything based on the CMake configure options
add_subdirectory(configured_files)
target_include_directories(project_options INTERFACE ${CMAKE_BINARY_DIR})

add_subdirectory(src)

# Adding the tests:
option(ENABLE_TESTING "Enable the tests" ON)
if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests.")
  add_subdirectory(test)
endif()

option(ENABLE_FUZZING "Enable the fuzz tests" OFF)
if(ENABLE_FUZZING)
  message("Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  add_subdirectory(fuzz_test)
endif()

