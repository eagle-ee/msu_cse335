/**
 * @file HeadTop.h
 * @author b3big
 *
 *
 */
 
#ifndef HEADTOP_H
#define HEADTOP_H

#include "AnimChannelPoint.h"
#include "ImageDrawable.h"


/**
 * The separate Head of an actor
 */
class HeadTop : public ImageDrawable{
private:
    ///Location of center of eyes
    wxPoint mEyesCenter = wxPoint(55, 79);
    ///Distance between eyes
    int mInterocularDistance = 27;
    ///channel for position of teh head
    AnimChannelPoint mChannelPosition;

public:
    ///Default constructor (Disabled)
    HeadTop() = delete;
    /// Copy Constructor (Disabled)
    HeadTop(const HeadTop &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const HeadTop &) = delete;
    ///Destructor
    virtual ~HeadTop() {};
    /**
     * Head Top Constructor
     * @param name Name of Head
     * @param filename Image source
     */
    HeadTop(const std::wstring& name, const std::wstring& filename) : ImageDrawable(name, filename){};
    /**
     * Is image movable?
     * @return True, head moves independently
     */
    bool IsMovable() override {return true;};

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void DrawEyebrow(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1, wxPoint p2);
    void DrawEye(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1);
    wxPoint TransformPoint(wxPoint p);

    /**
     * Set point as center of eyes
     * @param point Point to set
     */
    void SetEyesCenter(const wxPoint& point) { mEyesCenter = point; };
    /**
     * Set interocular distance
     * @param value Value to set
     */
    void SetInterocularDistance(const int& value) { mInterocularDistance = value; };
    /**
     * The position animation channel
     * @return Pointer to animation channel
     */
    AnimChannelPoint *GetPositionChannel() { return &mChannelPosition; }

    void SetKeyframe() override;
    void GetKeyframe() override;
    void SetTimeline(Timeline* timeline) override;
    void SetActor(Actor* actor);
    void DeleteKeyframe();
};



#endif //HEADTOP_H
