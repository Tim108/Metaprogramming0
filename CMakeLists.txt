cmake_minimum_required(VERSION 3.7)
project(Metaprogramming0)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES symm.cpp symm.h Vector.cpp Vector.h matrix.cpp matrix.h)
add_executable(Metaprogramming0 ${SOURCE_FILES})

set(BOOST_ROOT /home/tim/boost_1_64_0)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})