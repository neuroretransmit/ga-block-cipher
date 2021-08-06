cmake_minimum_required(VERSION 3.8.2)
project("ga-block-cipher")

# We require C++17 or higher.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

#find_package(Boost 1.71 COMPONENTS program_options iostreams REQUIRED )
#include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(tests)
#target_link_libraries(iching LINK_PUBLIC ${Boost_LIBRARIES})
