FROM ubuntu:22.04

WORKDIR /ws

RUN apt update \
    && apt install -y \
    g++ \
    gcc \
    cmake \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-ttf-dev \
    libsdl2-mixer-dev

ADD cmake /ws/cmake
ADD CMakeLists.txt /ws/
ADD Fonts /ws/Fonts
ADD Sounds /ws/Sounds
ADD Textures /ws/Textures
ADD main.cpp /ws/
ADD Headers /ws/Headers

RUN mkdir -p build \
    && cd build \
    && cmake .. \
    && cmake --build . -j

