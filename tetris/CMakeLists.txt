cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Flecs as a static library
add_library(flecs STATIC lib/flecs.c)
target_include_directories(flecs PUBLIC lib)

# Gather all source files recursively
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/modules/*/*.cpp"
    "src/modules/*/*/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "src/*.hpp"
    "src/modules/*/*.hpp"
    "src/modules/*/*/*.hpp"
    "src/utils/*.hpp"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        src
        src/modules
        src/utils
)

# Link libraries
# System-wide Raylib (no find_package needed)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib m pthread dl flecs)

# Optional: platform-specific defines
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_WINDOWS)
elseif(UNIX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_UNIX)
endif()
