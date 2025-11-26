/**
 * @file GameApp.h
 *
 * @author Michael Dreon
 *
 * Game App Class
 */

#ifndef PROJECT1_GAMEAPP_H
#define PROJECT1_GAMEAPP_H

/**
 * Main application class
 */
class GameApp : public wxApp
{
public:
    // Initialize the application
    bool OnInit() override;
};


#endif //PROJECT1_GAMEAPP_H