/**
 * @file Football.cpp
 *
 * @author Michael Dreon
 *
 * The football in our game
 */


#include "pch.h"
#include <string>
#include "Football.h"
#include "Game.h"

using namespace std;

/// Football Filename
const wstring FootballImageLeftName = L"images/footballLeft.png";
const wstring FootballImageMidName = L"images/footballMid.png";
const wstring FootballImageRightName = L"images/footballRight.png";

/**
 * Constructor
 * @param game the game this football lives in
 */
Football::Football(Game* game) : Item(game, FootballImageMidName)
{
    mItemBitmapLeft = game->GetCachedImage(FootballImageLeftName);
    mItemBitmapMid = game->GetCachedImage(FootballImageMidName);
    mItemBitmapRight = game->GetCachedImage(FootballImageRightName);
}

/**
 * Sets the velocity of the football
 * @param x The x velocity
 */
void Football::SetXVelocity(double x)
{
    mXVelocity = x;
}

/**
 * Sets the velocity of the football
 * @param y The y velocity
 */
void Football::SetYVelocity(double y)
{
    mYVelocity = y;
}

/**
 * This checks if the football has collided with an object
 * @param item The item we check a collision with
 * @return if we collided
 */
bool Football::CollisionTest(Item* item)
{
    // Border for the item
    auto itemLeft = item->GetX() - item->GetWidth() / 2;
    auto itemRight = item->GetX() + item->GetWidth() / 2;
    auto itemTop = item->GetY() - item->GetHeight() / 2;
    auto itemBottom = item->GetY() + item->GetHeight() / 2;

    // For us
    auto ourLeft = GetX() - GetWidth() / 2;
    auto ourRight = GetX() + GetWidth() / 2;
    auto ourTop = GetY() - GetHeight() / 2;
    auto ourBottom = GetY() + GetHeight() / 2;

    // Test for all of the non-collision cases
    if (ourRight < itemLeft ||  // Completely to the left
        ourLeft > itemRight ||  // Completely to the right
        ourTop > itemBottom ||  // Completely below
        ourBottom < itemTop)    // Completely above
    {
        return false;
    }

    return true;
}

/**
 * Handles collision with an object
 * @param item The item we have collided with
 */
/**
void Football::OnCollide(Item& item)
{
    CollisionResolve(item);
}*/

void Football::CollisionResolve(Item* item)
{
    double itemTop = item->GetY() - item->GetHeight() / 2;
    double itemBottom = item->GetY() + item->GetHeight() / 2;
    double itemLeft = item->GetX() - item->GetWidth() / 2;
    double itemRight = item->GetX() + item->GetWidth() / 2;

    double thisTop = GetY() - GetHeight() / 2;
    double thisBottom = GetY() + GetHeight() / 2;
    double thisLeft = GetX() - GetWidth() / 2;
    double thisRight = GetX() + GetWidth() / 2;

    if (thisBottom <= itemTop || thisTop >= itemBottom ||
        thisRight <= itemLeft || thisLeft >= itemRight)
    {
        return;
    }

    double overlapFromTop = thisBottom - itemTop;       /// The overlap from the top of the item
    double overlapFromBottom = itemBottom - thisTop;    /// The overlap from the bottom of the item
    double overlapFromLeft = thisRight - itemLeft;      /// The overlap from the left of the item
    double overlapFromRight = itemRight - thisLeft;     /// The overlap from the right of the item

    double newY = GetY();
    double newX = GetX();

    mGrounded = false;
    mStandingOn = nullptr;

    enum MinSide {leftS=0, rightS, topS, bottomS}; /// The direction of the minimum overlap from the view of the item
    MinSide minSide=leftS;
    std::vector<double> overlaps = {overlapFromLeft, overlapFromRight, overlapFromTop, overlapFromBottom};

    // Find min side
    for (int i = 0; i<4; i++)
    {
        if (overlaps[i]<overlaps[minSide])
        {
            minSide = (MinSide)i;
        }
    }

    switch (minSide)
    {
    case leftS:
        newX = itemLeft - GetWidth()/2;
        break;
    case rightS:
        newX = itemRight + GetWidth()/2;
        break;
    case topS:
        newY = itemTop - GetHeight()/2;
        mYVelocity = 0;
        mGrounded = true;
        mStandingOn = item;
        break;
    case bottomS:
        newY = itemBottom + GetHeight()/2;
        break;

    }

    SetLocation(newX,newY);
}


/**
 * Updates position based off of velocity
 * @param elapsed
 */
void Football::Update(double elapsed)
{
    double x = GetX();
    x += mXVelocity*elapsed;
    double y = GetY();
    if (!mGrounded)
    {
        mYVelocity += mGravity*elapsed;
        if (mYVelocity>mTerminalVelocity)
        {
            mYVelocity = mTerminalVelocity;
        }
    }
    y += mYVelocity*elapsed;


    SetLocation(x, y);

    if (mStandingOn != nullptr)
    {
        double dxPlatform = mStandingOn->GetX() - mStandingOn->GetPrevX();
        double dyPlatform = mStandingOn->GetY() - mStandingOn->GetPrevY();

        SetLocation(GetX() + dxPlatform, GetY() + dyPlatform);
    }

    if (mXVelocity > 0)
    {
        this->SetBitmap(mItemBitmapRight);
    } else if (mXVelocity < 0)
    {
        this->SetBitmap(mItemBitmapLeft);
    } else
    {
        this->SetBitmap(mItemBitmapMid);
    }
}


