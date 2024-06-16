cmake_minimum_required(VERSION 3.29.2)
project(task01)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -g

    -fsanitize=address

    # -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

add_link_options(-fsanitize=address)

add_executable(task01 geometry_main.cpp
    src/vector.cpp
    src/point.cpp
    src/segment.cpp
    src/line.cpp
    src/ray.cpp
    src/polygon.cpp
    src/circle.cpp
    vector.h
    i_shape.h
    point.h
    segment.h
    line.h
    ray.h
    polygon.h
    circle.h)