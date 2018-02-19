cmake_minimum_required(VERSION 3.10)
project(BouncyBall-linux)

set(CMAKE_CXX_STANDARD 17)
add_executable(BouncyBall
        src/main.cpp

        src/ball.cpp
        src/block.cpp
        src/drawable.cpp
        src/enemy.cpp
        src/game.cpp
        src/good_smiley.cpp
        src/level.cpp
        src/moveable.cpp
        src/player.cpp
        src/spike_block.cpp
        src/stone_block.cpp

        include/ball.h
        include/block.h
        include/drawable.h
        include/enemy.h
        include/game.h
        include/good_smiley.h
        include/level.h
        include/moveable.h
        include/player.h
        include/spike_block.h
        include/stone_block.h
        )

target_include_directories(BouncyBall PUBLIC include/)
target_link_libraries(BouncyBall glfw)
target_link_libraries(BouncyBall GLEW)
target_link_libraries(BouncyBall GLU)
target_link_libraries(BouncyBall GL)
target_link_libraries(BouncyBall SOIL)