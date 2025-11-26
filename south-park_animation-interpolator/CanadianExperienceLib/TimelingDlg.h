/**
 * @file TimelingDlg.h
 * @author b3big
 *
 *
 */
 
#ifndef TIMELINGDLG_H
#define TIMELINGDLG_H
#include "Timeline.h"

/**
 * Dialog for editing timeline properties
 */
class TimelineDlg final : public wxDialog{
private:
    ///The timeline that creates tis object
    Timeline* mTimeline;
    /// Number of frames in the animation
    int mNumberOfFrames;
    ///Frame rate of animation
    int mFrameRate;
public:
    TimelineDlg(wxWindow* parent, Timeline* timeline);
    void OnOK(wxCommandEvent& event);
};



#endif //TIMELINGDLG_H
