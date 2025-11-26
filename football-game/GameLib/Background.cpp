/**
 * @file Background.cpp
 *
 * @author Michael Dreon
 */

#include "pch.h"
#include "Background.h"

/**
 * Constructor
 * @param game the game
 * @param BackgroundImage the background image
 */
Background::Background(Game *game, const std::wstring& BackgroundImage) : Item(game, BackgroundImage)
{

}

/**
 * Save this  to an XML node
 * @param node The parent node we are going to be a child of
 * @return GoalPost Node
 */
wxXmlNode* Background::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"background");

    return itemNode;
}