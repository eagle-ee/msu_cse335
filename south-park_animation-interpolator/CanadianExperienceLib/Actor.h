/**
 * @file Actor.h
 * @author Brennan Eagle
 *
 *
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
 
#ifndef ACTOR_H
#define ACTOR_H

#include "AnimChannelPoint.h"
#include "Drawable.h"

class Drawable;
class Picture;

/**
 * Class for actors in our drawings.
 */
class Actor {
private:
    ///name
    std::wstring mName;
    ///enabled
    bool mEnabled = true;
    ///xy loc
    wxPoint mPosition = wxPoint(0, 0);
    ///clickable
    bool mClickable = true;
    /// The root drawable
    std::shared_ptr<Drawable> mRoot;
    /// The drawables in drawing order
    std::vector<std::shared_ptr<Drawable>> mDrawablesInOrder;
    ///the picture
    Picture* mPicture = nullptr;
    ///channel for position of actor
    AnimChannelPoint mChannelPosition;

public:
    virtual ~Actor() {}


    Actor(const std::wstring &name);

    ///Default constructor disabled
    Actor() = delete;
    /// Copy Constructor (Disabled)
    Actor(const Actor &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Actor &) = delete;

    void SetRoot(std::shared_ptr<Drawable>);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    std::shared_ptr<Drawable> HitTest(wxPoint pos);
    void AddDrawable(std::shared_ptr<Drawable> drawable);

    /**
     * Get name
     * @return name
     */
    std::wstring GetName() const {return mName;};
    /**
     * Get position
     * @return position
     */
    wxPoint GetPosition() const {return mPosition;};
    /**
     * Set position
     * @param pos to set
     */
    void SetPosition(wxPoint pos) {mPosition = pos;};

    /**
     * Get enabled
     * @return enabled?
     */
    bool IsEnabled() const {return mEnabled;};
    /**
     * Set enabled
     * @param enable set t/f
     */
    void SetEnabled(bool enable) {mEnabled = enable;};
    /**
     * Get clickable
     * @return clickable?
     */
    bool IsClickable() const {return mClickable;};
    /**
     * Set clickable
     * @param clickable set t/f
     */
    void SetClickable(bool clickable) {mClickable = clickable;};
    /**
     * Get the picture
     * @return the picture
     */
    Picture* GetPicture() const {return mPicture;};
    /**
     * Set the picture
     * @param picture to set
     */
    void SetPicture(Picture* picture);
    void SetKeyframe();
    void GetKeyframe();
    /**
     * The position animation channel
     * @return Pointer to animation channel
     */
    AnimChannelPoint *GetPositionChannel() { return &mChannelPosition; }
    /**
     * Delete a keyframe at the current frame
     */
    void DeleteKeyframe() { mChannelPosition.DeleteKeyframe(); }
};



#endif //ACTOR_H
