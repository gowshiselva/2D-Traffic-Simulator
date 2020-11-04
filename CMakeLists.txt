
cmake_minimum_required(VERSION 3.14)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

set(CMAKE_CXX_STANDARD 11)


# Put the project early since modules might need to detect the compiler.
project(
    "TrafficSimulator" # This will exposed as the variable PROJECT_NAME.
    VERSION 1.0 # Used for installation and defines variables PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, and PROJECT_VERSION_TWEAK.
    LANGUAGES C CXX # Used to determine the languages to use based on file extensions
)


############################
##  Modules and scripts   ##
############################


#Bring the headers, 
include_directories(include)
 
#Can manually add the sources using the set command as follows:
#set(SOURCES src/traffic-simulator-main.cpp )
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
add_executable(traffic-simulator ${SOURCES})