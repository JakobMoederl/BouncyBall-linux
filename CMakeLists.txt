cmake_minimum_required(VERSION 3.10)
project(BouncyBall-linux)

set(CMAKE_CXX_STANDARD 17)
add_executable(BouncyBall src/main.cpp)

target_link_libraries(BouncyBall -lglut)
target_link_libraries(BouncyBall -lGL)