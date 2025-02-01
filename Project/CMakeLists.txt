# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
cmake_minimum_required (VERSION 3.8)

# Config
set(PROJECT_NAME "Project")
set(ENGINE_PATH "C:/Repos/Engine/Engine")
set(PROJECT_VERSION 0.0.1)

# Define project
project("${PROJECT_NAME}" LANGUAGES CXX VERSION ${PROJECT_VERSION})

# Set the C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generated config
set(ENGINE_BUILD_PATH "${CMAKE_BINARY_DIR}/Engine_build")

# Engine directory
add_subdirectory(${ENGINE_PATH} ${ENGINE_BUILD_PATH})

get_property(ENGINE_CONFIGURATION GLOBAL PROPERTY ENGINE_CONFIGURATION)

# Set directories
set(PROJECT_CURRENT_BIN_DIRECTORY_PATH "${CMAKE_BINARY_DIR}/bin/${ENGINE_CONFIGURATION}")
set(PROJECT_CURRENT_LIB_DIRECTORY_PATH "${CMAKE_BINARY_DIR}/lib/${ENGINE_CONFIGURATION}")

message(STATUS "PROJECT_CURRENT_BIN_DIRECTORY_PATH: '${PROJECT_CURRENT_BIN_DIRECTORY_PATH}'")
message(STATUS "PROJECT_CURRENT_LIB_DIRECTORY_PATH: '${PROJECT_CURRENT_LIB_DIRECTORY_PATH}'")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_CURRENT_BIN_DIRECTORY_PATH})
set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_CURRENT_BIN_DIRECTORY_PATH})
set(CMAKE_PDB_OUTPUT_DIRECTORY ${PROJECT_CURRENT_BIN_DIRECTORY_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_CURRENT_BIN_DIRECTORY_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_CURRENT_BIN_DIRECTORY_PATH})

set(LIBRARY_OUTPUT_PATH ${PROJECT_CURRENT_LIB_DIRECTORY_PATH})
set(CMAKE_LIBRARY_PATH ${PROJECT_CURRENT_LIB_DIRECTORY_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_CURRENT_LIB_DIRECTORY_PATH})

# Assets
get_property(ASSETS_DIR_NAME GLOBAL PROPERTY ASSETS_DIR_NAME)
set(ASSETS_DIR_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${ASSETS_DIR_NAME})
set(ASSETS_DIR_TARGET_PATH ${PROJECT_CURRENT_BIN_DIRECTORY_PATH}/${ASSETS_DIR_NAME})

# Get assets
file(GLOB ASSET_FILES_TO_COPY "${ASSETS_DIR_SOURCE_PATH}/*")

# Print assets dirs
message(STATUS "COPY PROJECT ASSETS: '${ASSETS_DIR_SOURCE_PATH}', DESTINATION: '${ASSETS_DIR_TARGET_PATH}'")

# Attempt to copy files with a fallback for permission issues
foreach(file ${ASSET_FILES_TO_COPY})
    get_filename_component(filename ${file} NAME)
    if (NOT filename MATCHES "^\\..*" AND EXISTS ${file})
        file(COPY ${file} DESTINATION ${ASSETS_DIR_TARGET_PATH} FILE_PERMISSIONS OWNER_READ OWNER_WRITE)
    else()
        message(WARNING "Could not access file: ${file} (skipping)")
    endif()
endforeach()

# Enable Hot Reload for MSVC compilers if supported.
# TODO: Check if it works, should be enabled by child project
#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

# Add executable
add_executable("${PROJECT_NAME}" "Source/Private/Project.cpp" "Source/Private/ProjectEngine.cpp")

# Add source files for project
target_include_directories("${PROJECT_NAME}"
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source/Public
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source/Private
)

# Link engine
target_link_libraries("${PROJECT_NAME}" PRIVATE Engine)
