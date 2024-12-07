#include "mainframe.h"

PFrame::PFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxPoint(100, 100), wxSize(500, 300))
{
    wxImage::AddHandler(new wxPNGHandler); 
    wxImage::AddHandler(new wxJPEGHandler); 
    SetUpMenu();

    wxSplitterWindow* m_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                                                                 wxSP_3DBORDER | wxSP_LIVE_UPDATE);
 
    // Paneli oluştur
    m_panel = new wxPanel(m_splitter);
    vt_panel = new wxPanel(m_panel, wxID_ANY, wxPoint(120, 60), wxSize(600,600));
    sk_panel = new wxPanel(m_panel, wxID_ANY, wxPoint(720, 60), wxSize(160,600));

    vt_panel->SetBackgroundColour(wxColour(255,255,255));
    sk_panel->SetBackgroundColour(wxColour(255,255,255));

    
    m_splitter->SetMinimumPaneSize(200);

    wxTreeCtrl* m_treeCtrl = new wxTreeCtrl(m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_LINES_AT_ROOT | wxTR_HAS_BUTTONS);

    wxImageList* imageList = new wxImageList(16, 16, true);

    this->CreateObjectPoolTree(m_treeCtrl, imageList);

    m_treeCtrl->ExpandAll();

    m_splitter->SetSashGravity(0);
    m_splitter->SplitVertically(m_treeCtrl, m_panel);

    m_panel->Bind(wxEVT_PAINT, &PFrame::OnPaint, this);
    
    sk_panel->Bind(wxEVT_PAINT, &PFrame::DrawSoftkeyLine, this);
    // Fare olaylarını dinle
    vt_panel->Bind(wxEVT_MOTION, &PFrame::OnMouseMove, this);
    
    ////////////
    wxImage image("deneme.PNG", wxBITMAP_TYPE_PNG);
    if (image.IsOk()) {
        // Resmi boyutunu al
        int width = image.GetWidth();
        int height = image.GetHeight();
        
        // wxBitmap oluştur
        m_bitmap = wxBitmap(image);
        
        // Paneli yeniden boyayın
        vt_panel->Refresh();
    }
    wxImage image2("anim.jpg", wxBITMAP_TYPE_JPEG);
    if (image2.IsOk()) {
        // Resmi boyutunu al
        int width = image2.GetWidth();
        int height = image2.GetHeight();
        
        // wxBitmap oluştur
        m2_bitmap = wxBitmap(image2);
        
        // Paneli yeniden boyayın
        sk_panel->Refresh();
    }
    vt_panel->Bind(wxEVT_PAINT, &PFrame::DenemeResim, this);
 }

void PFrame::DenemeResim(wxPaintEvent& event)
{
    wxPaintDC dc(vt_panel);
        // Bitmap'i panele çiz
    dc.DrawBitmap(m_bitmap, 0, 0, false);
}

void PFrame::DenemeResim2(wxPaintEvent& event)
{
    wxPaintDC dc(sk_panel);
        // Bitmap'i panele çiz
    dc.DrawBitmap(m2_bitmap, 160, 0, false);
}

void PFrame::OnPaint(wxPaintEvent &event)
{
    wxBufferedPaintDC dc(m_panel);
    
    dc.Clear();

    // Cetvelleri çiz
    this->DrawRuler(dc);

    // Üstteki çizgiyi çiz
    this->DrawFollowerLine(dc, m_triangleTopX, 0, m_triangleTopX, 20, *wxRED_BRUSH);

    // Soldaki çizgiyi çiz
    this->DrawFollowerLine(dc, 0, m_triangleLeftY, 20, m_triangleLeftY, *wxRED_BRUSH);

}

