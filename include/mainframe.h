#ifndef _MAINFRAME_
#define _MAINFRAME_

#include <wx/wx.h>
#include <wx/dcclient.h>
#include <wx/splitter.h>
#include <wx/dcbuffer.h>
#include <wx/treectrl.h>
#include <wx/artprov.h>

/* 
*
* @brief main frame for the application
*/

class PFrame : public wxFrame
{
private:
    /* 
    * @brief main panel
    */
    wxPanel *m_panel;

    wxPanel* vt_panel;
    wxPanel* sk_panel;
    wxPanel* r1_panel;
    wxPanel* r2_panel;

    wxBitmap m_bitmap;
    wxBitmap m2_bitmap;
    int m_triangleTopX, m_triangleTopY,m_triangleLeftX, m_triangleLeftY = 0;
    
    
    /*
    *
    *   event hanles on apps main frame
    */
    
    void OnMouseMove(wxMouseEvent &event);
    
    void OnPaint(wxPaintEvent &event);

    void DrawRuler(wxDC &dc);

    void DrawFollowerLine(wxDC &dc, int x1, int y1, int x2, int y2, const wxBrush &brush);

    void DrawSoftkeyLine(wxPaintEvent &event);  

    void DenemeResim(wxPaintEvent &event);
    void DenemeResim2(wxPaintEvent &event);
    /*event * */
     /*
    *
    *@brief does the menu stuffs 
    */

    void SetUpMenu();

    /*
    *
    *@brief Creates Tree model for iop objects 
    *
    * @return    number of object created
    */
    int CreateObjectPoolTree(wxTreeCtrl* tc, wxImageList* imageList);


    void ParsIOPXML();

public:
    PFrame(const wxString &title);
};

#endif