/**
 * @file Scoreboard.cpp
 * @author Brennan Eagle
 */
 
#include "Scoreboard.h"



/**
 * Constructor
 */
Scoreboard::Scoreboard()
{

}

/**
 * Initialize scoreboard
 * @param game Pointer
 * @param stopWatch Pointer
 */
void Scoreboard::Initialize(wxStopWatch* stopWatch)
{
    mStopWatch = stopWatch;
    mLastScore = mStopWatch->Time();
}

/**
 * Draw scoreboard
 * @param gc Graphics context
 * @param width of window
 * @param height of window
 */
void Scoreboard::OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height)
{
    if (!mStopWatch) return;

    gc->PushState();
    gc->SetTransform(gc->CreateMatrix());

    wxFont font(wxSize(0, 20), wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    gc->SetFont(font, *wxWHITE);

    gc->SetBrush(wxBrush(wxColour(0, 0, 0, 128)));
    gc->SetPen(*wxTRANSPARENT_PEN);

    //timer
    long elapsedMs = mStopWatch->Time();
    int minutes = elapsedMs / 60000;
    int seconds = (elapsedMs / 1000) % 60;
    wxString timeStr = wxString::Format("Time: %02d:%02d", minutes, seconds);
    double timeWidth, timeHeight;
    gc->GetTextExtent(timeStr, &timeWidth, &timeHeight);

    gc->DrawRectangle(5, 5, timeWidth + 10, timeHeight + 10);
    gc->DrawText(timeStr, 10, 10);

    //score
    wxString scoreStr = wxString::Format("Score: %d", static_cast<int>(mScore));
    double scoreWidth, scoreHeight;
    gc->GetTextExtent(scoreStr, &scoreWidth, &scoreHeight);

    gc->DrawRectangle(width - scoreWidth - 15, 5, scoreWidth + 10, scoreHeight + 10);
    gc->DrawText(scoreStr, width - scoreWidth - 10, 10);

    gc->PopState();
}

/**
 * Update the scoreboard
 * @param elapsed Time since last update
 */
void Scoreboard::Update(double elapsed)
{
    if (!mStopWatch) return;

    if(mPowerUp) //check power up time
    {
        long currentTime = mStopWatch->Time();
        if(currentTime - mPowerUpStart >= mPowerUpDuration)
        {
            mPowerUp = false;
        }
    }

    if (elapsed > 0)
    {
        double decay = mDecay * elapsed;
        mScore = std::max(0., (mScore - decay));
    }
}

/**
 * Reset scoreboard
 */
void Scoreboard::Reset()
{
    mScore = 0;
    mPowerUp = false;
    mPowerUpStart = 0;
    if (mStopWatch)
    {
        mStopWatch->Start();
        mLastScore = mStopWatch->Time();
    }
}

/**
 * Add points to score. If power up add 2x points
 * @param points Points to add
 */
void Scoreboard::AddScore(int points)
{
    mScore += points;
    if(mPowerUp)
    {
        mScore += points; //do it again for x2
    }
}

/**
 * Trigger power up for calculating points
 */
void Scoreboard::PowerUp()
{
    if(mStopWatch)
    {
        mPowerUp = true;
        mPowerUpStart = mStopWatch->Time();
    }
}
