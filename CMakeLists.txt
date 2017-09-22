CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(GameOfLife)

#Für std=c++11
set(CMAKE_CXX_STANDARD 11)

#add include directory
include_directories(include)

#find source files
file(GLOB SOURCES "src/*.cpp")

#add executeable
add_executable(GameOfLife ${SOURCES})

#link directories
link_directories(/usr/local/lib)

#link SDL
find_library(
	SDL
	NAMES "SDL2"
	PATH "/usr/local/lib"
	PATH_SUFFIXES lib
)

if(SDL)
	message("-- libSDL2 found: " ${SDL})
	include_directories(/usr/local/include/SDL2)
	target_link_libraries(GameOfLife ${SDL_LIBRARIES} -lSDL2)
else(NOT CURL)
	message(FATAL_ERROR "-- SDL2 NOT FOUND")
endif()

find_package( Boost 1.65 COMPONENTS program_options REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
target_link_libraries( GameOfLife ${Boost_LIBRARIES} -lboost_program_options)
