cmake_minimum_required(VERSION 3.29.2)
project(task03)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -g

    -fsanitize=address
    # -fsanitize=leak

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
# add_link_options(-fsanitize=leak)

add_executable(task03 vector_public_test.cpp # vector_public_test.cpp
    vector.h
    vector.tpp
)