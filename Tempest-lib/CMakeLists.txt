add_library(
    Tempest-lib
    src/Game.cpp
    src/PulsarTankers.cpp 
    src/FuseballTankers.cpp 
    src/Fuseballs.cpp 
    src/Tunel.cpp 
    src/Pulsars.cpp 
    src/Tankers.cpp 
    src/Flippers.cpp 
    src/Spikers.cpp 
    src/Game.cpp 
    src/GameOver.cpp
    src/Line.cpp 
    src/Point.cpp 
    src/TriangleMap.cpp 
    src/Tube.cpp 
    src/Color.cpp 
    src/Level.cpp 
    src/Enemy.cpp 
    src/Player.cpp 
    src/Collision.cpp 
    src/Missile.cpp 
    src/Pause.cpp
    src/Menu.cpp
    src/Timer.cpp 
    src/CircleMap.cpp 
    src/SquareMap.cpp 
    src/TextRenderer.cpp
    src/SDLWrapper.cpp
    src/Audio.cpp

)

target_link_libraries(Tempest-lib SDL2main SDL2-static)
target_include_directories(Tempest-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
