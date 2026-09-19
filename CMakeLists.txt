cmake_minimum_required(VERSION 3.20)
project(particle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Point CMake exactly to your local SFML installation path.
# Note: Use forward slashes (/) instead of backslashes (\) in CMake files.
set(SFML_DIR "C:/Users/prays/Desktop/SFML-3.1.0")

# 2. Find the SFML package using your predefined location
find_package(SFML 3.1.0 COMPONENTS graphics window system REQUIRED)

add_executable(particle main.cpp)

# 3. Link the targets directly
target_link_libraries(particle PRIVATE sfml-graphics sfml-window sfml-system)
