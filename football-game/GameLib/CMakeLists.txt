cmake_minimum_required(VERSION 3.29.0)
project(GameLib)

set(SOURCE_FILES
        pch.h
        MainFrame.cpp
        MainFrame.h
        GameView.cpp
        GameView.h
        Game.cpp
        Game.h
        Item.cpp
        Item.h
        ItemCoin10.cpp
        ItemCoin10.h
        ItemCoin100.cpp
        ItemCoin100.h
        ids.h
        Football.cpp
        Football.h
        Scoreboard.cpp
        Scoreboard.h
        PowerUp.cpp
        PowerUp.h
        Enemy.cpp
        Enemy.h
        GoalPost.cpp
        GoalPost.h
        Background.cpp
        Background.h
        CollisionVisitor.cpp
        CollisionVisitor.h
        Platform.cpp
        Platform.h
        Wall.cpp
        Wall.h
        FloatingText.cpp
        FloatingText.h
        MovingPlatform.cpp
        MovingPlatform.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
