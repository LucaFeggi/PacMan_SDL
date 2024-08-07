cmake_minimum_required(VERSION 3.17)
project(PacMan_SDL)

# Find SDL
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(pacman_sdl
  src/main.cpp
  src/Board.cpp
  src/Blinky.cpp
  src/Clyde.cpp
  src/Entity.cpp
  src/Fruit.cpp
  src/Game.cpp
  src/Ghost.cpp
  src/Inky.cpp
  src/Pac.cpp
  src/Pinky.cpp
  src/Position.cpp
  src/Sound.cpp
  src/Texture.cpp
  src/Timer.cpp
)
target_include_directories(pacman_sdl
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/inc/)

target_link_libraries(pacman_sdl ${SDL2_LIBRARIES} SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer)

# Copy resources
add_custom_command(TARGET pacman_sdl POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/Fonts
  $<TARGET_FILE_DIR:pacman_sdl>/Fonts)
  
add_custom_command(TARGET pacman_sdl POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/Sounds
  $<TARGET_FILE_DIR:pacman_sdl>/Sounds)

add_custom_command(TARGET pacman_sdl POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/Textures
  $<TARGET_FILE_DIR:pacman_sdl>/Textures)