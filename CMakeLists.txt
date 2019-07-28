cmake_minimum_required(VERSION 3.1)

project(mercatortile)

set (CMAKE_CXX_STANDARD 11)

# create the library
add_library(mercatortile SHARED src/MercatorTile.cpp)
target_include_directories(mercatortile
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# install
install (TARGETS mercatortile
        LIBRARY DESTINATION lib)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION include    
    )
