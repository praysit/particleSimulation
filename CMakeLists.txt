cmake_minimum_required(VERSION 3.20)
project(particleSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1. Point CMake exactly to the folder containing SFMLConfig.cmake
set(SFML_DIR "C:/Users/prays/Desktop/SFML-3.1.0/lib/cmake/SFML")

# 2. Tell CMake to find the package using the directory above
find_package(SFML 3.1.0 COMPONENTS Graphics Window System REQUIRED NO_DEFAULT_PATH)
add_executable(particleSimulation main.cpp)

# 3. Link the targets using the modern SFML 3.x namespace
target_link_libraries(particleSimulation PRIVATE SFML::Graphics SFML::Window SFML::System)