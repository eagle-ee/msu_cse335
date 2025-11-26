/**
 * @file FloatingText.h
 * @author Brennan Eagle
 *
 *
 */
 
#ifndef FLOATINGTEXT_H
#define FLOATINGTEXT_H



class FloatingText {
private:
    ///text to write
    wxString mText;
    ///x, y locations
    double mX, mY;
    ///velocity upwards
    double mVelocityY;
    ///current fade time
    double mLifetime;
    ///max fade time
    double mMaxLifetime;
    ///points
    int mPoints;
public:
    FloatingText();
    FloatingText(const wxString& text, double x, double y, int points);
    void Update(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> gc, double xOffset);
    void SetVelocityY(double vy) { mVelocityY = vy; }
    /**
     * Check age of floating text
     * @return if text is old enough to destroy
     */
    bool IsExpired() const { return mLifetime >= mMaxLifetime; }
};



#endif //FLOATINGTEXT_H
