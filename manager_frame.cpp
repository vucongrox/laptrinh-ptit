#include "manager_frame.h"
#include <sstream>
#include "wallet.h"

ManagerFrame::ManagerFrame(const wxString& title, int userId) 
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)), userId(userId) {
    manager = new Manager();
    manager->loadFromId(userId);
    
    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    notebook = new wxNotebook(mainPanel, wxID_ANY);

    // Tab 1: View Info
    wxPanel* infoPanel = new wxPanel(notebook);
    wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
    infoOutputText = new wxTextCtrl(infoPanel, wxID_ANY, "", wxDefaultPosition, wxSize(750, 300), 
                                    wxTE_MULTILINE | wxTE_READONLY);
    infoOutputText->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    infoSizer->Add(infoOutputText, 1, wxEXPAND | wxALL, 10);
    wxButton* viewInfoBtn = new wxButton(infoPanel, wxID_ANY, "Xem Thong Tin");
    viewInfoBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    infoSizer->Add(viewInfoBtn, 0, wxALL | wxALIGN_CENTER, 10);
    infoPanel->SetSizer(infoSizer);
    notebook->AddPage(infoPanel, "Thong Tin");

    // Tab 2: View Customers (hiển thị dạng bảng)
    wxPanel* customersPanel = new wxPanel(notebook);
    wxBoxSizer* customersSizer = new wxBoxSizer(wxVERTICAL);
    customersOutputText = new wxTextCtrl(customersPanel, wxID_ANY, "", wxDefaultPosition, 
                                         wxSize(750, 300), wxTE_MULTILINE | wxTE_READONLY);
    customersOutputText->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    customersSizer->Add(customersOutputText, 1, wxEXPAND | wxALL, 10);
    wxButton* viewCustomersBtn = new wxButton(customersPanel, wxID_ANY, "Xem Danh Sach Khach Hang");
    viewCustomersBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    customersSizer->Add(viewCustomersBtn, 0, wxALL | wxALIGN_CENTER, 10);
    customersPanel->SetSizer(customersSizer);
    notebook->AddPage(customersPanel, "Danh Sach Khach Hang");

    // Tab 3: Create User
    wxPanel* addCustomerPanel = new wxPanel(notebook);
    wxBoxSizer* addCustomerSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* usernameLabel = new wxStaticText(addCustomerPanel, wxID_ANY, "Username:");
    usernameLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    inputSizer->Add(usernameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    usernameInput = new wxTextCtrl(addCustomerPanel, wxID_ANY);
    usernameInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    inputSizer->Add(usernameInput, 1, wxALL | wxEXPAND, 10);
    wxStaticText* passwordLabel = new wxStaticText(addCustomerPanel, wxID_ANY, "Mat Khau:");
    passwordLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    inputSizer->Add(passwordLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    passwordInput = new wxTextCtrl(addCustomerPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    passwordInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    inputSizer->Add(passwordInput, 1, wxALL | wxEXPAND, 10);
    wxBoxSizer* nameDobSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* nameLabel = new wxStaticText(addCustomerPanel, wxID_ANY, "Ten:");
    nameLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    nameDobSizer->Add(nameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    nameInput = new wxTextCtrl(addCustomerPanel, wxID_ANY);
    nameInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    nameDobSizer->Add(nameInput, 1, wxALL | wxEXPAND, 10);
    wxStaticText* dobLabel = new wxStaticText(addCustomerPanel, wxID_ANY, "Ngay Sinh:");
    dobLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    nameDobSizer->Add(dobLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    dobInput = new wxTextCtrl(addCustomerPanel, wxID_ANY);
    dobInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    nameDobSizer->Add(dobInput, 1, wxALL | wxEXPAND, 10);
    wxBoxSizer* addrSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* addressLabel = new wxStaticText(addCustomerPanel, wxID_ANY, "Dia Chi:");
    addressLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    addrSizer->Add(addressLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    addressInput = new wxTextCtrl(addCustomerPanel, wxID_ANY);
    addressInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    addrSizer->Add(addressInput, 1, wxALL | wxEXPAND, 10);
    wxButton* addCustomerBtn = new wxButton(addCustomerPanel, wxID_ANY, "Them Nguoi Dung");
    addCustomerBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    addCustomerSizer->Add(inputSizer, 0, wxEXPAND | wxALL, 10);
    addCustomerSizer->Add(nameDobSizer, 0, wxEXPAND | wxALL, 10);
    addCustomerSizer->Add(addrSizer, 0, wxEXPAND | wxALL, 10);
    addCustomerSizer->Add(addCustomerBtn, 0, wxALL | wxALIGN_CENTER, 10);
    addCustomerPanel->SetSizer(addCustomerSizer);
    notebook->AddPage(addCustomerPanel, "Tao Tai Khoan");

    // Tab 4: Update User Info (bỏ ID, không cần điền hết)
    wxPanel* updatePanel = new wxPanel(notebook);
    wxBoxSizer* updateSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* updateInputSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* updateUsernameLabel = new wxStaticText(updatePanel, wxID_ANY, "Username:");
    updateUsernameLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    updateInputSizer->Add(updateUsernameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    updateIdInput = new wxTextCtrl(updatePanel, wxID_ANY);
    updateIdInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    updateInputSizer->Add(updateIdInput, 1, wxALL | wxEXPAND, 10);
    wxBoxSizer* updateNameDobSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* updateNameLabel = new wxStaticText(updatePanel, wxID_ANY, "Ten:");
    updateNameLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    updateNameDobSizer->Add(updateNameLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    updateNameInput = new wxTextCtrl(updatePanel, wxID_ANY);
    updateNameInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    updateNameDobSizer->Add(updateNameInput, 1, wxALL | wxEXPAND, 10);
    wxStaticText* updateDobLabel = new wxStaticText(updatePanel, wxID_ANY, "Ngay Sinh:");
    updateDobLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    updateNameDobSizer->Add(updateDobLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    updateDobInput = new wxTextCtrl(updatePanel, wxID_ANY);
    updateDobInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    updateNameDobSizer->Add(updateDobInput, 1, wxALL | wxEXPAND, 10);
    wxBoxSizer* updateAddrSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* updateAddressLabel = new wxStaticText(updatePanel, wxID_ANY, "Dia Chi:");
    updateAddressLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    updateAddrSizer->Add(updateAddressLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    updateAddressInput = new wxTextCtrl(updatePanel, wxID_ANY);
    updateAddressInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    updateAddrSizer->Add(updateAddressInput, 1, wxALL | wxEXPAND, 10);
    wxButton* updateBtn = new wxButton(updatePanel, wxID_ANY, "Cap Nhat");
    updateBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    updateSizer->Add(updateInputSizer, 0, wxEXPAND | wxALL, 10);
    updateSizer->Add(updateNameDobSizer, 0, wxEXPAND | wxALL, 10);
    updateSizer->Add(updateAddrSizer, 0, wxEXPAND | wxALL, 10);
    updateSizer->Add(updateBtn, 0, wxALL | wxALIGN_CENTER, 10);
    updatePanel->SetSizer(updateSizer);
    notebook->AddPage(updatePanel, "Cap Nhat Thong Tin");
        
    // Tab 5: Add Points (dùng username)
    wxPanel* addPointsPanel = new wxPanel(notebook);
    wxBoxSizer* addPointsSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* pointsInputSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* customerIdLabel = new wxStaticText(addPointsPanel, wxID_ANY, "Username Khach Hang:");
    customerIdLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    pointsInputSizer->Add(customerIdLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    customerIdInput = new wxTextCtrl(addPointsPanel, wxID_ANY);
    customerIdInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    pointsInputSizer->Add(customerIdInput, 1, wxALL | wxEXPAND, 10);
    wxStaticText* pointsLabel = new wxStaticText(addPointsPanel, wxID_ANY, "Diem Them:");
    pointsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    pointsInputSizer->Add(pointsLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    pointsInput = new wxTextCtrl(addPointsPanel, wxID_ANY);
    pointsInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    pointsInputSizer->Add(pointsInput, 1, wxALL | wxEXPAND, 10);
    wxButton* addPointsBtn = new wxButton(addPointsPanel, wxID_ANY, "Them Diem");
    addPointsBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    addPointsSizer->Add(pointsInputSizer, 0, wxEXPAND | wxALL, 10);
    addPointsSizer->Add(addPointsBtn, 0, wxALL | wxALIGN_CENTER, 10);
    addPointsPanel->SetSizer(addPointsSizer);
    notebook->AddPage(addPointsPanel, "Them Diem");
        
    // Tab 6: Transaction History
    wxPanel* historyPanel = new wxPanel(notebook);
    wxBoxSizer* historySizer = new wxBoxSizer(wxVERTICAL);
    historyText = new wxTextCtrl(historyPanel, wxID_ANY, "", wxDefaultPosition, wxSize(750, 300), 
                                 wxTE_MULTILINE | wxTE_READONLY);
    historyText->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    wxButton* viewHistoryBtn = new wxButton(historyPanel, wxID_ANY, "Xem Lich Su");
    viewHistoryBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    historySizer->Add(historyText, 1, wxEXPAND | wxALL, 10);
    historySizer->Add(viewHistoryBtn, 0, wxALL | wxALIGN_CENTER, 10);
    historyPanel->SetSizer(historySizer);
    notebook->AddPage(historyPanel, "Lich Su Giao Dich");

    // Tab 7: Add Points to Total Wallet
    wxPanel* addTotalPointsPanel = new wxPanel(notebook);
    wxBoxSizer* addTotalPointsSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* totalPointsInputSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* totalPointsLabel = new wxStaticText(addTotalPointsPanel, wxID_ANY, "Diem Them Vao Vi Tong:");
    totalPointsLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    totalPointsInputSizer->Add(totalPointsLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    totalPointsInput = new wxTextCtrl(addTotalPointsPanel, wxID_ANY);
    totalPointsInput->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    totalPointsInputSizer->Add(totalPointsInput, 1, wxALL | wxEXPAND, 10);
    wxButton* addTotalPointsBtn = new wxButton(addTotalPointsPanel, wxID_ANY, "Them Diem Vao Vi Tong");
    addTotalPointsBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    addTotalPointsSizer->Add(totalPointsInputSizer, 0, wxEXPAND | wxALL, 10);
    addTotalPointsSizer->Add(addTotalPointsBtn, 0, wxALL | wxALIGN_CENTER, 10);
    addTotalPointsPanel->SetSizer(addTotalPointsSizer);
    notebook->AddPage(addTotalPointsPanel, "Them Diem Vi Tong");

    mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 10);

    logoutBtn = new wxButton(mainPanel, wxID_ANY, "Dang Xuat");
    logoutBtn->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mainSizer->Add(logoutBtn, 0, wxALL | wxALIGN_CENTER, 10);

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
    std::string name = nameInput->GetValue().ToStdString();
    std::string dob = dobInput->GetValue().ToStdString();
    std::string address = addressInput->GetValue().ToStdString();
    if (username.empty() || password.empty() || name.empty() || dob.empty() || address.empty()) {
        wxMessageBox("Vui long nhap day du thong tin!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    if (manager->createUser(username, password, name, dob, address)) {
        wxMessageBox("Them nguoi dung thanh cong!", "Thanh cong", wxOK | wxICON_INFORMATION);
        usernameInput->Clear();
        passwordInput->Clear();
        nameInput->Clear();
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
    if (!file.is_open()) {
        wxMessageBox("Khong the mo file taikhoan.txt!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        try {
            size_t pos1 = line.find("|");
            if (pos1 == std::string::npos) continue;
            size_t pos2 = line.find("|", pos1 + 1);
            if (pos2 == std::string::npos) continue;
            size_t pos3 = line.find("|", pos2 + 1);
            if (pos3 == std::string::npos) continue;
            std::string fileUsername = line.substr(pos2 + 1, pos3 - pos2 - 1);
            if (fileUsername == username) {
                size_t pos7 = line.rfind("|");
                if (pos7 == std::string::npos) continue;
                walletId = std::stoi(line.substr(pos7 + 1));
                break;
            }
        } catch (const std::exception& e) {
            continue; // Bỏ qua dòng lỗi
        }
    }
    file.close();

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
    std::string username = updateIdInput->GetValue().ToStdString();
    std::string name = updateNameInput->GetValue().ToStdString();
    std::string dob = updateDobInput->GetValue().ToStdString();
    std::string address = updateAddressInput->GetValue().ToStdString();
    if (username.empty()) {
        wxMessageBox("Vui long nhap username!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    // Tìm userId từ username
    std::ifstream file("E:/tai_lieu/c++/taikhoan.txt");
    int userId = -1;
    if (!file.is_open()) {
        wxMessageBox("Khong the mo file taikhoan.txt!", "Loi", wxOK | wxICON_ERROR);
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        try {
            size_t pos1 = line.find("|");
            if (pos1 == std::string::npos) continue;
            size_t pos2 = line.find("|", pos1 + 1);
            if (pos2 == std::string::npos) continue;
            size_t pos3 = line.find("|", pos2 + 1);
            if (pos3 == std::string::npos) continue;
            std::string fileUsername = line.substr(pos2 + 1, pos3 - pos2 - 1);
            if (fileUsername == username) {
                userId = std::stoi(line.substr(0, pos1));
                break;
            }
        } catch (const std::exception& e) {
            continue; // Bỏ qua dòng lỗi
        }
    }
    file.close();

    if (userId == -1) {
        wxMessageBox("Khong tim thay khach hang voi username nay!", "Loi", wxOK | wxICON_ERROR);
        return;
    }

    if (manager->updateUserInfo(userId, name, dob, address, this)) {
        wxMessageBox("Cap nhat thong tin thanh cong!", "Thanh cong", wxOK | wxICON_INFORMATION);
        updateIdInput->Clear();
        updateNameInput->Clear();
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

    Wallet* totalWallet = Wallet::loadFromFile(0);
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
