cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories($ENV{HOME}/opt/boost_1_62_0 $ENV{HOME}/git/SFML/include)
link_directories($ENV{HOME}/opt/boost_1_62_0/stage/lib $ENV{HOME}/git/SFML/lib)
add_executable(multiplables main.cc sounds/202498__xtrsounder__small-crowd-cheering-and-clapping-at-party-2.cc)
target_link_libraries(multiplables boost_program_options boost_system boost_thread sfml-system sfml-audio)
