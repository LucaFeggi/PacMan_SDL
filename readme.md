## Linux build (Ubtuntu 23.04)

1. Install dependency development libraries `sudo apt install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev`
2. Configure CMake `cmake -S . -B build`
3. Build the project `cmake --build build/ -- j`
4. Run program from source directory: `./build/pacman_sdl`

## Build with Visual Studio Code
1. Install _CMake_ externsion
2. Open the command pallete (default F1) and search for `cmake`
3. Configure CMake with action `CMake: Configure`, you may be prompted to select a compiler toolchain
4. Build project with action `CMake: Build`
5. Run project with action `CMake: Run Without Debugging`

## Build docker

```sh
docker build -t pacman_sdl .
```

## Run pacman in docker with X11

> :warning: This may work differently depending on the system
```sh
xhost + local:docker
docker run -it --rm --env="DISPLAY" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" pacman_sdl /ws/build/pacman_sdl
```

