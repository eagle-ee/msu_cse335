/**
 * @file AnimChannelPoint.h
 * @author b3big
 *
 *
 */
 
#ifndef ANIMCHANNELPOINT_H
#define ANIMCHANNELPOINT_H

#include "AnimChannel.h"

/**
 * An animation channel specific to points (translational movement)
 */
class AnimChannelPoint : public AnimChannel
{
private:
    /// The current point value
    wxPoint mPoint = wxPoint(0, 0);

protected:
    /// Class that represents a keyframe for a point
    class KeyframePoint : public Keyframe
    {
    private:
        /// The point value for this keyframe
        wxPoint mPoint;

        /// The channel this keyframe is associated with
        AnimChannelPoint *mChannel;

    public:
        /// Default constructor (Disabled)
        KeyframePoint() = delete;

        /// Copy Constructor (Disabled)
        KeyframePoint(const KeyframePoint &) = delete;

        /// Assignment Operator (Disabled)
        void operator=(const KeyframePoint &) = delete;

        /**
         * Constructor
         * @param channel The channel we are for
         * @param point The point value for the keyframe
         */
        KeyframePoint(AnimChannelPoint *channel, wxPoint point) :
                Keyframe(channel), mChannel(channel), mPoint(point) {}

        /**
         * Get the point value
         * @return The point value
         */
        wxPoint GetPoint() { return mPoint; }

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyframe 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the point
        void UseOnly() override { mChannel->mPoint = mPoint; }
    };

    void Tween(double t) override;

private:
    /// First point keyframe
    KeyframePoint *mKeyframe1 = nullptr;

    /// Second point keyframe
    KeyframePoint *mKeyframe2 = nullptr;

public:
    /// Constructor
    AnimChannelPoint() {}

    /// Copy Constructor (Disabled)
    AnimChannelPoint(const AnimChannelPoint &) = delete;

    /// Assignment Operator (Disabled)
    void operator=(const AnimChannelPoint &) = delete;

    /// Destructor
    virtual ~AnimChannelPoint() {}

    /**
     * Get the point value
     * @return The current point value
     */
    wxPoint GetPoint() { return mPoint; }

    void SetKeyframe(wxPoint point);
};



#endif //ANIMCHANNELPOINT_H
