/**
 * @file MovingPlatform.cpp
 *
 * @author Michael Dreon
 */

#include "pch.h"
#include "CollisionVisitor.h"
#include "MovingPlatform.h"


/**
 * Constructor
 * @param game Game this platform is in
 * @param filename Image file for this platform segment
 */
MovingPlatform::MovingPlatform(Game* game, const std::wstring& filename) : Platform(game, filename)
{
}

/**
 * Accept a collision visitor
 * @param visitor The collision visitor
 */
void MovingPlatform::Accept(CollisionVisitor* visitor)
{
    visitor->VisitPlatform(this);
}

/**
 * Updates the motion of the platform
 */
void MovingPlatform::SetMotion(double cx, double cy, double radius, double omega)
{
    mCenterX = cx;
    mCenterY = cy;
    mRadius = radius;
    mOmega = omega;
}

void MovingPlatform::Update(double elapsed)
{
    mAngle += mOmega*elapsed;

    //Circle position
    double px = mCenterX + std::cos(mAngle)*mRadius;
    double py = mCenterY + std::sin(mAngle)*mRadius;

    SetLocation(px,py);
}
