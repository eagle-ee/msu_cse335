/**
 * @file ScoreboardTest.cpp
 *
 * @author Brennan Eagle
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Scoreboard.h>
#include <wx/stopwatch.h>

TEST(ScoreboardTest, Initialization)
{
    Scoreboard scoreboard;

    ASSERT_EQ(0, scoreboard.GetScore());
}


TEST(ScoreboardTest, AddScore)
{
    Scoreboard scoreboard;
    wxStopWatch stopWatch;
    scoreboard.Initialize(&stopWatch);

    ASSERT_EQ(0, scoreboard.GetScore());

    scoreboard.AddScore(10);
    ASSERT_EQ(10, scoreboard.GetScore());

    scoreboard.AddScore(25);
    ASSERT_EQ(35, scoreboard.GetScore());
}

TEST(ScoreboardTest, TimeDecrement)
{
    Scoreboard scoreboard;
    wxStopWatch stopWatch;
    scoreboard.Initialize(&stopWatch);

    ASSERT_EQ(0, scoreboard.GetScore());

    scoreboard.AddScore(10);
    ASSERT_EQ(10, scoreboard.GetScore());

    scoreboard.Update(2.0);
    ASSERT_LT(scoreboard.GetScore(), 10); //score should be less than 10 after elapsing
}