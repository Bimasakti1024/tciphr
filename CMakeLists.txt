cmake_minimum_required(VERSION 3.10)
project(tciphr C)

set(CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(tciphr ${SOURCES})

target_compile_options(tciphr PRIVATE -Wall -Wextra)

target_compile_options(tciphr PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -fsanitize=address>
    $<$<CONFIG:Release>:-O3>
)

target_link_libraries(tciphr PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
)

target_link_libraries(tciphr PRIVATE m)