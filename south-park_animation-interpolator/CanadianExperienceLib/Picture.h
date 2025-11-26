/**
 * @file Picture.h
 * @author Brennan Eagle
 *
 * The picture we are drawing.
 *
 * There will be one picture object that contains all of
 * our actors, which then contains the drawables.
 */
 
#ifndef PICTURE_H
#define PICTURE_H

#include "Timeline.h"

class Actor; ///<forward ref
class PictureObserver; ///<forward ref
class Timeline; ///<forward ref

/**
 * Picture we are drawing
 */
class Picture {
private:
    /// The picture size
    wxSize mSize = wxSize(1500, 800);
    /// The observers of this picture
    std::vector<PictureObserver *> mObservers;
    /// The drawables in drawing order
    std::vector<std::shared_ptr<Actor>> mActors;
    /// The animation timeline
    Timeline mTimeline;

public:
    /**
     * Constructor
     */
    Picture() {};
    /// Copy Constructor (Disabled)
    Picture(const Picture &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Picture &) = delete;
    /**
     * Get the picture size
     * @return Picture size in pixels
     */
    wxSize GetSize() {return mSize;}

    /**
     * Set the picture size
     * @param size Picture size in pixels
     */
    void SetSize(wxSize size) {mSize = size;}

    void AddObserver(PictureObserver *observer);
    void RemoveObserver(PictureObserver *observer);
    void UpdateObservers();
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void AddActor(std::shared_ptr<Actor> actor);
    void SetAnimationTime(double time);

    /**
     * Iterate over objects in Picture
     */
    class Iter
    {
    public:
        /**
         * Constructor
         * @param picture Picture we are iterating over
         * @param pos Position in collection
         */
        Iter(Picture *picture, int pos) : mPicture(picture), mPos(pos) {};
        /**
         * Compare 2 iters
         * @param other Other iterator to compare with
         * @return true if pos ==
         */
        bool operator!=(const Iter &other) const
        {
            return mPos != other.mPos;
        };

        /**
         * Deference operator for value at current position
         * @return pointer to Actor at mPos
         */
        std::shared_ptr<Actor> operator*() const
        {
            return mPicture->mActors[mPos];
        }

        /**
         * Increment iterator
         * @return Reference to this iterator
         */
        const Iter& operator++()
        {
            ++mPos;
            return *this;
        }
    private:
        ///Picture we are iterating over
        Picture *mPicture;
        ///Position in collection
        int mPos;
    };

    /**
     * Get iterator for start of collection
     * @return Iter object at position 0
     */
    Iter begin(){ return Iter(this, 0);};
    /**
     * Get iterator for end of collection
     * @return Iter object at postion past end
     */
    Iter end(){ return Iter(this, mActors.size());};

    /**
     * Get a pointer to the Timeline object
     * @return Pointer to the Timeline object
     */
    Timeline *GetTimeline() {return &mTimeline;}
};



#endif //PICTURE_H
