/**
 * @file GameView.cpp
 * @author Eduardo Jimenez and Michael Dreon
 */

#include "pch.h"
#include "GameView.h"
#include "ids.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

using namespace std;

/**
 * Destructor
 */
GameView::~GameView()
{
    //fixes X and File>Exit not working
    mTimer.Stop(); //running timer keeps loop active
    mStopWatch.Pause();
}

/**
 * Initialize the Game view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::LoadLevelZero, this, IDM_LEVELZERO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::LoadLevelOne, this, IDM_LEVELONE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::LoadLevelTwo, this, IDM_LEVELTWO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::LoadLevelThree, this, IDM_LEVELTHREE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnRestartLevel, this, IDM_RESTARTLEVEL);

    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);

    mScoreboard.Initialize(&mStopWatch);
    mGame.SetScoreboard(&mScoreboard);
    mGame.SetStopWatch(&mStopWatch);

    mTimer.SetOwner(this);
    mTimer.Start(16);  // ~60 FPS (16ms per frame)
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);
    mStopWatch.Start();
}


//
//
//View Handlers
//
//
/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{

    wxAutoBufferedPaintDC dc(this);

    // Maximum Amount of time allowed for elapsed
    const double MaxElapsed = 0.05;
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    //
    // Prevent Tunneling
    //
    while (elapsed > MaxElapsed)
    {
        mGame.Update(MaxElapsed);

        elapsed -= MaxElapsed;
    }
    // Consume remaining time
    if (elapsed > 0)
    {
        mGame.Update(elapsed);
    }


    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto size = GetClientSize();
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());
    mScoreboard.OnDraw(graphics,size.GetWidth(),size.GetHeight());

    if (!mGame.GetMessage().empty())
    {
        auto gc = wxGraphicsContext::Create(dc);
        if (gc)
        {
            gc->SetFont(wxFontInfo(40).Bold(), *wxRED);
            gc->DrawText(mGame.GetMessage(), 400, 300);
        }
    }
    // Draw the level message in the center
    auto gc2 = wxGraphicsContext::Create(dc);
    if (gc2 && !mGame.GetLevelMessage().empty())
    {
        wxString message = mGame.GetLevelMessage();

        // Create a big bold font
        wxFont font(48, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gc2->SetFont(font, *wxRED);  // Use red or any color

        // Measure the text size
        double w, h;
        gc2->GetTextExtent(message, &w, &h);

        // Get the center of the client area
        wxSize size = GetClientSize();
        double x = (size.GetWidth() - w) / 2;
        double y = (size.GetHeight() - h) / 2;

        // Draw the text at the center
        gc2->DrawText(message, x, y);
    }

}

/**
 * Timed view refresh
 * @param event Timer event object
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    auto football = mGame.GetFootball();
    if (!football)
    {
        Refresh();
        return;
    }

    double xV = 0;
    double yV = football->GetYVelocity();
    double const xSpeed=300;
    double yJumpVel = -750;
    if (mLeftDown)
        xV = -xSpeed;
    if (mRightDown)
        xV = xSpeed;
    if (!football->GetGrounded())
    {

    }
    else
    {
        yV=0;
        if (mSpaceDown)
        {
            yV = yJumpVel;
        }
    }
    football->SetXVelocity(xV);
    football->SetYVelocity(yV);
    Refresh();
}




//
//
// Menu Handlers
//
//
/**
 * File>Save As menu handler
 * @param event
 */
void GameView::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, L"Save Game file", L"", L"",
            L"Game Files (*.game)|*.game", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();
    mGame.Save(filename);
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void GameView::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, L"Load Game file", L"", L"",
            L"Game Files (*.game)|*.game", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();

    mGame.Load(filename);
    Refresh();
}



//
//
// Mouse Handlers
//
//
/**
 * Handle the left mouse button down event
 * @param event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{

}

/**
* Handle the left mouse button down event
* @param event
*/
void GameView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the left mouse button down event
* @param event
*/
void GameView::OnMouseMove(wxMouseEvent &event)
{

}

/**
 * Handle key down presses
 * @param event
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_LEFT:
        mLeftDown = true;
        break;
    case WXK_RIGHT:
        mRightDown = true;
        break;
    case WXK_SPACE:
        mSpaceDown = true;
        break;
    }
}

/**
 * Handle key up events
 * @param event
 */
void GameView::OnKeyUp(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_LEFT:
        mLeftDown = false;
        break;
    case WXK_RIGHT:
        mRightDown = false;
        break;
    case WXK_SPACE:
        mSpaceDown = false;
        break;
    }
}


/** Loads level of specified integer
* @param level number of level being loaded
*/
void GameView::LoadLevel(int level)
{
    mStopWatch.Pause();
    mScoreboard.Reset();
    
    /// Reset coin multiplier when new level loaded or restarted
    mGame.ResetCoinMultiplier();
    mGame.LoadLevel(level);
    mStopWatch.Start();
    Refresh();

}

/**
 * Handles the level 0 loading event
 * @param event
 */
void GameView::LoadLevelZero(wxCommandEvent& event)
{
    LoadLevel(0);
    Refresh();           // redraw the view
}

/**
 * Handles the level 1 loading event
 * @param event
 */
void GameView::LoadLevelOne(wxCommandEvent& event)
{
    LoadLevel(1);
    Refresh();
}

/**
 * Handles the level 2 loading event
 * @param event
 */
void GameView::LoadLevelTwo(wxCommandEvent& event)
{
    LoadLevel(2);
    Refresh();
}

/**
 * Handles the level 3 loading event
 * @param event
 */
void GameView::LoadLevelThree(wxCommandEvent& event)
{
    LoadLevel(3);
    Refresh();
}

/**
 * Shut down the timers
 */
void GameView::Shutdown()
{
    if (mTimer.IsRunning())
    {
        mTimer.Stop();
    }
}

/**
 * Handles restarting the current level
 * @param event Menu event
 */
void GameView::OnRestartLevel(wxCommandEvent& event)
{
    //mStopWatch.Pause();
    mGame.ReloadCurrentLevel();
    //mStopWatch.Start();
    //Refresh();
}
