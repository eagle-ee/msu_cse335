/**
 * @file Item.h
 * @author Eduardo Jimenez and Michael Dreon
 *
 *
 */

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H

#include <wx/xml/xml.h>

class wxXmlNode;
class CollisionVisitor; ///<forward ref
class Game; ///<forward ref

class Item
{
private:
    // Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item
    // Previous item location
    double mPrevX = 0;
    double mPrevY = 0;
    // Item width and height
    double mWid = 0;
    double mHit = 0;

    /// The bitmap we can display for this item
    std::shared_ptr<wxBitmap> mItemBitmap;

protected:
    /// Pointer to the game this item belongs to
    Game* mGame = nullptr;
    /**
     * Set the bitmap for this item
     * @param bitmap shared pointer to bitmap
     */
    void SetBitmap(std::shared_ptr<wxBitmap> bitmap);

public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    ~Item();
    Item(Game* game, const std::wstring& filename);
    /**
    * The X location of the item
    * @returns X location in pixels
    */
    double GetX() const { return mX; }
    /**
     * The Y location of the item
     * @returns Y location in pixels
     */
    double GetY() const { return mY; }
    /**
    * The previous X location of the item
    * @returns previous X location in pixels
    */
    double GetPrevX() const { return mPrevX; }
    /**
     * The previous Y location of the item
     * @returns previous Y location in pixels
     */
    double GetPrevY() const { return mPrevY; }
    /**
     * Update previous locations
     */
    void UpdatePrev() { mPrevX = mX; mPrevY = mY; }
    /**
     * @returns the Width of the item
     */
    double GetWidth() const { return mWid; }
    /**
     * @returns the Width of the item
     */
    double GetHeight() const { return mHit; }
    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    virtual bool HitTest(int x, int y);
    virtual void Draw(std::shared_ptr<wxGraphicsContext> gc, double offset);
    virtual wxXmlNode* XmlSave(wxXmlNode* node);
    virtual void XmlLoad(wxXmlNode* node);
    std::shared_ptr<wxBitmap> GetBitmap();

    // Deals with how an object collides with another object
    virtual void OnCollide(Item* item) { }

    /// Returns if the object is a collidable, default is true
    virtual bool IsCollidable() { return true; }

    /**
     * Handle updates in time
     * @param elapsed Time elapsed since the last class
     */
    virtual void Update(double elapsed) {}

    /**
     * Accept a collision visitor
     * @param visitor The collision visitor
     */
    virtual void Accept(CollisionVisitor* visitor) { }

    /** 
     * Use if the item should be removed after update
     * @param game Pointer to the game for context
     */
    virtual bool ShouldRemove(const Game* game) const { return false; }
};


#endif //PROJECT1_ITEM_H