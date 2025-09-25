cmake_minimum_required(VERSION 3.15)
project(mlcpppy VERSION 0.1 LANGUAGES CXX)

# Configura o padrão C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------
# Flags de compilação (warnings + otimização)
# ---------------------------------
if (MSVC)
    # Warnings fortes no MSVC
    set(COMMON_FLAGS /W4 /permissive- /O2)
else()
    # GCC/Clang: warnings + performance
    set(COMMON_FLAGS -Wall -Wextra -Wpedantic -O3 -march=native)
endif()

# Aplica a todos os targets
add_compile_options(${COMMON_FLAGS})

# -------------------------------
# Biblioteca mlcpppy
# -------------------------------
file(GLOB_RECURSE MLCPP_SOURCES src/*.cpp src/*/*.cpp src/*/*/*.cpp)
add_library(mlcpppy SHARED ${MLCPP_SOURCES})

# Inclui os headers da biblioteca
target_include_directories(mlcpppy PUBLIC ${PROJECT_SOURCE_DIR}/include)

# -------------------------------
# Executáveis de exemplo
# -------------------------------
add_executable(example_main examples/main.cpp)
add_executable(example_instance examples/atributes_usage.cpp)
add_executable(example_binary_tree examples/example_binary_tree.cpp)

# Linka a biblioteca ao executável
target_link_libraries(example_main PRIVATE mlcpppy)
target_link_libraries(example_instance PRIVATE mlcpppy)
target_link_libraries(example_binary_tree PRIVATE mlcpppy)