void PFrame::DrawRuler(wxDC &dc)
{
    // Panelin boyutlarını al
    int width, height;
    m_panel->GetSize(&width, &height);

    // Üst cetveli çiz
    int spacing = 10;
    dc.SetPen(*wxBLACK_PEN);

    wxFont font(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc.SetFont(font);

    for (int x = 60; x < 800; x += spacing)
    {
        dc.DrawLine(x, 0, x, 5);
        wxString coordStr = wxString::Format(wxT("%d"), x - 120);
        if(!(x % 20))dc.DrawText(coordStr, x - 5, 5);
    }

    // Sol cetveli çiz
    for (int y = 20; y < 700; y += spacing)
    {
        dc.DrawLine(0, y, 5, y);
        wxString coordStr = wxString::Format(wxT("%d"), y - 60);
        if(!(y % 20))dc.DrawText(coordStr, 5, y - 5);
    }
}

void PFrame::DrawFollowerLine(wxDC &dc, int x1, int y1, int x2, int y2, const wxBrush &brush)
{
    wxPen pen(wxColour(255, 0, 0), 5, wxPenStyle::wxPENSTYLE_SOLID);
    dc.SetPen(pen);
    dc.DrawLine(x1, y1, x2, y2);
}

void PFrame::DrawSoftkeyLine(wxPaintEvent &event)
{
    wxPaintDC sk_dc(sk_panel);

    sk_dc.Clear();
    sk_dc.DrawBitmap(m2_bitmap, 80, 0, false);
    sk_dc.SetPen(*wxBLACK_DASHED_PEN);
    
    sk_dc.DrawLine(0, 0, 0, 600);
    sk_dc.DrawLine(0, 0, 160, 0);
    sk_dc.DrawLine(0, 600, 160, 600);
    sk_dc.DrawLine(80, 0, 80, 600);
    sk_dc.DrawLine(160, 0, 160, 600);

    for (size_t i = 0; i < 6; i++)
    {
        sk_dc.DrawLine(0, 0 + i*(600/5), 160, i*(600/5));    
    }

    
}


void PFrame::OnMouseMove(wxMouseEvent &event)
{
    // Fare konumunu al
    wxPoint mousePos = event.GetPosition();

    // Üstteki çizginin konumunu güncelle
    m_triangleTopX = mousePos.x + 120;
    m_triangleTopY = 0;

    // Soldaki çizginin konumunu güncelle
    m_triangleLeftX = 0;
    m_triangleLeftY = mousePos.y + 60;

    // Paneli yeniden çiz (sadece çizgileri)
    m_panel->Refresh(false);
}

void PFrame::SetUpMenu()
{
    wxMenuBar* mainmanu  = new wxMenuBar();

    wxMenu* filemenu = new wxMenu();
    filemenu->Append(wxID_NEW);
    filemenu->Append(wxID_OPEN);
    filemenu->AppendSeparator();
    filemenu->Append(wxID_SAVE);
    filemenu->Append(wxID_SAVEAS);

    wxMenu* editmenu = new wxMenu();
    editmenu->Append(wxID_CUT);
    editmenu->Append(wxID_COPY);

    mainmanu->Append(filemenu, "File");
    mainmanu->Append(editmenu, "Edit");

    SetMenuBar(mainmanu);
}

int PFrame::CreateObjectPoolTree(wxTreeCtrl* tc , wxImageList* imageList)
{
    // Create an image list
    wxIcon rootIcon = wxArtProvider::GetIcon(wxART_GO_TO_PARENT, wxART_OTHER, wxSize(16, 16));
    wxIcon childIcon = wxArtProvider::GetIcon(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
    
    int rootIconIndex = imageList->Add(rootIcon);
    int childIconIndex = imageList->Add(childIcon);

    tc->AssignImageList(imageList);

    // Add root item
    wxTreeItemId rootId = tc->AddRoot("Example IOP", rootIconIndex);

    wxTreeItemId child = tc->AppendItem(rootId, "Working Set", childIconIndex);

    // Add child items
    wxTreeItemId gchild = tc->AppendItem(child, "Data Mask", childIconIndex);
    tc->AppendItem(gchild, "birseyler", childIconIndex);
    tc->AppendItem(rootId, "Picture G.", childIconIndex);
    tc->AppendItem(rootId, "Picture G.", childIconIndex);

    return tc->GetCount();
}

