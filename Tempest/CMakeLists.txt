add_library(
    Tempest
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
    src/Timer.cpp 
    src/CircleMap.cpp 
    src/SquareMap.cpp 
    src/TextRenderer.cpp

)

target_link_libraries(Tempest SDL2main SDL2-static)
target_include_directories(Tempest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
