#include "PApp.h"
#include "mainframe.h"

bool PApp::OnInit()
{
    PFrame *frame = new PFrame(wxT(PROJECT_NAME));
    frame->Show(true);
    //frame->Maximize();
    return true;
}

wxIMPLEMENT_APP(PApp);