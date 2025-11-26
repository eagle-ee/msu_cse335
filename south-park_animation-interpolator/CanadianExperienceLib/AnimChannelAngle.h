/**
 * @file AnimChannelAngle.h
 * @author b3big
 *
 *
 */
 
#ifndef ANIMCHANNELANGLE_H
#define ANIMCHANNELANGLE_H
#include "AnimChannel.h"


/**
 * Animation channel for angles.
 */
class AnimChannelAngle : public AnimChannel
{
private:
    ///Angle
    double mAngle;

protected:
    ///Class the represents a keyframe angle
    class KeyframeAngle : public Keyframe
    {
    private:
        /// Angle of the keyframe
        double mAngle;
        ///Channel this keyframe angle is associated with
        AnimChannelAngle *mChannel;
    public:
        ///Default constructor (Disabled)
        KeyframeAngle() = delete;
        /// Copy Constructor (Disabled)
        KeyframeAngle(const KeyframeAngle &) = delete;
        /// Assignment Operator (Disabled)
        void operator=(const KeyframeAngle &) = delete;
        /**
         * Get the angle
         * @return mAngle the Angle
         */
        double GetAngle() {return mAngle;};
        /**
         * Constructor
         * @param channel The channel we are for
         * @param angle The angle for the keyframe
         */
        KeyframeAngle(AnimChannelAngle *channel, double angle) :
                Keyframe(channel), mChannel(channel), mAngle(angle) {}

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mAngle = mAngle; }
    };

    void Tween(double t) override;
private:
    ///First angle keyframe
    KeyframeAngle *mKeyframe1 = nullptr;
    ///Second angle keyframe
    KeyframeAngle *mKeyframe2 = nullptr;
public:
    ///constructor
    AnimChannelAngle() {};
    /// Copy Constructor (Disabled)
    AnimChannelAngle(const AnimChannelAngle &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const AnimChannelAngle &) = delete;
    ///Destructor
    virtual ~AnimChannelAngle() {};

    /**
     * Get the angle
     * @return the angle
     */
    double GetAngle() {return mAngle;}

    void SetKeyframe(double angle);
};



#endif //ANIMCHANNELANGLE_H
