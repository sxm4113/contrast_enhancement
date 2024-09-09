#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>
#include <opencv2/opencv.hpp>

class wxImagePanel : public wxPanel
{
private:
    wxImage image;
    cv::Mat image_pyramid;
    cv::Mat image_morphology;

    wxBitmap resized;
    int w, h;

public:
    wxImagePanel(wxFrame* parent, wxString file, cv::Mat image_pyramid, cv::Mat image_morphology, wxBitmapType format);

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);
    void button0();
    void button1();
    void button2(); 
    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()
};


