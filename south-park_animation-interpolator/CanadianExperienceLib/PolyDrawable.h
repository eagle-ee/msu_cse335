/**
 * @file PolyDrawable.h
 * @author Brennan Eagle
 *
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
 
#ifndef POLYDRAWABLE_H
#define POLYDRAWABLE_H
#include "Drawable.h"

/**
 * Polygon
 */
class PolyDrawable: public Drawable {
private:
    /// The polygon color
    wxColour mColor = *wxBLACK;
    /// The array of point objects
    std::vector<wxPoint> mPoints;
    ///Graphics path
    wxGraphicsPath mPath;
public:
    PolyDrawable(const std::wstring& name);
    ///Default constructor disabled
    PolyDrawable() = delete;
    /// Copy Constructor (Disabled)
    PolyDrawable(const PolyDrawable &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const PolyDrawable &) = delete;
    /**
     * Set the color
     * @param color to set
     */
    void SetColor(wxColour color) {mColor = color;}
    /**
     * Get the color
     * @return color
     */
    wxColour GetColor() {return mColor;}
    /**
     * Add a point
     * @param point to add
     */
    void AddPoint(wxPoint point) {mPoints.push_back(point);}
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(wxPoint pos) override;


};



#endif //POLYDRAWABLE_H
