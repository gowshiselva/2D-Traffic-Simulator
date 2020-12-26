
cmake_minimum_required(VERSION 3.13)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

set(CMAKE_CXX_STANDARD 14)

#IF you use your own of SFML uncomment these:
set(SFML_INCLUDE_DIR "/home/workspace/2D-Traffic-Simulator/include/SFML")
set(Python3_Numpy_INCLUDE_DIRS "/usr/local/lib/python3.5/dist-packages")
# set(SFML_LIBRARY_DIR "/home/vin/download/SFML-2.5.1-Compiled/lib")
#set(SFML_DIR/home/workspace/2D-Traffic-Simulator/cmake")

#PYTHON3_EXECUTABLE:FILEPATH=/root/miniconda3/bin/python3

# Put the project early since modules might need to detect the compiler.
project(
    "TrafficSimulator" # This will exposed as the variable PROJECT_NAME.
    VERSION 1.0 # Used for installation and defines variables PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, and PROJECT_VERSION_TWEAK.
    LANGUAGES C CXX # Used to determine the languages to use based on file extensions
)




#find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)





############################
##  Modules and scripts   ##
############################


#Bring the headers, 
include_directories(include ${SFML_INCLUDE_DIR}
                            ${PYTHON_INCLUDE_DIRS}
                            ${NUMPY_INCLUDE_DIRS}
                            )
 
#Can manually add the sources using the set command as follows:
#set(SOURCES src/traffic-simulator-main.cpp )
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

#SET env
message("THING:" $ENV{THING})

if(DEFINED ENV{THING})
 message(STATUS "THING environment variable defined")
    # some more commands
endif()


# Enable additional warnings and debug mode
set (CMAKE_CXX_FLAGS "-g -W -pedantic -Wno-dev")
set(CMAKE_BUILD_TYPE Debug)
add_executable(traffic-simulator ${SOURCES})
target_compile_options(traffic-simulator PRIVATE -Wall -Wextra -pedantic -Werror)
target_link_libraries(traffic-simulator sfml-system sfml-window sfml-graphics sfml-audio )

find_package(Python3 COMPONENTS Interpreter Development Numpy)
message("Python_FOUND:${Python3_FOUND}")
message("Python_VERSION:${Python3_VERSION}")
message("Python_Development_FOUND:${Python3_Development_FOUND}")
message("Python_LIBRARIES:${Python3_LIBRARIES}")


message("Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message("Numpy_FOUND: ${Python3_NumPy_FOUND}")
message("Python3_NumPy_INCLUDE_DIRS: ${Python3_NumPy_INCLUDE_DIRS}")

if (Python3_FOUND)
  message(STATUS "Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
  message(STATUS "_Python3_EXECUTABLE: ${_Python3_EXECUTABLE}\n")
 
  message(STATUS "Python3_INCLUDE_DIR: ${Python3_INCLUDE_DIR}")
  message(STATUS "_Python3_INCLUDE_DIR: ${_Python3_INCLUDE_DIR}\n")
 
  message(STATUS "Python3_LIBRARY_DEBUG: ${Python3_LIBRARY_DEBUG}")
  message(STATUS "_Python3_LIBRARY_DEBUG: ${_Python3_LIBRARY_DEBUG}\n")
 
  message(STATUS "Python3_LIBRARY_RELEASE: ${Python3_LIBRARY_RELEASE}")
  message(STATUS "_Python3_LIBRARY_RELEASE: ${_Python3_LIBRARY_RELEASE}\n")
 
  message(STATUS "Python3_NumPy_INCLUDE_DIR: ${Python3_NumPy_INCLUDE_DIR}")
  message(STATUS "_Python3_NumPy_INCLUDE_DIR: ${_Python3_NumPy_INCLUDE_DIR}\n")
endif()




target_include_directories(traffic-simulator PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS} ${Python_NumPy_INCLUDE_DIRS})
target_link_libraries(traffic-simulator Python3::Python Python3::Numpy)
