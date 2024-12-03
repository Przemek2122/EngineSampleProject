# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
cmake_minimum_required (VERSION 3.8)

# Config
set(PROJECT_NAME "Project")
set(ENGINE_PATH "C:/Repos/Engine/Engine")

# Generated config
set(ENGINE_BUILD_PATH "${CMAKE_BINARY_DIR}/Engine_build")

# Enable Hot Reload for MSVC compilers if supported.
# TODO: Check if it works, should be enabled by child project
#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

# Define project
project("${PROJECT_NAME}")

# Add source files for prject
include_directories(${CMAKE_SOURCE_DIR}/Source/Public)
include_directories(${CMAKE_SOURCE_DIR}/Source/Private)

# Add executable
add_executable("${PROJECT_NAME}" "Source/Private/Project.cpp")

# Engine directory
add_subdirectory(${ENGINE_PATH} ${ENGINE_BUILD_PATH})

# Link engine
target_link_libraries("${PROJECT_NAME}" PRIVATE Engine)

