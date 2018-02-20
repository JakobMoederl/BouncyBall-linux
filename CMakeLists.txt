cmake_minimum_required(VERSION 3.10)
project(BouncyBall-linux)

set(CMAKE_CXX_STANDARD 17)
add_executable(BouncyBall
        src/main.cpp

        src/drawable.cpp
        include/drawable.h
        src/moveable.cpp
        include/moveable.h
        src/shader.cpp
        include/shader.h
        )

target_include_directories(BouncyBall PUBLIC include/)
target_link_libraries(BouncyBall glfw)
target_link_libraries(BouncyBall GLEW)
target_link_libraries(BouncyBall GLU)
target_link_libraries(BouncyBall GL)
target_link_libraries(BouncyBall SOIL)