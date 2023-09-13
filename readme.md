## Linux build (Ubtuntu 22.04)

1. Install `sudo apt install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev` library
2. `mkdir build && cd build`
3. `cmake ..`
4. `make -j`
5. Run program from source directory: `./build/pacman_sdl`

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

