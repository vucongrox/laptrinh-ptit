#include <wx/wx.h>
#include "login_frame.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        LoginFrame* frame = new LoginFrame("Dang Nhap");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
