/**
 * @file GameApp.cpp
 *
 * @author Michael Dreon
 */

#include "pch.h"
#include <MainFrame.h>
#include "GameApp.h"

#ifndef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#endif

/**
 * Initialize the application
 * @return
 */
bool GameApp::OnInit()
{
    /// Debug information
#ifdef WIN32
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    /// If the app doesnt start correctly
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}