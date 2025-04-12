#include "login_frame.h"

LoginFrame::LoginFrame(const wxString& title) 
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 300)) {
    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    notebook = new wxNotebook(mainPanel, wxID_ANY);

    // Tab 1: Login
    wxPanel* loginPanel = new wxPanel(notebook);
    wxBoxSizer* loginSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* loginUsernameSizer = new wxBoxSizer(wxHORIZONTAL);
    loginUsernameSizer->Add(new wxStaticText(loginPanel, wxID_ANY, "Username:"), 
                            0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    loginUsernameInput = new wxTextCtrl(loginPanel, wxID_ANY);
    loginUsernameSizer->Add(loginUsernameInput, 1, wxALL | wxEXPAND, 5);
    loginSizer->Add(loginUsernameSizer, 0, wxEXPAND);

    wxBoxSizer* loginPasswordSizer = new wxBoxSizer(wxHORIZONTAL);
    loginPasswordSizer->Add(new wxStaticText(loginPanel, wxID_ANY, "Password:"), 
                            0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    loginPasswordInput = new wxTextCtrl(loginPanel, wxID_ANY, "", 
                                       wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    loginPasswordSizer->Add(loginPasswordInput, 1, wxALL | wxEXPAND, 5);
    loginSizer->Add(loginPasswordSizer, 0, wxEXPAND);

    wxButton* loginBtn = new wxButton(loginPanel, wxID_ANY, "Dang Nhap");
    loginSizer->Add(loginBtn, 0, wxALL | wxALIGN_CENTER, 10);

    loginPanel->SetSizer(loginSizer);
    notebook->AddPage(loginPanel, "Dang Nhap");

    // Tab 2: Register
    wxPanel* registerPanel = new wxPanel(notebook);
    wxBoxSizer* registerSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* regUsernameSizer = new wxBoxSizer(wxHORIZONTAL);
    regUsernameSizer->Add(new wxStaticText(registerPanel, wxID_ANY, "Username:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    regUsernameInput = new wxTextCtrl(registerPanel, wxID_ANY);
    regUsernameSizer->Add(regUsernameInput, 1, wxALL | wxEXPAND, 5);
    registerSizer->Add(regUsernameSizer, 0, wxEXPAND);

    wxBoxSizer* regPasswordSizer = new wxBoxSizer(wxHORIZONTAL);
    regPasswordSizer->Add(new wxStaticText(registerPanel, wxID_ANY, "Password:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    regPasswordInput = new wxTextCtrl(registerPanel, wxID_ANY, "", 
                                     wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    regPasswordSizer->Add(regPasswordInput, 1, wxALL | wxEXPAND, 5);
    registerSizer->Add(regPasswordSizer, 0, wxEXPAND);

    wxBoxSizer* dobSizer = new wxBoxSizer(wxHORIZONTAL);
    dobSizer->Add(new wxStaticText(registerPanel, wxID_ANY, "Ngay Sinh:"), 
                  0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    dobInput = new wxTextCtrl(registerPanel, wxID_ANY);
    dobSizer->Add(dobInput, 1, wxALL | wxEXPAND, 5);
    registerSizer->Add(dobSizer, 0, wxEXPAND);

    wxBoxSizer* addressSizer = new wxBoxSizer(wxHORIZONTAL);
    addressSizer->Add(new wxStaticText(registerPanel, wxID_ANY, "Dia Chi:"), 
                      0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    addressInput = new wxTextCtrl(registerPanel, wxID_ANY);
    addressSizer->Add(addressInput, 1, wxALL | wxEXPAND, 5);
    registerSizer->Add(addressSizer, 0, wxEXPAND);

    wxButton* registerBtn = new wxButton(registerPanel, wxID_ANY, "Dang Ky");
    registerSizer->Add(registerBtn, 0, wxALL | wxALIGN_CENTER, 10);

    registerPanel->SetSizer(registerSizer);
    notebook->AddPage(registerPanel, "Dang Ky");

    mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 5);
    mainPanel->SetSizer(mainSizer);

    loginBtn->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);
    registerBtn->Bind(wxEVT_BUTTON, &LoginFrame::OnRegister, this);
}

void LoginFrame::OnLogin(wxCommandEvent& event) {
    std::string username = loginUsernameInput->GetValue().ToStdString();
    std::string password = loginPasswordInput->GetValue().ToStdString();
    if (username.empty() || password.empty()) {
        wxMessageBox("Vui long nhap day du thong tin!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    
    User user; // Tạo một đối tượng User để kiểm tra đăng nhập
    if (user.login(username, password)) {
        this->Hide();
        if (user.getAccountType() == 1) { // Manager
            ManagerFrame* managerFrame = new ManagerFrame("Quan Ly", user.getId());
            managerFrame->Show(true);
        } else { // Customer
            CustomerFrame* customerFrame = new CustomerFrame("Khach Hang", user.getId());
            customerFrame->Show(true);
        }
    } else {
        wxMessageBox("Dang nhap that bai!", "Loi", wxOK | wxICON_ERROR);
    }
}

void LoginFrame::OnRegister(wxCommandEvent& event) {
    std::string username = regUsernameInput->GetValue().ToStdString();
    std::string password = regPasswordInput->GetValue().ToStdString();
    std::string dob = dobInput->GetValue().ToStdString();
    std::string address = addressInput->GetValue().ToStdString();
    std::string name = nameInput->GetValue().ToStdString(); // Thêm dòng này để lấy name

    if (username.empty() || password.empty() || dob.empty() || address.empty() || name.empty()) {
        wxMessageBox("Vui long nhap day du thong tin!", "Loi", wxOK | wxICON_ERROR);
        return;
    }

    if (User::registerAccount(username, password, name, dob, address)) { // Xóa dấu ; và sửa cú pháp
        wxMessageBox("Dang ky thanh cong! Vui long dang nhap.", "Thanh cong", 
                     wxOK | wxICON_INFORMATION);
        regUsernameInput->Clear();
        regPasswordInput->Clear();
        dobInput->Clear();
        addressInput->Clear();
        nameInput->Clear(); // Thêm dòng này để xóa ô name
        notebook->SetSelection(0); // Chuyển sang tab đăng nhập
    } else {
        wxMessageBox("Dang ky that bai! Username co the da ton tai.", "Loi", 
                     wxOK | wxICON_ERROR);
    }
}
