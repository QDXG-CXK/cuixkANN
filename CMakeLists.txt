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

include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

include(FetchContent)
FetchContent_Declare(
    json URL
    https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_subdirectory(src/myLib)
add_subdirectory(src/faiss)

# add the executable
add_executable(
    cuixkANN
    src/main.cpp
    src/utils.cpp
    src/dataset.h
    src/test/test.cpp
    src/index/index_brute.h
    src/index/index_ivf.h
)

target_link_libraries(cuixkANN argparse myLib faiss nlohmann_json::nlohmann_json)