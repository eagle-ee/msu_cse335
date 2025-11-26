/**
 * @file AnimChannelPoint.cpp
 * @author b3big
 */
 
#include "pch.h"
#include "AnimChannelPoint.h"

#include "Timeline.h"

/**
 * Compute a point that is an interpolation between two keyframes
 *
 * This function is called after UseAs1 and UseAs2,
 * so we have pointers to valid keyframes of the
 * type KeyframePoint. This function computes the tweening.
 *
 * @param t A t value. t=0 means keyframe1, t=1 means keyframe2.
 * Other values interpolate between.
 */
void AnimChannelPoint::Tween(double t)
{
    wxPoint a = mKeyframe1->GetPoint();
    wxPoint b = mKeyframe2->GetPoint();

    mPoint = wxPoint(int(a.x + t * (b.x - a.x)),
                     int(a.y + t * (b.y - a.y)));
}

/**
 * Set a keyframe
 *
 * This function allocates a new keyframe and sends it to
 * AnimChannel, which will insert it into the collection of keyframes.
 * @param point Point value for the keyframe.
 */
void AnimChannelPoint::SetKeyframe(wxPoint point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the point
    auto keyframe = std::make_shared<KeyframePoint>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}
