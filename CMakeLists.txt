cmake_minimum_required(VERSION 3.10)
project(BouncyBall-linux)

set(CMAKE_CXX_STANDARD 17)
add_executable(BouncyBall
        src/main.cpp
        src/lib/stb_image.h
        src/base/texture.cpp src/base/texture.h
        src/base/shader.cpp src/base/shader.h
        src/base/drawable.cpp src/base/drawable.h
        src/base/moveable.cpp src/base/moveable.h
        src/animation/animation.cpp src/animation/animation.h
        src/animation/animation_rot.cpp src/animation/animation_rot.h
        src/animation/animation_bounce.cpp src/animation/animation_bounce.h
        src/ball/ball.cpp src/ball/ball.h
        src/ball/enemy.cpp src/ball/enemy.h
        #src/ball/player.cpp src/ball/player.h
        src/block/block.cpp src/block/block.h
        #src/block/spike_block.cpp src/block/spike_block.h
        #src/base/level.cpp src/base/level.h
        #src/base/game.cpp src/base/game.h
        )

target_include_directories(BouncyBall PUBLIC src/)
target_link_libraries(BouncyBall glfw)
target_link_libraries(BouncyBall GLEW)
target_link_libraries(BouncyBall GL)