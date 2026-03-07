cmake_minimum_required(VERSION 4.2)
project(off_yourself)
add_executable(${PROJECT_NAME} src/main.cpp src/costume.cpp src/functions.cpp src/game.cpp src/gameObject.cpp src/sprite.cpp src/window.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_directories(${PROJECT_NAME} PRIVATE lib)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    freeglut 
    opengl32 
    glu32
)