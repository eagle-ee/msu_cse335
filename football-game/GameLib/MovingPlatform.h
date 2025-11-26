/**
 * @file MovingPlatform.h
 *
 * @author Michael Dreon
 */

#ifndef PROJECT1_MOVINGPLATFORM_H
#define PROJECT1_MOVINGPLATFORM_H

#include "Platform.h"


class MovingPlatform : public Platform
{
private:
    // The radius of the moving platform
    double mRadius = 0;
    // The x of the center of the moving platform
    double mCenterX = 0;
    // The y of the center of the moving platform
    double mCenterY = 0;
    // The speed in radians per second
    double mOmega = 1;
    // The current angle
    double mAngle = 0;
public:
    /// Default constructor (disabled)
    MovingPlatform() = delete;

    /// Copy constructor (disabled)
    MovingPlatform(const MovingPlatform &) = delete;

    /// Assignment operator
    void operator=(const MovingPlatform &) = delete;
    /**
     * Constructor
     * @param game Game this platform is in
     * @param filename Image file for this platform segment
     */
    MovingPlatform(Game* game, const std::wstring& filename);

    /**
     * Accept a collision visitor
     * @param visitor The collision visitor
     */
    void Accept(CollisionVisitor* visitor) override;

    /**
     * Updates the motion of the moving platform
     * @param cx Center x
     * @param cy Center y
     * @param radius Radius
     * @param omega Turn speed
     */
    void SetMotion(double cx, double cy, double radius, double omega);

    /**
     * Updates the position of the moving platform
     * @param elapsed Elapsed time
     */
    void Update(double elapsed) override;

};


#endif //PROJECT1_MOVINGPLATFORM_H