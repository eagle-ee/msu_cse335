/**
 * @file Item.cpp
 * @author Eduardo Jimenez
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

using namespace std;
/**
 * Constructor
 * @param
 */
Item::Item(Game* game, const std::wstring &filename)
{
    mGame = game;
    mItemBitmap = game->GetCachedImage(filename);
    mWid = mItemBitmap->GetWidth();
    mHit = mItemBitmap->GetHeight();
}

void Item::SetBitmap(std::shared_ptr<wxBitmap> bitmap)
{
    mItemBitmap = bitmap;
    if (mItemBitmap)
    {
        mWid = mItemBitmap->GetWidth();
        mHit = mItemBitmap->GetHeight();
    }
}

/**
 * Destructor
 */
Item::~Item()
{

}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(int x, int y)
{
    if (!mItemBitmap) return false;
    
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();

    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        return false;
    }

    return true;
}

/**
 * Draw this item
 * @param gc graphics context to draw on
 */
void Item::Draw(shared_ptr<wxGraphicsContext> gc, double offset)
{
    if (!mItemBitmap) return;
    
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();

    const double x = GetX() - wid / 2.0;
    const double y = GetY() - hit / 2.0;

    gc->DrawBitmap(*mItemBitmap, x-offset, y, wid, hit);
}


//
//
//Save/Load
//
//
/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode *Item::XmlSave(wxXmlNode *node)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");
    node->AddChild(itemNode);

    itemNode->AddAttribute(L"x", wxString::FromDouble(mX));
    itemNode->AddAttribute(L"y", wxString::FromDouble(mY));

    return itemNode;
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
}

/**
 * Gets the bitmap of an item
 * @return the bitmap of an item
 */
std::shared_ptr<wxBitmap> Item::GetBitmap()
{
    return mItemBitmap;
}
