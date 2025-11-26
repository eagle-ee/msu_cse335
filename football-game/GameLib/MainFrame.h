/**
 * @file MainFrame.h
 *
 * @author Michael Dreon and Eduardo Jimenez
 *
 * The top-level (main) frame of the application
 */

#ifndef GAME_MAINFRAME_H
#define GAME_MAINFRAME_H

#include "GameView.h"

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    GameView* mGameView = nullptr;

    /**
     * Exit menu option handlers
     * @param event
     */
    void OnExit(wxCommandEvent& event);

    /**
     * Close window handler
     * @param event Close event
     */
    void OnClose(wxCloseEvent& event);

public:
    // Creates actual mainframe window on screen
    void Initialize();
    void OnAbout(wxCommandEvent& event);
};

#endif //GAME_MAINFRAME_H