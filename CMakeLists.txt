cmake_minimum_required(VERSION 3.29)

project(SpaceInvaders)

add_executable(${PROJECT_NAME} 
	main.c
)

find_package(SDL2 REQUIRED)

target_link_libraries(
		SpaceInvaders
		PRIVATE
		SDL2
)
