cmake_minimum_required(VERSION 3.18)

project(pjoin LANGUAGES C CXX DESCRIPTION "Partitioned Joined Benchmark")

include(FetchContent)
FetchContent_Declare(
  libdivide
  GIT_REPOSITORY https://github.com/ridiculousfish/libdivide.git
  GIT_TAG        b322221677351ebb11f0a42fe9a9a2794da5bfe5 # release-5.0.0
)
FetchContent_MakeAvailable(libdivide)

add_executable(pjoin main.cpp join.cpp pjoin.cpp hashtable.cpp)
target_compile_features(pjoin PRIVATE cxx_std_20)
target_link_libraries(pjoin PRIVATE libdivide)