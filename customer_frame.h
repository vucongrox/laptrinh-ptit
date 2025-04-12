#ifndef CUSTOMER_FRAME_H
#define CUSTOMER_FRAME_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "customer.h"
#include "login_frame.h"

class CustomerFrame : public wxFrame {
public:
    CustomerFrame(const wxString& title, int userId);
    ~CustomerFrame();

private:
    int userId;
    Customer* customer;
    wxNotebook* notebook;
    wxTextCtrl* outputText;
    wxTextCtrl* oldPasswordInput;
    wxTextCtrl* newPasswordInput;
    wxTextCtrl* receiverUsernameInput;
    wxTextCtrl* transferPointsInput;
    wxTextCtrl* searchUsernameInput;
    wxTextCtrl* nameInput;
    wxTextCtrl* dobInput;
    wxTextCtrl* addressInput;
    wxTextCtrl* historyText;

    void OnViewInfo(wxCommandEvent& event);
    void OnChangePassword(wxCommandEvent& event);
    void OnTransferPoints(wxCommandEvent& event);
    void OnLogout(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnSearchCustomer(wxCommandEvent& event);
    void OnUpdateInfo(wxCommandEvent& event);
    void OnViewHistory(wxCommandEvent& event);
};

#endif
