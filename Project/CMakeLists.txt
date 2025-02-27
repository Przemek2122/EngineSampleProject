# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
cmake_minimum_required (VERSION 3.8)

# Config
# Note: for android build 'main' as it expect library libmain.so
set(PROJECT_NAME "main")
set(ENGINE_PATH "C:/Repos/Engine/Engine")
set(PROJECT_VERSION 0.0.1)

# Define project
project("${PROJECT_NAME}" LANGUAGES CXX VERSION ${PROJECT_VERSION})

# Set the C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generated config
set(ENGINE_BUILD_PATH "${CMAKE_BINARY_DIR}/Engine_build")

# @TODO: Force diasbled lib gme due to android issues but it should be fixed
set(SDLMIXER_GME OFF CACHE BOOL "Disable support for GME music" FORCE)
set(SDLMIXER_GME_SHARED OFF CACHE BOOL "Disable dynamic loading of libgme" FORCE)

# Make sure engine compiles as library
set(ENGINE_BUILD_AS_LIBRARY ON CACHE BOOL "ON - build as library, OFF - build as executable" FORCE)

# Engine directory
add_subdirectory(${ENGINE_PATH} ${ENGINE_BUILD_PATH})

get_property(ENGINE_CONFIGURATION GLOBAL PROPERTY ENGINE_CONFIGURATION)
get_property(ENGINE_CONFIGURATION GLOBAL PROPERTY RUNTIME_LIB_EXT)

set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(PROJECT_SOURCE_PRIVATE_DIR "${PROJECT_SOURCE_DIR}/Private")
set(PROJECT_SOURCE_PUBLIC_DIR "${PROJECT_SOURCE_DIR}/Public")

# Collect source files
file(GLOB_RECURSE PROJECT_SOURCE_FILES_PUBLIC "${PROJECT_SOURCE_PUBLIC_DIR}/*.h")
file(GLOB_RECURSE PROJECT_SOURCE_FILES_PRIVATE "${PROJECT_SOURCE_PRIVATE_DIR}/*.cpp")

# Set directories
set(PROJECT_BIN_DIRECTORY_PATH "${CMAKE_BINARY_DIR}/bin")
set(PROJECT_LIB_DIRECTORY_PATH "${CMAKE_BINARY_DIR}/lib")

# For all targets:
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)

# Assets
get_property(ASSETS_DIR_NAME GLOBAL PROPERTY ASSETS_DIR_NAME)
set(ASSETS_DIR_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${ASSETS_DIR_NAME})
set(ASSETS_DIR_TARGET_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ASSETS_DIR_NAME})

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

# Depending on platform we want to add executable or build as library
if(NOT ANDROID)
	# Add executable
	add_executable("${PROJECT_NAME}" ${PROJECT_SOURCE_FILES_PRIVATE} ${PROJECT_SOURCE_FILES_PUBLIC})
else()
	# The SDL java code is hardcoded to load libmain.so on android, so we need to change EXECUTABLE_NAME
	set(EXECUTABLE_NAME main)
	
	# SHARED library
	add_library("${PROJECT_NAME}" SHARED 
		${PROJECT_SOURCE_FILES_PRIVATE}
		${PROJECT_SOURCE_FILES_PUBLIC}
	)
endif()

source_group("Public" FILES ${PROJECT_SOURCE_FILES_PUBLIC})
source_group("Private" FILES ${PROJECT_SOURCE_FILES_PRIVATE})

# Add source files for project
target_include_directories("${PROJECT_NAME}"
    PRIVATE ${PROJECT_SOURCE_DIR}
    PRIVATE ${PROJECT_SOURCE_PRIVATE_DIR}
    PUBLIC ${PROJECT_SOURCE_PUBLIC_DIR}
)

# Link engine
target_link_libraries("${PROJECT_NAME}" PRIVATE Engine)

# Copy Engine library to output directory
# Must be done after linking!
if(WIN32)
    # Windows - copy DLL
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Engine>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copying Engine DLL to output directory"
    )
elseif(APPLE)
    # macOS - copy dylib
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Engine>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copying Engine dylib to output directory"
    )
elseif(UNIX AND NOT ANDROID)
    # Linux - copy so
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Engine>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMENT "Copying Engine shared object to output directory"
    )
endif()
