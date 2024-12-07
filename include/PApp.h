#ifndef _PAPP_
#define _PAPP_

#include <wx/wx.h>

#define PROJECT_NAME "PoolUP"

class PApp : public wxApp
{
private:
    /* data */
public:
    virtual bool OnInit();
};

#endif