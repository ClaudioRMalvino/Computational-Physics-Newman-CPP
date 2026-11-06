cmake_minimum_required(VERSION 3.25)
project(Newman_Computational_Physics)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE EXERCISE_FILES "src/**/*.cpp")

include_directories(include)

find_package(OpenMP REQUIRED)

foreach(FILE_PATH ${EXERCISE_FILES})
    get_filename_component(FILE_NAME ${FILE_PATH} NAME_WE)

    add_executable(${FILE_NAME} ${FILE_PATH})
    target_link_libraries(${FILE_NAME} PRIVATE OpenMP::OpenMP_CXX)
endforeach()
