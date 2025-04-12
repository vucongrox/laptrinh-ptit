#include "customer_frame.h"
#include "login_frame.h" 

CustomerFrame::CustomerFrame(const wxString& title, int userId) 
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 400)), userId(userId) {
    customer = new Customer();
    customer->loadFromId(userId);
    
    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    notebook = new wxNotebook(mainPanel, wxID_ANY);
    
    // Tab 1: View Info
    wxPanel* infoPanel = new wxPanel(notebook);
    wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
    wxButton* viewInfoBtn = new wxButton(infoPanel, wxID_ANY, "Xem Thong Tin");
    outputText = new wxTextCtrl(infoPanel, wxID_ANY, "", wxDefaultPosition, wxSize(450, 150), 
                                wxTE_MULTILINE | wxTE_READONLY);
    infoSizer->Add(viewInfoBtn, 0, wxALL, 5);
    infoSizer->Add(outputText, 1, wxEXPAND | wxALL, 5);
    infoPanel->SetSizer(infoSizer);
    notebook->AddPage(infoPanel, "Thong Tin");
    
    // Tab 2: Change Password
    wxPanel* passwordPanel = new wxPanel(notebook);
    wxBoxSizer* passwordSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* passwordInputSizer = new wxBoxSizer(wxHORIZONTAL);
    passwordInputSizer->Add(new wxStaticText(passwordPanel, wxID_ANY, "Mat Khau Cu:"), 
                           0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    oldPasswordInput = new wxTextCtrl(passwordPanel, wxID_ANY, "", wxDefaultPosition, 
                                      wxDefaultSize, wxTE_PASSWORD);
    passwordInputSizer->Add(oldPasswordInput, 1, wxALL | wxEXPAND, 5);
    passwordInputSizer->Add(new wxStaticText(passwordPanel, wxID_ANY, "Mat Khau Moi:"), 
                           0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    newPasswordInput = new wxTextCtrl(passwordPanel, wxID_ANY, "", wxDefaultPosition, 
                                      wxDefaultSize, wxTE_PASSWORD);
    passwordInputSizer->Add(newPasswordInput, 1, wxALL | wxEXPAND, 5);
    wxButton* changePasswordBtn = new wxButton(passwordPanel, wxID_ANY, "Doi Mat Khau");
    passwordSizer->Add(passwordInputSizer, 0, wxEXPAND | wxALL, 5);
    passwordSizer->Add(changePasswordBtn, 0, wxALL, 5);
    passwordPanel->SetSizer(passwordSizer);
    notebook->AddPage(passwordPanel, "Doi Mat Khau");
    
    // Tab 3: Update Info
    wxPanel* updatePanel = new wxPanel(notebook);
    wxBoxSizer* updateSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* updateInputSizer = new wxBoxSizer(wxHORIZONTAL);
    updateInputSizer->Add(new wxStaticText(updatePanel, wxID_ANY, "Ten:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    nameInput = new wxTextCtrl(updatePanel, wxID_ANY);
    updateInputSizer->Add(nameInput, 1, wxALL | wxEXPAND, 5);
    updateInputSizer->Add(new wxStaticText(updatePanel, wxID_ANY, "Ngay Sinh:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    dobInput = new wxTextCtrl(updatePanel, wxID_ANY);
    updateInputSizer->Add(dobInput, 1, wxALL | wxEXPAND, 5);
    wxBoxSizer* addrSizer = new wxBoxSizer(wxHORIZONTAL);
    addrSizer->Add(new wxStaticText(updatePanel, wxID_ANY, "Dia Chi:"), 
                   0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    addressInput = new wxTextCtrl(updatePanel, wxID_ANY);
    addrSizer->Add(addressInput, 1, wxALL | wxEXPAND, 5);
    wxButton* updateBtn = new wxButton(updatePanel, wxID_ANY, "Cap Nhat");
    updateSizer->Add(updateInputSizer, 0, wxEXPAND | wxALL, 5);
    updateSizer->Add(addrSizer, 0, wxEXPAND | wxALL, 5);
    updateSizer->Add(updateBtn, 0, wxALL, 5);
    updatePanel->SetSizer(updateSizer);
    notebook->AddPage(updatePanel, "Cap Nhat Thong Tin");

    // Tab 4: Transfer Points
    wxPanel* transferPanel = new wxPanel(notebook);
    wxBoxSizer* transferSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* transferInputSizer = new wxBoxSizer(wxHORIZONTAL);
    transferInputSizer->Add(new wxStaticText(transferPanel, wxID_ANY, "Username Nguoi Nhan:"), 
                           0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    receiverUsernameInput = new wxTextCtrl(transferPanel, wxID_ANY);
    transferInputSizer->Add(receiverUsernameInput, 1, wxALL | wxEXPAND, 5);
    transferInputSizer->Add(new wxStaticText(transferPanel, wxID_ANY, "Diem Chuyen:"), 
                           0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    transferPointsInput = new wxTextCtrl(transferPanel, wxID_ANY);
    transferInputSizer->Add(transferPointsInput, 1, wxALL | wxEXPAND, 5);
    wxButton* transferPointsBtn = new wxButton(transferPanel, wxID_ANY, "Chuyen Diem");
    transferSizer->Add(transferInputSizer, 0, wxEXPAND | wxALL, 5);
    transferSizer->Add(transferPointsBtn, 0, wxALL, 5);
    transferPanel->SetSizer(transferSizer);
    notebook->AddPage(transferPanel, "Chuyen Diem");

    // Tab 5: Search Customer
    wxPanel* searchPanel = new wxPanel(notebook);
    wxBoxSizer* searchSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* searchInputSizer = new wxBoxSizer(wxHORIZONTAL);
    searchInputSizer->Add(new wxStaticText(searchPanel, wxID_ANY, "Username:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    searchUsernameInput = new wxTextCtrl(searchPanel, wxID_ANY);
    searchInputSizer->Add(searchUsernameInput, 1, wxALL | wxEXPAND, 5);
    wxButton* searchBtn = new wxButton(searchPanel, wxID_ANY, "Tim Kiem");
    searchSizer->Add(searchInputSizer, 0, wxEXPAND | wxALL, 5);
    searchSizer->Add(searchBtn, 0, wxALL, 5);
    searchPanel->SetSizer(searchSizer);
    notebook->AddPage(searchPanel, "Tim Khach Hang");

    // Tab 6: Transaction History
    wxPanel* historyPanel = new wxPanel(notebook);
    wxBoxSizer* historySizer = new wxBoxSizer(wxVERTICAL);
    wxButton* viewHistoryBtn = new wxButton(historyPanel, wxID_ANY, "Xem Lich Su");
    historyText = new wxTextCtrl(historyPanel, wxID_ANY, "", wxDefaultPosition, wxSize(450, 150), 
                                 wxTE_MULTILINE | wxTE_READONLY);
    historySizer->Add(viewHistoryBtn, 0, wxALL, 5);
    historySizer->Add(historyText, 1, wxEXPAND | wxALL, 5);
    historyPanel->SetSizer(historySizer);
    notebook->AddPage(historyPanel, "Lich Su Giao Dich");
    
    wxButton* logoutBtn = new wxButton(mainPanel, wxID_ANY, "Dang Xuat");
    
    mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(logoutBtn, 0, wxALL | wxALIGN_CENTER, 5);
    mainPanel->SetSizer(mainSizer);
    
    // Bind events
    viewInfoBtn->Bind(wxEVT_BUTTON, &CustomerFrame::OnViewInfo, this);
    changePasswordBtn->Bind(wxEVT_BUTTON, &CustomerFrame::OnChangePassword, this);
    updateBtn->Bind(wxEVT_BUTTON, &CustomerFrame::OnUpdateInfo, this);
    transferPointsBtn->Bind(wxEVT_BUTTON, &CustomerFrame::OnTransferPoints, this);
    searchBtn->Bind(wxEVT_BUTTON, &CustomerFrame::OnSearchCustomer, this);
    viewHistoryBtn->Bind(wxEVT_BUTTON, &CustomerFrame::OnViewHistory, this);
    logoutBtn->Bind(wxEVT_BUTTON, &CustomerFrame::OnLogout, this);
    Bind(wxEVT_CLOSE_WINDOW, &CustomerFrame::OnClose, this);

    Centre(); 
}
