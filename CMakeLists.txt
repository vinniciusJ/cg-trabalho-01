cmake_minimum_required(VERSION 4.0)
project(trabalho_01)

set(CMAKE_CXX_STANDARD 20)

include_directories("${CMAKE_SOURCE_DIR}/sdl2/x86_64-w64-mingw32/include")

add_executable(trabalho_01 main.cpp
        graphic-primitives/algorithmns/midpoint.cpp
        graphic-primitives/graphic-primitives.h
        graphic-primitives/algorithmns/cohen-sutherland.cpp
        graphic-primitives/algorithmns/polygon.cpp
        graphic-primitives/algorithmns/scanline.cpp
        utils/sdl-application.h
        utils/sdl-application.cpp
        demo.cpp
        demo.h)

target_link_libraries(trabalho_01
        mingw32
        "${CMAKE_SOURCE_DIR}/sdl2/x86_64-w64-mingw32/lib/libSDL2main.a"
        "${CMAKE_SOURCE_DIR}/sdl2/x86_64-w64-mingw32/lib/libSDL2.dll.a"
)

add_custom_command(TARGET trabalho_01 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/sdl2/x86_64-w64-mingw32/bin/SDL2.dll"
        $<TARGET_FILE_DIR:trabalho_01>
)