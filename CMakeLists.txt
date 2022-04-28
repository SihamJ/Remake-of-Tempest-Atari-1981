cmake_minimum_required(VERSION 3.6)

add_subdirectory(SDL)
install(DIRECTORY images DESTINATION .)
file(COPY images/fuseballTanker_PURPLE.bmp images/pulsarTanker_PURPLE.bmp images/pulsar_LIGHTBLUE.bmp images/fuseball.bmp images/flipper_RED.bmp images/flipper_GREEN.bmp images/flipper_PURPLE.bmp images/spiker_GREEN.bmp images/spiker_BLUE.bmp images/spiker_LIGHTBLUE.bmp images/spiker_RED.bmp images/tanker_PURPLE.bmp images/tanker_BLUE.bmp images/tanker_LIGHTBLUE.bmp images/missile.bmp images/blaster_RED.bmp images/blaster_BLUE.bmp images/blaster_GREEN.bmp images/blaster_YELLOW.bmp images/logo.bmp images/gameover.bmp DESTINATION images)

project(Tempest LANGUAGES CXX)

add_executable (${PROJECT_NAME} ./src/main.cpp)
target_sources(${PROJECT_NAME} PRIVATE ./src/PulsarTankers.cpp ./src/FuseballTankers.cpp ./src/Fuseballs.cpp ./src/Tunel.cpp ./src/Pulsars.cpp ./src/Tankers.cpp ./src/Flippers.cpp ./src/Spikers.cpp ./src/Game.cpp ./src/Line.cpp ./src/main.cpp ./src/Point.cpp ./src/TriangleMap.cpp ./src/Tube.cpp ./src/Color.cpp ./src/Level.cpp ./src/Enemy.cpp ./src/Player.cpp ./src/Collision.cpp ./src/Missile.cpp ./src/Timer.cpp ./src/CircleMap.cpp ./src/SquareMap.cpp ./src/TextRenderer.cpp )
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2-static)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
