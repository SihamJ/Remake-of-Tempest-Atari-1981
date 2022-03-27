cmake_minimum_required(VERSION 3.6)

add_subdirectory(SDL)

project(Tempest LANGUAGES CXX)

add_executable (${PROJECT_NAME} ./src/main.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/headers})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2-static)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
