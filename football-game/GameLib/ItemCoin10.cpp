/**
 * @file ItemCoin10.cpp
 * @author Brennan Eagle
 */

#include "pch.h"
#include "ItemCoin10.h"
#include "CollisionVisitor.h"
#include "Game.h"
#include <string>

using namespace std;


/// Coin filenames
const wstring coin10Image = L"images/coin10.png"; ///<10

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
ItemCoin10::ItemCoin10(Game *game) : Item(game, coin10Image)
{

}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* ItemCoin10::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"coin10");

    return itemNode;
}

/**
 * Accept visitor
 * @param visitor visitor
 */
void ItemCoin10::Accept(CollisionVisitor* visitor)
{
    visitor->VisitCoin10(this);
}

/**
 * Update coin position
 * In Level 2, coins move from right to left at a constant slow speed
 * @param elapsed Time elapsed since last update
 */
void ItemCoin10::Update(double elapsed)
{
    if (mGame && mGame->GetLevel() == 2)
    {
        const double moveSpeed = -10.0; // Negative for left movement
        double newX = GetX() + moveSpeed * elapsed;
        SetLocation(newX, GetY());
    }
}