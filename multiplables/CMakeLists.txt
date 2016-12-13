cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories($ENV{HOME}/opt/boost_1_62_0 $ENV{HOME}/git/SFML/include)
link_directories($ENV{HOME}/opt/boost_1_62_0/stage/lib $ENV{HOME}/git/SFML/lib)
add_executable(multiplables main.cc)
target_link_libraries(multiplables boost_program_options sfml-system sfml-audio)
