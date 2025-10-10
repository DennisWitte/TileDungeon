cmake_minimum_required(VERSION 3.10)

project(TileDungeon)

cmake_minimum_required(VERSION 3.16)
project(TileDungeon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

add_subdirectory(raylib)

# ⬇️ Stelle sicher, dass das Executable zuerst definiert wird
add_executable(
    TileDungeon Main.cpp
    Game.cpp

    Engine/Entity.cpp
    Engine/Component.cpp
    Engine/Scene.cpp
    Engine/Transform.cpp
    Engine/Camera.cpp
    Engine/MeshRenderer.cpp
    Engine/SceneManager.cpp
    Engine/TextRenderer.cpp
    
    Game/Player.cpp
    Game/CharacterController.cpp
    Game/JungleScene.cpp
    )

# ⬇️ Jetzt darfst du raylib (und andere libs) anhängen
target_link_libraries(TileDungeon raylib)

# Optional für Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(TileDungeon m pthread dl rt X11)
endif()
