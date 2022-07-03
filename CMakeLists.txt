cmake_minimum_required(VERSION 3.18)

project(pjoin LANGUAGES C CXX DESCRIPTION "Partitioned Joined Benchmark")

add_executable(pjoin main.cpp join.cpp pjoin.cpp hashtable.cpp)