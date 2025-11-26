/**
 * @file GameView.h
 * @author Eduarod Jimenez and Michael Dreon
 *
 *
 */

#ifndef PROJECT1_GAMEVIEW_H
#define PROJECT1_GAMEVIEW_H
#include "Game.h"
#include "Scoreboard.h"

/**
 * Game Window
 */
class GameView : public wxWindow
{
private:
    /// object for Game
    Game mGame;
    Scoreboard mScoreboard;
    /// The timer that allows for animation
    wxTimer mTimer;
    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;
    /// Left arrow is pressed
    bool mLeftDown = false;
    /// Right arrow is pressed
    bool mRightDown = false;
    /// Space is pressed
    bool mSpaceDown = false;
public:
    ~GameView();
    void Initialize(wxFrame* parent);
    void OnTimer(wxTimerEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnFileSaveAs(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void LoadLevel(int level);
    void LoadLevelZero(wxCommandEvent& event);
    void LoadLevelOne(wxCommandEvent& event);
    void LoadLevelTwo(wxCommandEvent& event);
    void LoadLevelThree(wxCommandEvent& event);
    void Shutdown();
    void OnRestartLevel(wxCommandEvent& event);
};


#endif //PROJECT1_GAMEVIEW_H