/**
 * @file Football.h
 *
 * @author Michael Dreon
 *
 * The football in our game
 */

#ifndef PROJECT1_FOOTBALL_H
#define PROJECT1_FOOTBALL_H

#include "Item.h"

/**
 * The football in our game
 */
class Football : public Item
{
private:
    /// X Velocity
    double mXVelocity = 0;
    /// Y Velocity
    double mYVelocity = 0;
    /// Y Acceleration
    double mGravity = 1000;
    /// The terminal velocity
    double mTerminalVelocity = 500;
    /// Tells the football whether it is on the ground or not
    bool mGrounded = false;
    /// What item we are standing on
    Item* mStandingOn = nullptr;

    /// Each of the directional bitmaps
    /// Left
    std::shared_ptr<wxBitmap> mItemBitmapLeft;
    std::shared_ptr<wxBitmap> mItemBitmapMid;
    std::shared_ptr<wxBitmap> mItemBitmapRight;
public:
    /// Default constructor (disabled)
    Football() = delete;

    /// Copy constructor (disabled)
    Football(const Football &) = delete;

    /// Assignment operator
    void operator=(const Football &) = delete;

    /// Constructor
    Football(Game* game);

    /// Set X velocity
    void SetXVelocity(double x);
    /// Set Y velocity
    void SetYVelocity(double y);
    /// Set grounded status
    void SetGrounded(bool grnd) { mGrounded = grnd; }
    /// Set the object standing on
    void SetStandingOn(Item* item) { mStandingOn = item; }
    /// Apply the motion of the platform
    void ApplyPlatformMotion(double dx, double dy){ SetLocation(GetX()+dx, GetY()+dy); }

    /**
     * Returns the y velocity
     * @return Y acceleration
     */
    double GetYVelocity() const { return mYVelocity; }
    /**
     * Returns if the football is grounded
     * @return State of standing on ground
     */
    bool GetGrounded() const { return mGrounded; }
    /**
     * Returns what football is standing on
     * @return Item football is standing on
     */
    Item* GetStandingOn() const { return mStandingOn; }

    /// Checks if the football collides with an item
    bool CollisionTest(Item* item);
    /// Returns that a football is not collidable
    bool IsCollidable() override { return false; };
    /// Resolves collion with an object
    void CollisionResolve(Item* item);


    /// Updates position
    void Update(double elapsed) override;
};


#endif //PROJECT1_FOOTBALL_H