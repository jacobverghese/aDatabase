cmake_minimum_required(VERSION 3.3)
project(Homework_5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file (GLOB SOURCE_FILES *.cpp *.rpt *.csv)
add_executable(Homework_5 ${SOURCE_FILES})