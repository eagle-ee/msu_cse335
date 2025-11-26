/**
 * @file Enemy.cpp
 * @author Eduardo Jimenez & Saransh S
 */

#include "pch.h"
#include "Enemy.h"
#include "CollisionVisitor.h"

/**
 * Constructor
 * @param game amd file of image
 */
Enemy::Enemy(Game* game, const std::wstring& filename) : Item(game, filename)
{

}

/**
 * Save this  to an XML node
 * @param node The parent node we are going to be a child of
 * @return enemyNode
 */
wxXmlNode* Enemy::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"enemy");
    return itemNode;
}

/**
 * move left/right or animate
 * @param elapsed
 *
 */
void Enemy::Update(double elapsed)
{
    // Get bottom position for the first time we update
    if (!mHasBase)
    {
        mBaseY = GetY();
        mHasBase = true;
    }

    // Advance local time
    mTime += elapsed;

    // Compute the progress of the wave
    const double cycle = 2.0 * mHalfPeriod;
    double t = fmod(mTime, cycle);
    double phase = t / mHalfPeriod;
    double progress = (phase <= 1.0) ? phase : (2.0 - phase);

    // Move upward from base, then back down
    double y = mBaseY - progress * mAmplitude;
    SetLocation(GetX(), y);
}

/**
 * Accept collision visitor
 * @param visitor to accept
 */
void Enemy::Accept(CollisionVisitor* visitor)
{
    visitor->VisitEnemy(this);
}