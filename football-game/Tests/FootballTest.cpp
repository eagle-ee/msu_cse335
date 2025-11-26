/**
 * @file FootballTest.cpp
 *
 * @author Michael Dreon
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Football.h>
#include <Game.h>

TEST(FootballTest, ExistTest)
{
    Game game;
    Football football(&game);
}

TEST(FootballTest, FootballVelocityTest)
{
    Game game;
    Football football(&game);
    football.SetYVelocity(1600);
    ASSERT_EQ(football.GetYVelocity(),500);
}