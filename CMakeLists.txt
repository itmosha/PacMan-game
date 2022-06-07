cmake_minimum_required(VERSION 3.22)
project(NewProject)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -O3")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB cpphfiles
        "*.h"
        "*.cpp"
        )

add_executable(NewProject ${cpphfiles} Game.cpp Game.h TextureCreator.cpp TextureCreator.h GameObject.cpp GameObject.h Map.cpp Map.h CollisionChecker.cpp CollisionChecker.h Food.cpp Food.h TextObject.cpp TextObject.h Ghost.cpp Ghost.h Player.cpp Player.h Page.cpp Page.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf SDL2_mixer )
target_link_libraries(NewProject ${SDL2_LIBRARIES})

cmake_minimum_required(VERSION 3.7)
