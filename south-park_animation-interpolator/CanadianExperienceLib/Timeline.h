/**
 * @file Timeline.h
 * @author b3big
 *
 *
 */
 
#ifndef TIMELINE_H
#define TIMELINE_H


class AnimChannel;
/**
 * This class implements a timeline that manages the animation
 *
 * A timeline consists of animation channels for different parts of our
 * actors, each with keyframes that set the position, orientation, etc
 * at that point in time.
 */
class Timeline {
private:
    ///number of frames
    int mNumFrames = 300;
    ///frame per second
    int mFrameRate = 30;
    ///time
    double mCurrentTime = 0;
    /// List of all animation channels
    std::vector<AnimChannel *> mChannels;

public:
    Timeline();

    /// Copy Constructor (Disabled)
    Timeline(const Timeline &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Timeline &) = delete;

    void AddChannel(AnimChannel* channel);

    //
    //
    //Getters/Setters
    //
    //
    /**
     * Get the number of frames in the animation
     * @return Number of frames in the animation
     */
    int GetNumFrames() const {return mNumFrames;}
    /**
     * Set the number of frames in the animation
     * @param numFrames Number of frames in the animation
     */
    void SetNumFrames(int numFrames) {mNumFrames = numFrames;}
    /**
     * Get the frame rate
     * @return Animation frame rate in frames per second
     */
    int GetFrameRate() const {return mFrameRate;}
    /**
     * Set the frame rate
     * @param frameRate Animation frame rate in frames per second
     */
    void SetFrameRate(int frameRate) {mFrameRate = frameRate;}
    /**
     * Get the current time
     * @return Current animation time in seconds
     */
    double GetCurrentTime() const {return mCurrentTime;}

    void SetCurrentTime(double currentTime);

    /**
     * Get the animation duration
     * @return Animation duration in seconds
     */
    double GetDuration() const { return static_cast<double>(mNumFrames) / mFrameRate; }
    /** Get the current frame.
     *
     * This is the frame associated with the current time
     * @return Current frame
     */
    int GetCurrentFrame() const { return static_cast<int>(mCurrentTime * mFrameRate); }
};



#endif //TIMELINE_H
