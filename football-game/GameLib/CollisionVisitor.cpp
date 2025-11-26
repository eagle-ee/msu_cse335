/**
 * @file CollisionVisitor.cpp
 * @author Brennan Eagle
 */

#include "pch.h"
#include "CollisionVisitor.h"
#include "Game.h"
#include "Scoreboard.h"
#include "Platform.h"
#include "ItemCoin10.h"
#include "ItemCoin100.h"
#include "Enemy.h"
#include "GoalPost.h"
#include "Football.h"
#include "PowerUp.h"



/**
 * Handle collision with a platform (terrain)
 * @param platform The platform collided with
 */
void CollisionVisitor::VisitPlatform(Platform* platform)
{
    mLastWasTerrain = true;
    mShouldRemove = false;
    if (auto football = mGame->GetFootball())
    {
        football->CollisionResolve(platform);
    }
}

void CollisionVisitor::VisitWall(Wall* wall)
{
    mLastWasTerrain = true;
    mShouldRemove = false;
    if (auto football = mGame->GetFootball())
    {
        football->CollisionResolve(wall);
    }
}


/**
 * Handle collision with a coin 10
 * @param coin The coin collided with
 */
void CollisionVisitor::VisitCoin10(ItemCoin10* coin)
{
    mLastWasTerrain = false;
    mShouldRemove = true;

    auto scoreboard = mGame->GetScoreboard();
    if (scoreboard)
    {
        int value = 10 * mGame->GetCoinMultiplier();
        scoreboard->AddScore(value);
        mGame->AddFloatingText(wxString::Format("+%d", value), coin->GetX(), coin->GetY(), value);
    }
}

/**
 * Handle collision with a coin 10
 * @param coin The coin collided with
 */
void CollisionVisitor::VisitCoin100(ItemCoin100* coin)
{
    mLastWasTerrain = false;
    mShouldRemove = true;

    auto scoreboard = mGame->GetScoreboard();
    if (scoreboard)
    {
        int value = 100 * mGame->GetCoinMultiplier();
        scoreboard->AddScore(value);
        mGame->AddFloatingText(wxString::Format("+%d", value), coin->GetX(), coin->GetY(), value);
    }
}

/**
 * Handle collision with an enemy
 * @param enemy The enemy collided with
 */
void CollisionVisitor::VisitEnemy(Enemy* enemy)
{
    mLastWasTerrain = false;
    mShouldRemove = false;
    mGame->ReloadCurrentLevel();
}

/**
 * Handle collision with a goal
 * @param goal The goal collided with
 */
void CollisionVisitor::VisitGoalPost(GoalPost* goal)
{
    mLastWasTerrain = false;
    mShouldRemove = false;

    mGame->LoadNextLevel();
}

/**
 * Hande collision with a powerup
 * @param powerup The powerup collided with
 */
void CollisionVisitor::VisitPowerUp(PowerUp* powerup)
{
    mLastWasTerrain = false;
    mShouldRemove = false;
    
    // Activate only once; ignore subsequent collisions
    if (powerup->TryActivate())
    {
        // Permanently double remaining coins upon consumption
        mGame->DoubleCoinMultiplier();
        // Simple floating text like coin collection
        mGame->AddFloatingText("Power Up!", powerup->GetX(), powerup->GetY(), 0);
    }
}
