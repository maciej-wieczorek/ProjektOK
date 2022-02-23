cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Set project name and version
set(PROJECT_NAME ProjektOK)
project(${PROJECT_NAME})

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug
    CACHE STRING
      "Choose the type of build (Debug or Release)" FORCE)
endif()

# Export compile commands for completion engines (optional)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Generate config.h
configure_file(include/config.h.in config.h)

# Find SFML shared libraries
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Compile executable
add_executable(${PROJECT_NAME}
  src/ContinuousGrid2D.cpp
  src/Grid.cpp
  src/Grid1D.cpp
  src/Grid2D.cpp
  src/main.cpp
  src/rulesetElementaryCA.cpp
  src/rulesetElementaryLoopedCA.cpp
  src/rulesetForest.cpp
  src/rulesetGameOfLifeClosedInTorus.cpp
  src/rulesetGameOfLifeDefault.cpp
  src/rulesetTheExpansion.cpp
  src/rulesetTheExpansionVonNeumann.cpp
  src/Utility.cpp
)

# Set include directory search paths
target_include_directories(${PROJECT_NAME} 
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

# Link executable to required SFML modules
target_link_libraries(${PROJECT_NAME} sfml-graphics)
