/**
 * @file GoalPost.cpp
 * @author Eduardo Jimenez
 */

#include "pch.h"
#include <string>
#include "GoalPost.h"

#include "CollisionVisitor.h"
using namespace std;

/// GoalPost filenames
const wstring GoalPostImage = L"images/goalpost.png"; ///

/**
 * Constructor
 * @param game and GoalPost image
 */
GoalPost::GoalPost(Game *game) : Item(game, GoalPostImage)
{
    wxBitmap test(L"images/sparty.png", wxBITMAP_TYPE_ANY);
    if (!test.IsOk())
    {
        wxLogError(L"Could not load PowerUp image!");
    }
}

/**
 * Save this  to an XML node
 * @param node The parent node we are going to be a child of
 * @return GoalPost Node
 */
wxXmlNode* GoalPost::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"goalpost");

    return itemNode;
}

void GoalPost::Accept(CollisionVisitor* visitor)
{
    visitor->VisitGoalPost(this);
}
