cmake_minimum_required(VERSION 3.6)

add_subdirectory(SDL)
project(Tempest LANGUAGES CXX)

install(DIRECTORY images DESTINATION .)
file(COPY images/fuseballTanker_PURPLE.bmp images/pulsar_LIGHTBLUE.bmp images/fuseball.bmp 
    images/flipper_RED.bmp images/flipper_GREEN.bmp images/flipper_PURPLE.bmp images/flipper_YELLOW.bmp images/spiker_GREEN.bmp images/spiker_BLUE.bmp 
    images/spiker_LIGHTBLUE.bmp images/spiker_RED.bmp images/tanker_PURPLE.bmp images/tanker_BLUE.bmp images/tanker_LIGHTBLUE.bmp 
    images/pulsarTanker_BLUE_LIGHTBLUE.bmp images/pulsarTanker_LIGHTBLUE_PURPLE.bmp images/pulsarTanker_YELLOW_BLUE.bmp 
    images/pulsarTanker_YELLOW_PURPLE.bmp images/fuseballTanker_BLUE.bmp images/fuseballTanker_LIGHTBLUE.bmp
    images/blaster_RED.bmp images/blaster_BLUE.bmp images/blaster_GREEN.bmp images/blaster_YELLOW.bmp 
    images/missile_ennemi.bmp images/missile_ennemi.bmp images/missile_player.bmp images/logo.bmp images/gameover.bmp DESTINATION images)

install(DIRECTORY Audio DESTINATION .)
file(COPY Audio/shoot.wav Audio/enemy_shot.wav Audio/gameover.wav Audio/menu.wav Audio/next_level.wav Audio/score.wav Audio/supperzapper.wav  DESTINATION Audio)

add_subdirectory(Tempest-lib)
add_subdirectory(Tempest)


