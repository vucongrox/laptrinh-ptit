#include "login_frame.h"

LoginFrame::LoginFrame(const wxString& title) 
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 500)) {
    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    notebook = new wxNotebook(mainPanel, wxID_ANY);

    // Tab 1: Login
    wxPanel* loginPanel = new wxPanel(notebook);
    wxBoxSizer* loginSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* loginUsernameSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* loginUsernameLabel = new wxStaticText(loginPanel, wxID_ANY, "Username:");
    loginUsernameLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    loginUsernameSizer->Add(loginUsernameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    loginUsernameInput = new wxTextCtrl(loginPanel, wxID_ANY);
    loginUsernameInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    loginUsernameSizer->Add(loginUsernameInput, 1, wxALL | wxEXPAND, 10);
    loginSizer->Add(loginUsernameSizer, 0, wxEXPAND);

    wxBoxSizer* loginPasswordSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* loginPasswordLabel = new wxStaticText(loginPanel, wxID_ANY, "Password:");
    loginPasswordLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    loginPasswordSizer->Add(loginPasswordLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    loginPasswordInput = new wxTextCtrl(loginPanel, wxID_ANY, "", 
                                       wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    loginPasswordInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    loginPasswordSizer->Add(loginPasswordInput, 1, wxALL | wxEXPAND, 10);
    loginSizer->Add(loginPasswordSizer, 0, wxEXPAND);

    wxButton* loginBtn = new wxButton(loginPanel, wxID_ANY, "Dang Nhap");
    loginBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    loginSizer->Add(loginBtn, 0, wxALL | wxALIGN_CENTER, 10);

    loginPanel->SetSizer(loginSizer);
    notebook->AddPage(loginPanel, "Dang Nhap");

    // Tab 2: Register
    wxPanel* registerPanel = new wxPanel(notebook);
    wxBoxSizer* registerSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* regUsernameSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* regUsernameLabel = new wxStaticText(registerPanel, wxID_ANY, "Username:");
    regUsernameLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    regUsernameSizer->Add(regUsernameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    regUsernameInput = new wxTextCtrl(registerPanel, wxID_ANY);
    regUsernameInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    regUsernameSizer->Add(regUsernameInput, 1, wxALL | wxEXPAND, 10);
    registerSizer->Add(regUsernameSizer, 0, wxEXPAND);

    wxBoxSizer* regPasswordSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* regPasswordLabel = new wxStaticText(registerPanel, wxID_ANY, "Password:");
    regPasswordLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    regPasswordSizer->Add(regPasswordLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    regPasswordInput = new wxTextCtrl(registerPanel, wxID_ANY, "", 
                                     wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    regPasswordInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    regPasswordSizer->Add(regPasswordInput, 1, wxALL | wxEXPAND, 10);
    registerSizer->Add(regPasswordSizer, 0, wxEXPAND);

    wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* nameLabel = new wxStaticText(registerPanel, wxID_ANY, "Ten:");
    nameLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    nameSizer->Add(nameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    nameInput = new wxTextCtrl(registerPanel, wxID_ANY);
    nameInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    nameSizer->Add(nameInput, 1, wxALL | wxEXPAND, 10);
    registerSizer->Add(nameSizer, 0, wxEXPAND);

    wxBoxSizer* dobSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* dobLabel = new wxStaticText(registerPanel, wxID_ANY, "Ngay Sinh:");
    dobLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    dobSizer->Add(dobLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    dobInput = new wxTextCtrl(registerPanel, wxID_ANY);
    dobInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    dobSizer->Add(dobInput, 1, wxALL | wxEXPAND, 10);
    registerSizer->Add(dobSizer, 0, wxEXPAND);

    wxBoxSizer* addressSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* addressLabel = new wxStaticText(registerPanel, wxID_ANY, "Dia Chi:");
    addressLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    addressSizer->Add(addressLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    addressInput = new wxTextCtrl(registerPanel, wxID_ANY);
    addressInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    addressSizer->Add(addressInput, 1, wxALL | wxEXPAND, 10);
    registerSizer->Add(addressSizer, 0, wxEXPAND);

    wxButton* registerBtn = new wxButton(registerPanel, wxID_ANY, "Dang Ky");
    registerBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    registerSizer->Add(registerBtn, 0, wxALL | wxALIGN_CENTER, 10);

    registerPanel->SetSizer(registerSizer);
    notebook->AddPage(registerPanel, "Dang Ky");

    mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 10);
    mainPanel->SetSizer(mainSizer);

    loginBtn->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);
    registerBtn->Bind(wxEVT_BUTTON, &LoginFrame::OnRegister, this);

    Centre();
}

void LoginFrame::OnLogin(wxCommandEvent& event) {
    std::string username = loginUsernameInput->GetValue().ToStdString();
    std::string password = loginPasswordInput->GetValue().ToStdString();
    if (username.empty() || password.empty()) {
        wxMessageBox("Vui long nhap day du thong tin!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    
    User user;
    if (!user.login(username, password)) {
        wxMessageBox("Dang nhap that bai!", "Loi", wxOK | wxICON_ERROR);
        return;
    }

    if (user.getId() <= 0) {
        wxMessageBox("Khong the tai thong tin nguoi dung!", "Loi", wxOK | wxICON_ERROR);
        return;
    }

    this->Hide();
    if (user.getAccountType() == 1) { // Manager
        ManagerFrame* managerFrame = new ManagerFrame("Quan Ly", user.getId());
        managerFrame->Show(true);
    } else { // Customer
        CustomerFrame* customerFrame = new CustomerFrame("Khach Hang", user.getId());
        customerFrame->Show(true);
    }
}

void LoginFrame::OnRegister(wxCommandEvent& event) {
    std::string username = regUsernameInput->GetValue().ToStdString();
    std::string password = regPasswordInput->GetValue().ToStdString();
    std::string dob = dobInput->GetValue().ToStdString();
    std::string address = addressInput->GetValue().ToStdString();
    std::string name = nameInput->GetValue().ToStdString();

    if (username.empty() || password.empty() || dob.empty() || address.empty() || name.empty()) {
        wxMessageBox("Vui long nhap day du thong tin!", "Loi", wxOK | wxICON_ERROR);
        return;
    }

    if (User::registerAccount(username, password, name, dob, address)) {
        wxMessageBox("Dang ky thanh cong! Vui long dang nhap.", "Thanh cong", 
                     wxOK | wxICON_INFORMATION);
        regUsernameInput->Clear();
        regPasswordInput->Clear();
        dobInput->Clear();
        addressInput->Clear();
        nameInput->Clear();
        notebook->SetSelection(0);
    } else {
        wxMessageBox("Dang ky that bai! Username co the da ton tai.", "Loi", 
                     wxOK | wxICON_ERROR);
    }
}
