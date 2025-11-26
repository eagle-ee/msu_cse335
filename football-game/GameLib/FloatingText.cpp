/**
 * @file FloatingText.cpp
 * @author Brennan Eagle
 */
 
#include "FloatingText.h"

/**
 * Constructor
 * @param text to display
 * @param x location
 * @param y location
 * @param points number of points
 */
FloatingText::FloatingText(const wxString& text, double x, double y, int points)
    : mText(text), mX(x), mY(y), mVelocityY(-50.0),
      mLifetime(0.0), mMaxLifetime(1.5), mPoints(points)
{

}

/**
 * Update this object
 * @param elapsed time
 */
void FloatingText::Update(double elapsed)
{
    mY += mVelocityY * elapsed;
    mLifetime += elapsed;
}

/**
 * Draw this object
 * @param gc graphics context
 * @param xOffset offset if coins moving
 */
void FloatingText::Draw(std::shared_ptr<wxGraphicsContext> gc, double xOffset)
{

    double alpha = 1.0 - (mLifetime / mMaxLifetime);
    if (alpha < 0) alpha = 0;
    if (alpha > 1) alpha = 1;

    wxFont font(wxSize(0, 24), wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxColour color;
    if (mPoints >= 100)
        color = wxColour(255, 215, 0, static_cast<int>(alpha * 255)); // Gold
    else
        color = wxColour(255, 255, 0, static_cast<int>(alpha * 255)); // Yellow

    gc->SetFont(font, color);
    gc->DrawText(mText, mX - xOffset, mY);
}
