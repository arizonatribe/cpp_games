cmake_minimum_required(VERSION 3.7)
project(Pong)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall -ggdb ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
	"src/"
	${SDL2_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
)

set(SOURCE_FILES
	"src/main.cpp"
	"src/game.cpp"
)

add_executable(Pong ${SOURCE_FILES})

# string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Pong
	${SDL2_LIBRARY}
	${SDL2_TTF_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
)
