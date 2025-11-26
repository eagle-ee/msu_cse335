/**
 * @file HeadTop.cpp
 * @author b3big
 */

#include "pch.h"
#include "HeadTop.h"

#include "Actor.h"
#include "Timeline.h"


/**
 * Draw the head
 * @param graphics Graphics object
 */
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    ImageDrawable::Draw(graphics);

    int d2 = mInterocularDistance / 2;
    int rightX = mEyesCenter.x - d2;
    int leftX = mEyesCenter.x + d2;
    int eyeY = mEyesCenter.y;

    DrawEyebrow(graphics, wxPoint(rightX - 10, eyeY - 16), wxPoint(rightX + 4, eyeY - 18));
    DrawEyebrow(graphics, wxPoint(leftX - 4, eyeY - 20), wxPoint(leftX + 9, eyeY - 18));

    DrawEye(graphics, wxPoint(leftX, eyeY));
    DrawEye(graphics, wxPoint(rightX, eyeY));
}

/**
 * Draw an eyebrow, automatically transforming the points
 *
 * Draw a line from (x1, y1) to (x2, y2) after transformation
 * to the local coordinate system.
 * @param graphics Graphics context to draw on
 * @param p1 First point
 * @param p2 Second point
 */
void HeadTop::DrawEyebrow(std::shared_ptr<wxGraphicsContext> graphics,
        wxPoint p1, wxPoint p2)
{
    auto eb1 = TransformPoint(p1);
    auto eb2 = TransformPoint(p2);

    wxPen eyebrowPen(*wxBLACK, 2);
    graphics->SetPen(eyebrowPen);
    graphics->StrokeLine(eb1.x, eb1.y, eb2.x, eb2.y);
}

/**
 * Draw an eye using an Ellipse
 * @param graphics The graphics context to draw on
 * @param p1 Where to draw before transformation
 *
 */
void HeadTop::DrawEye(std::shared_ptr<wxGraphicsContext> graphics, wxPoint p1)
{
    graphics->SetBrush(*wxBLACK_BRUSH);
    graphics->SetPen(*wxTRANSPARENT_PEN);

    auto e1 = TransformPoint(p1);

    float wid = 15.0f;
    float hit = 20.0f;

    graphics->PushState();
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    graphics->PopState();
}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* @param  p Point to transform
* @returns Transformed point
*/
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}

/**
 * Set a keyframe based on current position and rotation.
 * This extends the base Drawable functionality to also set position keyframes.
 */
void HeadTop::SetKeyframe()
{
    Drawable::SetKeyframe();
    mChannelPosition.SetKeyframe(GetPosition());
}

/**
 * Get a keyframe update from the animation system.
 * This extends the base Drawable functionality to also get position updates.
 */
void HeadTop::GetKeyframe()
{
    Drawable::GetKeyframe();

    if (mChannelPosition.IsValid())
    {
        SetPosition(mChannelPosition.GetPoint());
    }
}

/**
 * Add the channels for this drawable to a timeline.
 * This extends the base Drawable functionality to add both angle and position channels.
 * @param timeline The timeline class.
 */
void HeadTop::SetTimeline(Timeline *timeline)
{
    Drawable::SetTimeline(timeline);

    std::wstring baseName = GetAngleChannel()->GetName();
    mChannelPosition.SetName(baseName + L"-position");

    timeline->AddChannel(&mChannelPosition);
}

/**
 * Override SetActor to set up the position channel name
 * @param actor Actor using this drawable
 */
void HeadTop::SetActor(Actor *actor)
{
    Drawable::SetActor(actor);
    mChannelPosition.SetName(actor->GetName() + L":" + GetName() + L":position");
}

/**
 * Delete a keyframe at the current frame.
 * This extends the base Drawable functionality to also delete position keyframes.
 */
void HeadTop::DeleteKeyframe()
{
    Drawable::DeleteKeyframe();
    mChannelPosition.DeleteKeyframe();
}