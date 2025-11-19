cmake_minimum_required(VERSION 3.29)

project(SpaceInvaders)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
	PUBLIC
		SpaceInvaders.h
		Enemy.h
		Player.h
		Helpers.h
	PRIVATE
		main.c
		SpaceInvaders.c
		Enemy.c
		Player.c
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_link_libraries(
		SpaceInvaders
		PRIVATE
		SDL2
		SDL2_image
)

target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)

file(GLOB IMAGES *.png)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Textures)
add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${IMAGES} ${CMAKE_BINARY_DIR}/Textures
)