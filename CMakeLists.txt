cmake_minimum_required(VERSION 2.8)

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

project( ContrastAndHist )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( Hist Hist.cpp )
target_link_libraries( Hist ${OpenCV_LIBS} )
add_executable( Contrast Contrast.cpp )
target_link_libraries( Contrast ${OpenCV_LIBS} )

add_executable( CreateImages CreateImages.cpp )
target_link_libraries( CreateImages ${OpenCV_LIBS} )

