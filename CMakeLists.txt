cmake_minimum_required(VERSION 3.6)

add_subdirectory(SDL)
install(DIRECTORY images DESTINATION .)
file(COPY images/flipper_RED.bmp images/flipper_GREEN.bmp images/flipper_PURPLE.bmp images/spiker_GREEN.bmp images/spiker_BLUE.bmp images/spiker_LIGHTBLUE.bmp images/spiker_RED.bmp images/tanker_PURPLE.bmp images/tanker_BLUE.bmp images/tanker_LIGHTBLUE.bmp images/missile.bmp images/s0.bmp images/s1.bmp images/s2.bmp images/s3.bmp images/s4.bmp images/s5.bmp images/s6.bmp images/s7.bmp images/s8.bmp images/s9.bmp DESTINATION images)

project(Tempest LANGUAGES CXX)

add_executable (${PROJECT_NAME} ./src/main.cpp)
target_sources(${PROJECT_NAME} PRIVATE ./src/Flippers.cpp ./src/Spikers.cpp ./src/Game.cpp ./src/Line.cpp ./src/main.cpp ./src/Point.cpp ./src/Triangle.cpp ./src/TriangleMap.cpp ./src/Tube.cpp ./src/Color.cpp ./src/Level.cpp ./src/Enemy.cpp ./src/Player.cpp ./src/Collision.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2-static)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
