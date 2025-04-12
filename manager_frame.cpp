#include "manager_frame.h"
#include <sstream>
#include "wallet.h"

ManagerFrame::ManagerFrame(const wxString& title, int userId) 
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)), userId(userId) {
    manager = new Manager();
    manager->loadFromId(userId);
    
    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    notebook = new wxNotebook(mainPanel, wxID_ANY);

    // Tab 1: View Info
    wxPanel* infoPanel = new wxPanel(notebook);
    wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
    infoOutputText = new wxTextCtrl(infoPanel, wxID_ANY, "", wxDefaultPosition, wxSize(550, 200), 
                                    wxTE_MULTILINE | wxTE_READONLY);
    infoSizer->Add(infoOutputText, 1, wxEXPAND | wxALL, 5);
    wxButton* viewInfoBtn = new wxButton(infoPanel, wxID_ANY, "Xem Thong Tin");
    infoSizer->Add(viewInfoBtn, 0, wxALL | wxALIGN_CENTER, 5);
    infoPanel->SetSizer(infoSizer);
    notebook->AddPage(infoPanel, "Xem Thong Tin");

    // Tab 2: View Customers (hiển thị dạng bảng)
    wxPanel* customersPanel = new wxPanel(notebook);
    wxBoxSizer* customersSizer = new wxBoxSizer(wxVERTICAL);
    customersOutputText = new wxTextCtrl(customersPanel, wxID_ANY, "", wxDefaultPosition, 
                                         wxSize(550, 200), wxTE_MULTILINE | wxTE_READONLY);
    customersSizer->Add(customersOutputText, 1, wxEXPAND | wxALL, 5);
    wxButton* viewCustomersBtn = new wxButton(customersPanel, wxID_ANY, "Xem Danh Sach Khach Hang");
    customersSizer->Add(viewCustomersBtn, 0, wxALL | wxALIGN_CENTER, 5);
    customersPanel->SetSizer(customersSizer);
    notebook->AddPage(customersPanel, "Xem Danh Sach");

    // Tab 3: Create User
    wxPanel* addCustomerPanel = new wxPanel(notebook);
    wxBoxSizer* addCustomerSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    inputSizer->Add(new wxStaticText(addCustomerPanel, wxID_ANY, "Username:"), 
                    0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    usernameInput = new wxTextCtrl(addCustomerPanel, wxID_ANY);
    inputSizer->Add(usernameInput, 1, wxALL | wxEXPAND, 5);
    inputSizer->Add(new wxStaticText(addCustomerPanel, wxID_ANY, "Mat Khau:"), 
                    0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    passwordInput = new wxTextCtrl(addCustomerPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    inputSizer->Add(passwordInput, 1, wxALL | wxEXPAND, 5);
    wxBoxSizer* dobAddrSizer = new wxBoxSizer(wxHORIZONTAL);
    dobAddrSizer->Add(new wxStaticText(addCustomerPanel, wxID_ANY, "Ngay Sinh:"), 
                      0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    dobInput = new wxTextCtrl(addCustomerPanel, wxID_ANY);
    dobAddrSizer->Add(dobInput, 1, wxALL | wxEXPAND, 5);
    dobAddrSizer->Add(new wxStaticText(addCustomerPanel, wxID_ANY, "Dia Chi:"), 
                      0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    addressInput = new wxTextCtrl(addCustomerPanel, wxID_ANY);
    dobAddrSizer->Add(addressInput, 1, wxALL | wxEXPAND, 5);
    wxButton* addCustomerBtn = new wxButton(addCustomerPanel, wxID_ANY, "Them Nguoi Dung");
    addCustomerSizer->Add(inputSizer, 0, wxEXPAND | wxALL, 5);
    addCustomerSizer->Add(dobAddrSizer, 0, wxEXPAND | wxALL, 5);
    addCustomerSizer->Add(addCustomerBtn, 0, wxALL | wxALIGN_CENTER, 5);
    addCustomerPanel->SetSizer(addCustomerSizer);
    notebook->AddPage(addCustomerPanel, "Tao Tai Khoan");

    // Tab 4: Add Points (dùng username)
    wxPanel* addPointsPanel = new wxPanel(notebook);
    wxBoxSizer* addPointsSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* pointsInputSizer = new wxBoxSizer(wxHORIZONTAL);
    pointsInputSizer->Add(new wxStaticText(addPointsPanel, wxID_ANY, "Username Khach Hang:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    customerIdInput = new wxTextCtrl(addPointsPanel, wxID_ANY);
    pointsInputSizer->Add(customerIdInput, 1, wxALL | wxEXPAND, 5);
    pointsInputSizer->Add(new wxStaticText(addPointsPanel, wxID_ANY, "Diem Them:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    pointsInput = new wxTextCtrl(addPointsPanel, wxID_ANY);
    pointsInputSizer->Add(pointsInput, 1, wxALL | wxEXPAND, 5);
    wxButton* addPointsBtn = new wxButton(addPointsPanel, wxID_ANY, "Them Diem");
    addPointsSizer->Add(pointsInputSizer, 0, wxEXPAND | wxALL, 5);
    addPointsSizer->Add(addPointsBtn, 0, wxALL | wxALIGN_CENTER, 5);
    addPointsPanel->SetSizer(addPointsSizer);
    notebook->AddPage(addPointsPanel, "Them Diem");

    // Tab 5: Update User Info (bỏ ID, không cần điền hết)
    wxPanel* updatePanel = new wxPanel(notebook);
    wxBoxSizer* updateSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* updateInputSizer = new wxBoxSizer(wxHORIZONTAL);
    updateInputSizer->Add(new wxStaticText(updatePanel, wxID_ANY, "Username:"), 
                          0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    updateIdInput = new wxTextCtrl(updatePanel, wxID_ANY); // Tái sử dụng cho username
    updateInputSizer->Add(updateIdInput, 1, wxALL | wxEXPAND, 5);
    wxBoxSizer* updateDobAddrSizer = new wxBoxSizer(wxHORIZONTAL);
    updateDobAddrSizer->Add(new wxStaticText(updatePanel, wxID_ANY, "Ngay Sinh:"), 
                            0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    updateDobInput = new wxTextCtrl(updatePanel, wxID_ANY);
    updateDobAddrSizer->Add(updateDobInput, 1, wxALL | wxEXPAND, 5);
    updateDobAddrSizer->Add(new wxStaticText(updatePanel, wxID_ANY, "Dia Chi:"), 
                            0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    updateAddressInput = new wxTextCtrl(updatePanel, wxID_ANY);
    updateDobAddrSizer->Add(updateAddressInput, 1, wxALL | wxEXPAND, 5);
    wxButton* updateBtn = new wxButton(updatePanel, wxID_ANY, "Cap Nhat");
    updateSizer->Add(updateInputSizer, 0, wxEXPAND | wxALL, 5);
    updateSizer->Add(updateDobAddrSizer, 0, wxEXPAND | wxALL, 5);
    updateSizer->Add(updateBtn, 0, wxALL | wxALIGN_CENTER, 5);
    updatePanel->SetSizer(updateSizer);
    notebook->AddPage(updatePanel, "Cap Nhat Thong Tin");

    // Tab 6: Transaction History
    wxPanel* historyPanel = new wxPanel(notebook);
    wxBoxSizer* historySizer = new wxBoxSizer(wxVERTICAL);
    historyText = new wxTextCtrl(historyPanel, wxID_ANY, "", wxDefaultPosition, wxSize(550, 200), 
                                 wxTE_MULTILINE | wxTE_READONLY);
    wxButton* viewHistoryBtn = new wxButton(historyPanel, wxID_ANY, "Xem Lich Su");
    historySizer->Add(historyText, 1, wxEXPAND | wxALL, 5);
    historySizer->Add(viewHistoryBtn, 0, wxALL | wxALIGN_CENTER, 5);
    historyPanel->SetSizer(historySizer);
    notebook->AddPage(historyPanel, "Lich Su Giao Dich");

    // Tab 7: Add Points to Total Wallet (tab mới)
    wxPanel* addTotalPointsPanel = new wxPanel(notebook);
    wxBoxSizer* addTotalPointsSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* totalPointsInputSizer = new wxBoxSizer(wxHORIZONTAL);
    totalPointsInputSizer->Add(new wxStaticText(addTotalPointsPanel, wxID_ANY, "Diem Them Vao Vi Tong:"), 
                               0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    totalPointsInput = new wxTextCtrl(addTotalPointsPanel, wxID_ANY);
    totalPointsInputSizer->Add(totalPointsInput, 1, wxALL | wxEXPAND, 5);
    wxButton* addTotalPointsBtn = new wxButton(addTotalPointsPanel, wxID_ANY, "Them Diem Vao Vi Tong");
    addTotalPointsSizer->Add(totalPointsInputSizer, 0, wxEXPAND | wxALL, 5);
    addTotalPointsSizer->Add(addTotalPointsBtn, 0, wxALL | wxALIGN_CENTER, 5);
    addTotalPointsPanel->SetSizer(addTotalPointsSizer);
    notebook->AddPage(addTotalPointsPanel, "Them Diem Vi Tong");

    mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 5);

    logoutBtn = new wxButton(mainPanel, wxID_ANY, "Dang Xuat");
    mainSizer->Add(logoutBtn, 0, wxALL | wxALIGN_CENTER, 5);

    mainPanel->SetSizer(mainSizer);

    viewInfoBtn->Bind(wxEVT_BUTTON, &ManagerFrame::OnViewInfo, this);
    viewCustomersBtn->Bind(wxEVT_BUTTON, &ManagerFrame::OnViewCustomers, this);
    addCustomerBtn->Bind(wxEVT_BUTTON, &ManagerFrame::OnAddCustomer, this);
    addPointsBtn->Bind(wxEVT_BUTTON, &ManagerFrame::OnAddPoints, this);
    updateBtn->Bind(wxEVT_BUTTON, &ManagerFrame::OnUpdateUserInfo, this);
    viewHistoryBtn->Bind(wxEVT_BUTTON, &ManagerFrame::OnViewHistory, this);
    addTotalPointsBtn->Bind(wxEVT_BUTTON, &ManagerFrame::OnAddTotalPoints, this);
    logoutBtn->Bind(wxEVT_BUTTON, &ManagerFrame::OnLogout, this);
    Bind(wxEVT_CLOSE_WINDOW, &ManagerFrame::OnClose, this);

    Centre();
}

ManagerFrame::~ManagerFrame() {
    delete manager;
}

void ManagerFrame::OnViewInfo(wxCommandEvent& event) {
    if (manager->getId() == 0) {
        wxMessageBox("Khong the tai thong tin tai khoan!", "Loi", wxOK | wxICON_ERROR);
        OnLogout(event);
        return;
    }
    infoOutputText->SetValue(manager->getPersonalInfo());
}

void ManagerFrame::OnViewCustomers(wxCommandEvent& event) {
    std::ifstream file("E:/tai_lieu/c++/taikhoan.txt");
    std::stringstream ss;
    ss << "Username\tNgay Sinh\tDia Chi\tTong Diem\n";
    ss << "------------------------------------------------\n";
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos1 = line.find("|");
            int type = std::stoi(line.substr(pos1 + 1, line.find("|", pos1 + 1) - pos1 - 1));
            if (type == 0) { // Chỉ lấy Customer
                size_t pos2 = line.find("|", pos1 + 1);
                size_t pos3 = line.find("|", pos2 + 1);
                size_t pos4 = line.find("|", pos3 + 1);
                size_t pos5 = line.find("|", pos4 + 1);
                size_t pos6 = line.find("|", pos5 + 1);
                size_t pos7 = line.rfind("|");
                std::string username = line.substr(pos2 + 1, pos3 - pos2 - 1);
                std::string dob = line.substr(pos5 + 1, pos6 - pos5 - 1);
                std::string address = line.substr(pos6 + 1, pos7 - pos6 - 1);
                int walletId = std::stoi(line.substr(pos7 + 1));

                // Lấy tổng điểm từ wallets.txt
                Wallet* wallet = Wallet::loadFromFile(walletId);
                int balance = wallet ? wallet->getBalance() : 0;
                delete wallet;

                ss << username << "\t" << dob << "\t" << address << "\t" << balance << "\n";
            }
        }
        file.close();
    }
    customersOutputText->SetValue(ss.str());
}

void ManagerFrame::OnAddCustomer(wxCommandEvent& event) {
    std::string username = usernameInput->GetValue().ToStdString();
    std::string password = passwordInput->GetValue().ToStdString();
    std::string dob = dobInput->GetValue().ToStdString();
    std::string address = addressInput->GetValue().ToStdString();
    if (username.empty() || password.empty() || dob.empty() || address.empty()) {
        wxMessageBox("Vui long nhap day du thong tin!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    if (manager->createUser(username, password, "", dob, address)) {
        wxMessageBox("Them nguoi dung thanh cong!", "Thanh cong", wxOK | wxICON_INFORMATION);
        usernameInput->Clear();
        passwordInput->Clear();
        dobInput->Clear();
        addressInput->Clear();
        notebook->SetSelection(1);
        OnViewCustomers(event);
    } else {
        wxMessageBox("Them that bai! Username co the da ton tai.", "Loi", wxOK | wxICON_ERROR);
    }
}

void ManagerFrame::OnAddPoints(wxCommandEvent& event) {
    std::string username = customerIdInput->GetValue().ToStdString();
    long points;
    if (username.empty() || !pointsInput->GetValue().ToLong(&points) || points <= 0) {
        wxMessageBox("Vui long nhap username va so diem hop le!", "Loi", wxOK | wxICON_ERROR);
        return;
    }

    // Tìm walletId từ username
    std::ifstream file("E:/tai_lieu/c++/taikhoan.txt");
    int walletId = -1;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos2 = line.find("|", line.find("|") + 1);
            size_t pos3 = line.find("|", pos2 + 1);
            std::string fileUsername = line.substr(pos2 + 1, pos3 - pos2 - 1);
            if (fileUsername == username) {
                walletId = std::stoi(line.substr(line.rfind("|") + 1));
                break;
            }
        }
        file.close();
    }

    if (walletId == -1) {
        wxMessageBox("Khong tim thay khach hang voi username nay!", "Loi", wxOK | wxICON_ERROR);
        return;
    }

    if (manager->addPointsToUser(walletId, (int)points)) {
        wxMessageBox("Them diem thanh cong!", "Thanh cong", wxOK | wxICON_INFORMATION);
        customerIdInput->Clear();
        pointsInput->Clear();
        notebook->SetSelection(5);
        OnViewHistory(event);
    } else {
        wxMessageBox("Them diem that bai! Kiem tra so diem trong vi tong.", "Loi", wxOK | wxICON_ERROR);
    }
}

void ManagerFrame::OnUpdateUserInfo(wxCommandEvent& event) {
    std::string username = updateIdInput->GetValue().ToStdString(); // Dùng username thay vì ID
    std::string dob = updateDobInput->GetValue().ToStdString();
    std::string address = updateAddressInput->GetValue().ToStdString();
    if (username.empty()) {
        wxMessageBox("Vui long nhap username!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    // Tìm userId từ username
    std::ifstream file("E:/tai_lieu/c++/taikhoan.txt");
    int userId = -1;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos2 = line.find("|", line.find("|") + 1);
            size_t pos3 = line.find("|", pos2 + 1);
            std::string fileUsername = line.substr(pos2 + 1, pos3 - pos2 - 1);
            if (fileUsername == username) {
                userId = std::stoi(line.substr(0, pos2));
                break;
            }
        }
        file.close();
    }

    if (userId == -1) {
        wxMessageBox("Khong tim thay khach hang voi username nay!", "Loi", wxOK | wxICON_ERROR);
        return;
    }

    if (manager->updateUserInfo(userId, "", dob, address, this)) {
        wxMessageBox("Cap nhat thong tin thanh cong!", "Thanh cong", wxOK | wxICON_INFORMATION);
        updateIdInput->Clear();
        updateDobInput->Clear();
        updateAddressInput->Clear();
        notebook->SetSelection(1);
        OnViewCustomers(event);
    } else {
        wxMessageBox("Cap nhat that bai!", "Loi", wxOK | wxICON_ERROR);
    }
}

void ManagerFrame::OnViewHistory(wxCommandEvent& event) {
    std::string history = manager->getTransactionHistory();
    if (history.empty()) {
        historyText->SetValue("Khong co giao dich nao.");
    } else {
        historyText->SetValue(history);
    }
}

void ManagerFrame::OnAddTotalPoints(wxCommandEvent& event) {
    long points;
    if (!totalPointsInput->GetValue().ToLong(&points) || points <= 0) {
        wxMessageBox("Vui long nhap so diem hop le!", "Loi", wxOK | wxICON_ERROR);
        return;
    }

    Wallet* totalWallet = Wallet::loadFromFile(0); // Ví tổng
    if (!totalWallet) {
        wxMessageBox("Khong the tai vi tong!", "Loi", wxOK | wxICON_ERROR);
        return;
    }

    totalWallet->addPoints((int)points);
    delete totalWallet;

    wxMessageBox("Them diem vao vi tong thanh cong!", "Thanh cong", wxOK | wxICON_INFORMATION);
    totalPointsInput->Clear();
}

void ManagerFrame::OnLogout(wxCommandEvent& event) {
    if (manager) {
        delete manager;
        manager = nullptr;
    }
    LoginFrame* loginFrame = new LoginFrame("Dang Nhap");
    loginFrame->Show(true);
    this->Hide();
}

void ManagerFrame::OnClose(wxCloseEvent& event) {
    if (manager) {
        delete manager;
        manager = nullptr;
    }
    LoginFrame* loginFrame = new LoginFrame("Dang Nhap");
    loginFrame->Show(true);
    Destroy();
}
