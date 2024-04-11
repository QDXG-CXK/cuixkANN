cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

option(BUILD_CPU_ONLY "Build CPU only components. Applies to RAFT ANN benchmarks currently" OFF)

set(lang_list "CXX")
if(NOT BUILD_CPU_ONLY)
  list(APPEND lang_list "CUDA")
endif()

# set the project name
project(cuixkANN
    VERSION 0.0
    LANGUAGES ${lang_list}
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/myLib)

# add the executable
add_executable(
    ann
    src/main.cpp
    src/utils.cpp
    src/test/test.cpp
)

target_link_libraries(ann myLib)