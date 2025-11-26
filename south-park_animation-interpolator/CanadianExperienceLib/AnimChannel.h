/**
 * @file AnimChannel.h
 * @author b3big
 *
 *
 */
 
#ifndef ANIMCHANNEL_H
#define ANIMCHANNEL_H

class Timeline;


/** Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class AnimChannel {
private:
    ///Name
    std::wstring mName;

    ///Key frames
    int mKeyframe1 = -1;
    ///^
    int mKeyframe2 = -1;

    ///The timeline object
    Timeline *mTimeline = nullptr;


protected:
    /// Default constructor
    AnimChannel() { }

    ///Class the represets a keyframe
    class Keyframe
    {
    private:
        ///The Frame
        int mFrame;
        ///Channel this keyframe is associated with
        AnimChannel *mChannel;
    protected:
        /**
         * Constructor
         * @param channel Channel we are associated with
         */
        Keyframe(AnimChannel *channel) : mChannel(channel) {}
    public:
        ///Default constructor (Disabled)
        Keyframe() = delete;
        /// Copy Constructor (Disabled)
        Keyframe(const Keyframe &) = delete;
        /// Assignment Operator (Disabled)
        void operator=(const Keyframe &) = delete;
        /**
         * Get the frame
         * @return mFrame The frame
         */
        int GetFrame() { return mFrame; };
        /**
         * Set the frame
         * @param frame Frame to set
         */
        void SetFrame(int frame) {mFrame = frame; };
        ///UseAs virtual
        virtual void UseAs1() = 0;
        ///Use as virtual
        virtual void UseAs2() = 0;
        ///Use only virtual
        virtual void UseOnly() = 0;
    };
    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    /**
     * Tween as virtual
     * @param t Where to interpolate
     */
    virtual void Tween(double t) = 0;
    void DeleteKeyframeAtFrame(int frame);

private:
    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;

public:

    /// Copy constructor (disabled)
    AnimChannel(const AnimChannel &) = delete;
    /// Assignment operator
    void operator=(const AnimChannel &) = delete;
    ///Destructor
    virtual ~AnimChannel() {};

    /**
    * Get the name
    * @return mName the name
    */
    std::wstring GetName() {return mName;};
    /**
     * Set the name
     * @param name Name to set
     */
    void SetName(const std::wstring &name) {mName = name;}
    /**
     * Set the timeline
     * @param timeline Timeline to set
     */
    void SetTimeline(Timeline *timeline) {mTimeline = timeline;}
    /**
     * Get the timeline
     * @return mTimeline The timeline
     */
    Timeline *GetTimeline() {return mTimeline;}

    bool IsValid();
    void SetFrame(int currFrame);
    /**
     * Delete a keyframe
     */
    void DeleteKeyframe();
};



#endif //ANIMCHANNEL_H
