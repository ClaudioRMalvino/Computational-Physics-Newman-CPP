cmake_minimum_required(VERSION 3.31)
project(Comp_Physics_Newman_cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Explicitly enable C++23 for GCC
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
endif()

# Set conda environment path
set(Python3_ROOT_DIR "/home/claudio/miniconda3/envs/comp_phys")
set(Python3_FIND_STRATEGY LOCATION)

# Find Python and numpy for matplotlib-cpp
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

# Print found Python info for debugging
message(STATUS "Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message(STATUS "Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")

# Add matplotlib-cpp include directory
set(MATPLOTLIB_CPP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/matplotlib-cpp")

# Automatically find all .cpp files and create executables
file(GLOB_RECURSE ALL_CPP_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/chapter_*/*.cpp"
)

foreach(cpp_file ${ALL_CPP_FILES})
    # Get filename without extension for executable name
    get_filename_component(exe_name ${cpp_file} NAME_WE)
    get_filename_component(dir_name ${cpp_file} DIRECTORY)
    get_filename_component(parent_dir ${dir_name} NAME)

    # Create unique executable name (parent_dir_exe_name)
    set(full_exe_name "${parent_dir}_${exe_name}")

    # Create executable - ONLY include the specific cpp file
    add_executable(${full_exe_name} ${cpp_file}
            chapter_5/integration_methods.cpp
            chapter_5/integration_methods.h

    )

    # Link Python libraries to ALL executables (whether they use plotting or not)
    target_link_libraries(${full_exe_name} Python3::Python Python3::NumPy)

    message(STATUS "Created executable: ${full_exe_name}")
endforeach()
