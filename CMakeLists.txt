cmake_minimum_required(VERSION 3.5)

project(mercatortile)

set (CMAKE_CXX_STANDARD 11)

add_library(mercatortile STATIC src/MercatorTile.cpp)
target_include_directories(mercatortile
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)


add_executable(example examples/example.cpp)
target_link_libraries(example
    PRIVATE
        mercatortile
)



