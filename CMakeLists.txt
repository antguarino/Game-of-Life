rit_add_executable(game_of_life
    SOURCES
        app_gol.cpp
)

target_link_libraries(game_of_life
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)