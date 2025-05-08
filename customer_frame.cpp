#include "customer_frame.h"
#include "login_frame.h"

CustomerFrame::CustomerFrame(const wxString& title, int userId) 
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)), userId(userId) {
    customer = new Customer();
    customer->loadFromId(userId);
    
    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    notebook = new wxNotebook(mainPanel, wxID_ANY);
    
    // Tab 1: View Info
    wxPanel* infoPanel = new wxPanel(notebook);
    wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
    wxButton* viewInfoBtn = new wxButton(infoPanel, wxID_ANY, "Xem Thong Tin");
    viewInfoBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    outputText = new wxTextCtrl(infoPanel, wxID_ANY, "", wxDefaultPosition, wxSize(750, 300), 
                                wxTE_MULTILINE | wxTE_READONLY);
    outputText->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    infoSizer->Add(viewInfoBtn, 0, wxALL | wxALIGN_CENTER, 10);
    infoSizer->Add(outputText, 1, wxEXPAND | wxALL, 10);
    infoPanel->SetSizer(infoSizer);
    notebook->AddPage(infoPanel, "Thong Tin");
    
    // Tab 2: Change Password
    wxPanel* passwordPanel = new wxPanel(notebook);
    wxBoxSizer* passwordSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* passwordInputSizer = new wxBoxSizer(wxHORIZONTAL);
    passwordInputSizer->Add(new wxStaticText(passwordPanel, wxID_ANY, "Mat Khau Cu:"), 
                           0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    oldPasswordInput = new wxTextCtrl(passwordPanel, wxID_ANY, "", wxDefaultPosition, 
                                      wxDefaultSize, wxTE_PASSWORD);
    oldPasswordInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    passwordInputSizer->Add(oldPasswordInput, 1, wxALL | wxEXPAND, 10);
    passwordInputSizer->Add(new wxStaticText(passwordPanel, wxID_ANY, "Mat Khau Moi:"), 
                           0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    newPasswordInput = new wxTextCtrl(passwordPanel, wxID_ANY, "", wxDefaultPosition, 
                                      wxDefaultSize, wxTE_PASSWORD);
    newPasswordInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    passwordInputSizer->Add(newPasswordInput, 1, wxALL | wxEXPAND, 10);
    wxButton* changePasswordBtn = new wxButton(passwordPanel, wxID_ANY, "Doi Mat Khau");
    changePasswordBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    passwordSizer->Add(passwordInputSizer, 0, wxEXPAND | wxALL, 10);
    passwordSizer->Add(changePasswordBtn, 0, wxALL | wxALIGN_CENTER, 10);
    passwordPanel->SetSizer(passwordSizer);
    notebook->AddPage(passwordPanel, "Doi Mat Khau");
    
    // Tab 3: Update Info
    wxPanel* updatePanel = new wxPanel(notebook);
    wxBoxSizer* updateSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* updateInputSizer = new wxBoxSizer(wxHORIZONTAL);
    updateInputSizer->Add(new wxStaticText(updatePanel, wxID_ANY, "Ten:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    nameInput = new wxTextCtrl(updatePanel, wxID_ANY);
    nameInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    updateInputSizer->Add(nameInput, 1, wxALL | wxEXPAND, 10);
    updateInputSizer->Add(new wxStaticText(updatePanel, wxID_ANY, "Ngay Sinh:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    dobInput = new wxTextCtrl(updatePanel, wxID_ANY);
    dobInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    updateInputSizer->Add(dobInput, 1, wxALL | wxEXPAND, 10);
    wxBoxSizer* addrSizer = new wxBoxSizer(wxHORIZONTAL);
    addrSizer->Add(new wxStaticText(updatePanel, wxID_ANY, "Dia Chi:"), 
                   0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    addressInput = new wxTextCtrl(updatePanel, wxID_ANY);
    addressInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    addrSizer->Add(addressInput, 1, wxALL | wxEXPAND, 10);
    wxButton* updateBtn = new wxButton(updatePanel, wxID_ANY, "Cap Nhat");
    updateBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    updateSizer->Add(updateInputSizer, 0, wxEXPAND | wxALL, 10);
    updateSizer->Add(addrSizer, 0, wxEXPAND | wxALL, 10);
    updateSizer->Add(updateBtn, 0, wxALL | wxALIGN_CENTER, 10);
    updatePanel->SetSizer(updateSizer);
    notebook->AddPage(updatePanel, "Cap Nhat Thong Tin");

    // Tab 4: Transfer Points
    wxPanel* transferPanel = new wxPanel(notebook);
    wxBoxSizer* transferSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* transferInputSizer = new wxBoxSizer(wxHORIZONTAL);
    transferInputSizer->Add(new wxStaticText(transferPanel, wxID_ANY, "Username Nguoi Nhan:"), 
                           0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    receiverUsernameInput = new wxTextCtrl(transferPanel, wxID_ANY);
    receiverUsernameInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    transferInputSizer->Add(receiverUsernameInput, 1, wxALL | wxEXPAND, 10);
    transferInputSizer->Add(new wxStaticText(transferPanel, wxID_ANY, "Diem Chuyen:"), 
                           0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    transferPointsInput = new wxTextCtrl(transferPanel, wxID_ANY);
    transferPointsInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    transferInputSizer->Add(transferPointsInput, 1, wxALL | wxEXPAND, 10);
    wxButton* transferPointsBtn = new wxButton(transferPanel, wxID_ANY, "Chuyen Diem");
    transferPointsBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    transferSizer->Add(transferInputSizer, 0, wxEXPAND | wxALL, 10);
    transferSizer->Add(transferPointsBtn, 0, wxALL | wxALIGN_CENTER, 10);
    transferPanel->SetSizer(transferSizer);
    notebook->AddPage(transferPanel, "Chuyen Diem");

    // Tab 5: Search Customer
    wxPanel* searchPanel = new wxPanel(notebook);
    wxBoxSizer* searchSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* searchInputSizer = new wxBoxSizer(wxHORIZONTAL);
    searchInputSizer->Add(new wxStaticText(searchPanel, wxID_ANY, "Username:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    searchUsernameInput = new wxTextCtrl(searchPanel, wxID_ANY);
    searchUsernameInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    searchInputSizer->Add(searchUsernameInput, 1, wxALL | wxEXPAND, 10);
    wxButton* searchBtn = new wxButton(searchPanel, wxID_ANY, "Tim Kiem");
    searchBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    searchSizer->Add(searchInputSizer, 0, wxEXPAND | wxALL, 10);
    searchSizer->Add(searchBtn, 0, wxALL | wxALIGN_CENTER, 10);
    searchResultText = new wxTextCtrl(searchPanel, wxID_ANY, "", wxDefaultPosition, wxSize(750, 300), 
                                      wxTE_MULTILINE | wxTE_READONLY); // Gán vào biến thành viên
    searchResultText->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    searchSizer->Add(searchResultText, 1, wxEXPAND | wxALL, 10);
    searchPanel->SetSizer(searchSizer);
    notebook->AddPage(searchPanel, "Tim Khach Hang");

    // Tab 6: Transaction History
    wxPanel* historyPanel = new wxPanel(notebook);
    wxBoxSizer* historySizer = new wxBoxSizer(wxVERTICAL);
    wxButton* viewHistoryBtn = new wxButton(historyPanel, wxID_ANY, "Xem Lich Su");
    viewHistoryBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    historyText = new wxTextCtrl(historyPanel, wxID_ANY, "", wxDefaultPosition, wxSize(750, 300), 
                                 wxTE_MULTILINE | wxTE_READONLY);
    historyText->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    historySizer->Add(viewHistoryBtn, 0, wxALL | wxALIGN_CENTER, 10);
    historySizer->Add(historyText, 1, wxEXPAND | wxALL, 10);
    historyPanel->SetSizer(historySizer);
    notebook->AddPage(historyPanel, "Lich Su Giao Dich");
    
    wxButton* logoutBtn = new wxButton(mainPanel, wxID_ANY, "Dang Xuat");
    logoutBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    
    mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(logoutBtn, 0, wxALL | wxALIGN_CENTER, 10);
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

CustomerFrame::~CustomerFrame() {
    delete customer;
}

void CustomerFrame::OnViewInfo(wxCommandEvent& event) {
    std::string info = customer->getPersonalInfo();
    outputText->SetValue(info);
}

void CustomerFrame::OnChangePassword(wxCommandEvent& event) {
    std::string oldPassword = oldPasswordInput->GetValue().ToStdString();
    std::string newPassword = newPasswordInput->GetValue().ToStdString();
    if (oldPassword.empty() || newPassword.empty()) {
        wxMessageBox("Vui long nhap day du thong tin!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    if (customer->changePassword(oldPassword, newPassword)) {
        wxMessageBox("Doi mat khau thanh cong!", "Thanh cong", wxOK | wxICON_INFORMATION);
        oldPasswordInput->Clear();
        newPasswordInput->Clear();
    } else {
        wxMessageBox("Mat khau cu khong dung!", "Loi", wxOK | wxICON_ERROR);
    }
}

void CustomerFrame::OnUpdateInfo(wxCommandEvent& event) {
    std::string name = nameInput->GetValue().ToStdString();
    std::string dob = dobInput->GetValue().ToStdString();
    std::string address = addressInput->GetValue().ToStdString();
    if (name.empty() && dob.empty() && address.empty()) {
        wxMessageBox("Vui long nhap it nhat mot truong de cap nhat!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    if (customer->updatePersonalInfo(name, dob, address, this)) {
        wxMessageBox("Cap nhat thong tin thanh cong!", "Thanh cong", wxOK | wxICON_INFORMATION);
        nameInput->Clear();
        dobInput->Clear();
        addressInput->Clear();
        notebook->SetSelection(0);
        OnViewInfo(event);
    } else {
        wxMessageBox("Cap nhat that bai!", "Loi", wxOK | wxICON_ERROR);
    }
}

void CustomerFrame::OnTransferPoints(wxCommandEvent& event) {
    std::string receiverUsername = receiverUsernameInput->GetValue().ToStdString();
    long points;
    if (!transferPointsInput->GetValue().ToLong(&points) || receiverUsername.empty() || points <= 0) {
        wxMessageBox("Vui long nhap day du thong tin va so diem hop le!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    if (customer->transferPoints(receiverUsername, (int)points, this)) {
        wxMessageBox("Chuyen diem thanh cong!", "Thanh cong", wxOK | wxICON_INFORMATION);
        receiverUsernameInput->Clear();
        transferPointsInput->Clear();
        notebook->SetSelection(0);
        OnViewInfo(event);
    } else {
        wxMessageBox("Chuyen diem that bai! Kiem tra username hoac so diem.", "Loi", wxOK | wxICON_ERROR);
    }
}

void CustomerFrame::OnSearchCustomer(wxCommandEvent& event) {
    std::string username = searchUsernameInput->GetValue().ToStdString();
    if (username.empty()) {
        wxMessageBox("Vui long nhap username!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    std::string output;
    if (customer->findCustomerByUsername(username, output)) {
        searchResultText->SetValue(output);
    } else {
        wxMessageBox(output.empty() ? "Khong tim thay khach hang!" : output, "Ket Qua", wxOK | wxICON_INFORMATION);
    }
}

void CustomerFrame::OnViewHistory(wxCommandEvent& event) {
    std::string history = customer->getTransactionHistory();
    if (history.empty()) {
        historyText->SetValue("Khong co giao dich nao.");
    } else {
        historyText->SetValue(history);
    }
}

void CustomerFrame::OnLogout(wxCommandEvent& event) {
    if (customer) {
        delete customer;
        customer = nullptr;
    }
    LoginFrame* loginFrame = new LoginFrame("Dang Nhap");
    loginFrame->Show(true);
    this->Hide();
}

void CustomerFrame::OnClose(wxCloseEvent& event) {
    if (customer) {
        delete customer;
        customer = nullptr;
    }
    LoginFrame* loginFrame = new LoginFrame("Dang Nhap");
    loginFrame->Show(true);
    Destroy();
}
