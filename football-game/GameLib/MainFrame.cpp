/**
 * @file MainFrame.cpp
 *
 * @author Michael Dreon and Eduardo Jimenez
 *
 * The top-level (main) frame of the application
 */

#include "pch.h"
#include "MainFrame.h"
#include "ids.h"

#include "GameView.h"

/**
 * When we want to exit the application
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Initialize the MainFrame window
 */
void MainFrame::Initialize()
{
    // Create a window
    Create(nullptr,wxID_ANY, L"Spartan Touchdown",
        wxDefaultPosition, wxSize(1000,800));

    // Create a sizer that will lay out child windows vertically
    // one above another
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto gameView = new GameView();
    gameView->Initialize(this);
    mGameView = gameView;

    // Add it to the sizer
    sizer->Add(gameView,1, wxEXPAND | wxALL );
    SetSizer( sizer );

    Layout();

    auto menuBar = new wxMenuBar();

    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    menuBar->Append(fileMenu, "File");
    menuBar->Append(helpMenu, "Help");
    menuBar->Append(levelMenu, "Levels");

    fileMenu->Append(wxID_EXIT, "&Exit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    levelMenu->Append(IDM_RESTARTLEVEL, "&Restart Level\tCtrl-R", "Restart the current level");
    levelMenu->AppendSeparator();
    levelMenu->Append(IDM_LEVELZERO, "&Level 0", "Level 0");
    levelMenu->Append(IDM_LEVELONE, "&Level 1", "Level 1");
    levelMenu->Append(IDM_LEVELTWO, "&Level 2", "Level 2");
    levelMenu->Append(IDM_LEVELTHREE, "&Level 3", "Level 3");
    SetMenuBar(menuBar);

    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to the Spartan Touchdown!",
        L"About Spartan Touchdown",
        wxOK,
        this);
}

void MainFrame::OnClose(wxCloseEvent& event)
{
    if (mGameView)
    {
        mGameView->Shutdown();
    }
    Destroy();
}

