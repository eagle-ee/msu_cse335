/**
 * @file PictureObserver.h
 * @author Brennan Eagle
 *
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
 
#ifndef PICTUREOBSERVER_H
#define PICTUREOBSERVER_H


class Picture;

/**
 * Observer to update
 */
class PictureObserver {
private:
    /// Picture we are observing
    std::shared_ptr<Picture> mPicture;

protected:
    /// Constructor
    PictureObserver() {}

public:
    virtual ~PictureObserver();
    void SetPicture(std::shared_ptr<Picture> picture);
    /// Copy Constructor (Disabled)
    PictureObserver(const PictureObserver &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const PictureObserver &) = delete;
    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;
    /**
     * Get the picture
     * @return picture
     */
    const std::shared_ptr<Picture>& GetPicture() const {return mPicture;};
};



#endif //PICTUREOBSERVER_H
