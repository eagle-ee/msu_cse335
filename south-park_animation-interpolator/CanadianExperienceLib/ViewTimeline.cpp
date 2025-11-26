/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>

#include "ViewTimeline.h"

#include <sstream>

#include "Actor.h"
#include "Picture.h"
#include "PictureObserver.h"
#include "TimelingDlg.h"

/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";


/**
 * Constructor
 * @param parent The main wxFrame object
 * @param imagesDir image directory
 */
ViewTimeline::ViewTimeline(wxFrame* parent, std::wstring& imagesDir) :
    wxScrolledCanvas(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(100, Height))
{
    mImagesDir = imagesDir;
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
                 &ViewTimeline::OnEditTimelineProperties, this,
                 XRCID("EditTimelineProperties"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnSetKeyframe,
        this, XRCID("SetKeyframe"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnDeleteKeyframe,
        this, XRCID("DeleteKeyframe"));
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    //+20 offset to access pointer on last tick
    SetVirtualSize(TickSpacing*GetPicture()->GetTimeline()->GetNumFrames() + 20, Height);
    SetScrollRate(1, 0);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    wxPen pen(wxColour(0, 0, 0), 1);
    graphics->SetPen(pen);

    wxFont font(wxSize(0, 16),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);

    auto frameRate = GetPicture()->GetTimeline()->GetFrameRate();
    auto numFrames = GetPicture()->GetTimeline()->GetNumFrames();

    for(int tick = 0; tick < numFrames; ++tick)
    {
        int x = BorderLeft + tick*TickSpacing;
        bool onSecond = (tick % frameRate == 0);
        int tickLen = onSecond ? TickLong : TickShort;

        graphics->StrokeLine(x, TickTop, x, TickTop + tickLen);

        if (onSecond)
        {
            std::wstringstream str;
            str << tick / frameRate;
            std::wstring wstr = str.str();

            double w,h;
            graphics->GetTextExtent(wstr, &w, &h);

            graphics->DrawText(wstr, x - w/2, TickTop + TickLong + 2);

        }
    }

    if (!mPointerImage)
    {
        mPointerImage = std::make_unique<wxImage>(mImagesDir + PointerImageFile, wxBITMAP_TYPE_ANY);
    }
    mPointerBitmap = wxBitmap(*mPointerImage);

    int currentFrame = GetPicture()->GetTimeline()->GetCurrentFrame();
    int pointerX = BorderLeft + currentFrame * TickSpacing;


    graphics->DrawBitmap(mPointerBitmap,
        pointerX - mPointerImage->GetWidth() / 2,
        TickTop,
        mPointerImage->GetWidth(),
        mPointerImage->GetHeight());
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
    Update();
}

//
//Dialog Handler
//
/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
    TimelineDlg dlg(this->GetParent(), GetPicture()->GetTimeline());
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Tmeline settings
        GetPicture()->UpdateObservers();
    }
}


//
//
///Mouse Handlers
//
//

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();
    int pointerX = (int)(timeline->GetCurrentTime() *
            timeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - mPointerImage->GetWidth() / 2 &&
            x <= pointerX + mPointerImage->GetWidth() / 2;

    if(mMovingPointer)
    {
        int xx = 0;
    }
}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());
    if (mMovingPointer && event.Dragging())
    {
        int x = click.x;

        Timeline* timeline = GetPicture()->GetTimeline();
        int frame = (x - BorderLeft) / TickSpacing;

        if (frame < 0)
        {
            frame = 0;
        }
        else if (frame >= timeline->GetNumFrames())
        {
            frame = timeline->GetNumFrames() - 1;
        }

        GetPicture()->SetAnimationTime(frame / (double)timeline->GetFrameRate());
    }
}

/**
 * Handle an Edit>Set Keyframe menu option
 * @param event The menu event
 */
void ViewTimeline::OnSetKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

/**
 * Handle an Edit>Delete Keyframe menu option
 * @param event The menu event
 */
void ViewTimeline::OnDeleteKeyframe(wxCommandEvent& event)
{

}

