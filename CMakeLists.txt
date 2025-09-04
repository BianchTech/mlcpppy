cmake_minimum_required(VERSION 3.15)
project(mlcpppy VERSION 0.1 LANGUAGES CXX)

# Configura o padrão C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -------------------------------
# Biblioteca mlcpppy
# -------------------------------
file(GLOB_RECURSE MLCPP_SOURCES src/*.cpp src/*/*.cpp src/*/*/*.cpp)
add_library(mlcpppy SHARED ${MLCPP_SOURCES})

# Inclui os headers da biblioteca
target_include_directories(mlcpppy PUBLIC ${PROJECT_SOURCE_DIR}/include)

# -------------------------------
# Executável de exemplo
# -------------------------------
add_executable(example_main examples/main.cpp)

# Linka a biblioteca ao executável
target_link_libraries(example_main PRIVATE mlcpppy)
