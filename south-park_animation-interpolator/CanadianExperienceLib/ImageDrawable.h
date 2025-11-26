/**
 * @file ImageDrawable.h
 * @author b3big
 *
 * Class that draws an image
 */
 
#ifndef IMAGEDRAWABLE_H
#define IMAGEDRAWABLE_H

#include "Drawable.h"

/**
 * An image object
 */
class ImageDrawable : public Drawable{
private:
    ///Center of image
    wxPoint mCenter = wxPoint(0, 0);
protected:
    /// The image we are drawing
    std::unique_ptr<wxImage> mImage;
    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;
public:
    ///Default constructor (Disabled)
    ImageDrawable() = delete;
    /// Copy Constructor (Disabled)
    ImageDrawable(const ImageDrawable &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const ImageDrawable &) = delete;
    ///Destructor
    virtual ~ImageDrawable() {};
    ImageDrawable(const std::wstring& name, const std::wstring& filename);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(wxPoint pos) override;
    /**
     * Set Center point
     * @param center Center point to set
     */
    void SetCenter(wxPoint center) { mCenter = center; };
    /**
     * Get center point
     * @return Center point
     */
    wxPoint GetCenter() { return mCenter; };
};



#endif //IMAGEDRAWABLE_H
