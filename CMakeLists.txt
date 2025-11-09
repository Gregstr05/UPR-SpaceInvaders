cmake_minimum_required(VERSION 3.29)

project(SpaceInvaders)

add_executable(${PROJECT_NAME} 
	main.c
	SpaceInvaders.c
	SpaceInvaders.h
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_link_libraries(
		SpaceInvaders
		PRIVATE
		SDL2
		SDL2_image
)
