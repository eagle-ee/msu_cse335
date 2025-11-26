/**
 * @file ItemCoin100.cpp
 * @author Brennan Eagle
 */
 
#include "pch.h"
#include <string>

#include "CollisionVisitor.h"
#include "Game.h"
using namespace std;
#include "ItemCoin100.h"

/// Coin filename
const wstring coin100Image = L"images/coin100.png"; ///<100

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
ItemCoin100::ItemCoin100(Game *game) : Item(game, coin100Image)
{

}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* ItemCoin100::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"coin100");

    return itemNode;
}

/**
 * Accept visitor
 * @param visitor pointer
 */
void ItemCoin100::Accept(CollisionVisitor* visitor)
{
    visitor->VisitCoin100(this);
}

/**
 * Update coin position
 * In Level 2, coins move from right to left at a constant slow speed
 * @param elapsed Time elapsed since last update
 */
void ItemCoin100::Update(double elapsed)
{
    if (mGame && mGame->GetLevel() == 2)
    {
        const double moveSpeed = -10.0; // Negative for left movement
        double newX = GetX() + moveSpeed * elapsed;
        SetLocation(newX, GetY());
    }
}
