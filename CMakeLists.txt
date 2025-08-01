cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(ElytraGliding)

include(FetchContent)
FetchContent_Declare(
    matplotplusplus
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
    GIT_TAG v1.2.2
)
FetchContent_MakeAvailable(matplotplusplus)

include_directories(src/)
add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC matplot)