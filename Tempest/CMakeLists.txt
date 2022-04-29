add_library(
    Tempest
    src/Tempest/Game.cpp
    src/Tempest/PulsarTankers.cpp 
    src/Tempest/FuseballTankers.cpp 
    src/Tempest/Fuseballs.cpp 
    src/Tempest/Tunel.cpp 
    src/Tempest/Pulsars.cpp 
    src/Tempest/Tankers.cpp 
    src/Tempest/Flippers.cpp 
    src/Tempest/Spikers.cpp 
    src/Tempest/Game.cpp 
    src/Tempest/Line.cpp 
    src/Tempest/Point.cpp 
    src/Tempest/TriangleMap.cpp 
    src/Tempest/Tube.cpp 
    src/Tempest/Color.cpp 
    src/Tempest/Level.cpp 
    src/Tempest/Enemy.cpp 
    src/Tempest/Player.cpp 
    src/Tempest/Collision.cpp 
    src/Tempest/Missile.cpp 
    src/Tempest/Timer.cpp 
    src/Tempest/CircleMap.cpp 
    src/Tempest/SquareMap.cpp 
    src/Tempest/TextRenderer.cpp

)

target_link_libraries(Tempest SDL2main SDL2-static)
target_include_directories(Tempest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
