cmake_minimum_required(VERSION 2.6)
project(computer_club)

set(CMAKE_CXX_STANDARD 17)

include_directories("${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/src/computer_club"
	"${PROJECT_SOURCE_DIR}/src/events")

file(GLOB computerclub_src 
	"${PROJECT_SOURCE_DIR}/src/*.h"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/computer_club/*.h"
	"${PROJECT_SOURCE_DIR}/src/computer_club/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/events/*.h"
	"${PROJECT_SOURCE_DIR}/src/events/*.cpp")

add_executable(computer_club ${computerclub_src})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "computerclub")