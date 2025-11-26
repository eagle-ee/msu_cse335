/**
 * @file PowerUp.cpp
 * @author Eduardo Jimenez & Saransh S
 */

#include "pch.h"
#include <string>
#include "PowerUp.h"

#include "CollisionVisitor.h"
#include "Game.h"

using namespace std;

/// PowerUp filenames
const wstring PowerUpImage = L"images/sparty.png";

/**
 * Constructor
 * @param game and image
 */
PowerUp::PowerUp(Game *game) : Item(game, PowerUpImage)
{

}

/**
 * Save this Power-Up to an XML node
 * @param node The parent node we are going to be a child of
 * @return PowerUpNode
 */
wxXmlNode* PowerUp::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"power-up");

    return itemNode;
}

/**
 * Accept visitor
 * @param visitor to accept
 */
void PowerUp::Accept(CollisionVisitor* visitor)
{
    visitor->VisitPowerUp(this);
}

/**
 * Update object
 * @param elapsed time
 */
void PowerUp::Update(double elapsed)
{
    if (!mActivated)
    {
        return;
    }

    // Add gravity
    mVy += mGravity * elapsed;
    SetLocation(GetX(), GetY() + mVy * elapsed);
}

/**
 * To remove from game's object list (iteration protection)
 * @param game owner
 * @return true if to remove
 */
bool PowerUp::ShouldRemove(const Game* game) const
{
    if (!mActivated) return false;
    // Remove once off the bottom of the screen
    return GetY() - GetHeight() / 2 > game->GetHeight();
}
