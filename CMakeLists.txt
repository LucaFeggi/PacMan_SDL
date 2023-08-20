cmake_minimum_required(VERSION 3.17)
project(PacMan_SDL)

# Find SDL
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(pacman_sdl)
target_include_directories(pacman_sdl PRIVATE Headers)
target_sources(
  pacman_sdl PRIVATE
  Sources/main.cpp
  Sources/Globals.cpp
  Sources/Texture.cpp
  Sources/Timer.cpp
  Sources/Position.cpp
  Sources/Entity.cpp
  Sources/Pac.cpp
  Sources/Ghost.cpp
  Sources/Blinky.cpp
)
target_link_libraries(pacman_sdl ${SDL2_LIBRARIES} SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer)
