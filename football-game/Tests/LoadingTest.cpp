/**
 * @file LoadingTest.cpp
 *
 * @author Michael Dreon
 */

#include <filesystem>
#include <fstream>
#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>
#include <MovingPlatform.h>

using namespace std;

string movingPlatformXML = R"(<?xml version="1.0" encoding="UTF-8"?>
<level width="1024" height="1024" start-y="572" start-x="468">
  <declarations>
    <background id="i001" image="background0.png"/>
    <movingplatform id="i007" left-image="metalLeft.png" mid-image="metalMid.png" right-image="metalRight.png"/>
  </declarations>
  <items>
    <background id="i001" x="512" y="512"/>
    <movingplatform id="i007" x="600" y="720" width="160" height="32"/>
  </items>
</level>
)";


TEST(LoadingTest, LoadsMovingPlatformFromXML)
{
    wxInitAllImageHandlers();

    std::filesystem::path tmp = std::filesystem::temp_directory_path() / "level_mptest.game";
    {
        std::ofstream out(tmp);
        ASSERT_TRUE(out.good());
        out << movingPlatformXML;
    }

    Game game;

    game.Load(tmp.wstring());

    EXPECT_EQ(game.CountItems(), 3);

    std::filesystem::remove(tmp);
}
