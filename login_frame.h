#ifndef LOGIN_FRAME_H
#define LOGIN_FRAME_H

#include <wx/wx.h>
#include "user.h"
#include "customer.h"
#include "manager.h"
#include "customer_frame.h"
#include "manager_frame.h"

class LoginFrame : public wxFrame {
public:
    LoginFrame(const wxString& title);

private:
    wxNotebook* notebook;
    wxTextCtrl* loginUsernameInput;
    wxTextCtrl* loginPasswordInput;
    wxTextCtrl* regUsernameInput;
    wxTextCtrl* regPasswordInput;
    wxTextCtrl* dobInput;
    wxTextCtrl* addressInput;
    wxTextCtrl* nameInput;
    void OnLogin(wxCommandEvent& event);
    void OnRegister(wxCommandEvent& event);
};

#endif
