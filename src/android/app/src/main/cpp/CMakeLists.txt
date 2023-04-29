# The minimum version of CMake required to build this native library.
cmake_minimum_required(VERSION 3.4.1)

# Library configuration
add_library(
        # Library name
        native-lib
        # Set as a shared library
        SHARED
        # Source file path
        native-lib.cpp
		rt_nonfinite.cpp
		rtGetInf.cpp
		rtGetNaN.cpp
		aware_emxAPI.cpp
		aware_emxutil.cpp
		aware.cpp
)

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -static-openmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -static-openmp")