#ifndef MANAGER_FRAME_H
#define MANAGER_FRAME_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "manager.h"
#include "login_frame.h"

class ManagerFrame : public wxFrame {
public:
    ManagerFrame(const wxString& title, int userId);
    ~ManagerFrame();

private:
    int userId;
    Manager* manager;
    wxNotebook* notebook;
    wxTextCtrl* infoOutputText;
    wxTextCtrl* customersOutputText;
    wxTextCtrl* usernameInput;
    wxTextCtrl* passwordInput;
    wxTextCtrl* dobInput;
    wxTextCtrl* addressInput;
    wxTextCtrl* customerIdInput;
    wxTextCtrl* pointsInput;
    wxTextCtrl* updateIdInput; // Giờ là username
    wxTextCtrl* updateDobInput;
    wxTextCtrl* updateAddressInput;
    wxTextCtrl* historyText;
    wxTextCtrl* totalPointsInput; // Thêm cho tab mới
    wxButton* logoutBtn;

    void OnViewInfo(wxCommandEvent& event);
    void OnViewCustomers(wxCommandEvent& event);
    void OnAddCustomer(wxCommandEvent& event);
    void OnAddPoints(wxCommandEvent& event);
    void OnUpdateUserInfo(wxCommandEvent& event);
    void OnViewHistory(wxCommandEvent& event);
    void OnAddTotalPoints(wxCommandEvent& event); // Thêm hàm mới
    void OnLogout(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
};

#endif
