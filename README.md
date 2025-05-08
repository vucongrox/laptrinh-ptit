# Hệ thống đăng nhập và đăng ký tài khoản và quản lý ví điểm thưởng




## Mô tả dự án
**Hệ thống Quản lý Tài khoản và Ví Điểm thưởng** là một giải pháp phần mềm toàn diện được thiết kế để cung cấp các chức năng quản lý tài khoản người dùng và hệ thống giao dịch điểm thưởng một cách an toàn, hiệu quả. Dự án tập trung vào ba trụ cột chính:

- **Quản lý tài khoản**: Hỗ trợ đăng ký, đăng nhập, và cập nhật thông tin người dùng với cơ chế bảo mật tiên tiến, bao gồm xác thực bằng mật khẩu băm (hash) và OTP (One-Time Password).
- **Hệ thống ví điểm thưởng**: Cho phép người dùng thực hiện các giao dịch chuyển điểm giữa các ví, theo dõi số dư, và xem lịch sử giao dịch với tính toàn vẹn dữ liệu được đảm bảo.
- **Phân quyền linh hoạt**: Phân tách rõ ràng giữa người dùng thông thường (quản lý thông tin cá nhân) và người dùng quản lý (thêm tài khoản, chỉnh sửa thông tin, giám sát hệ thống).
## Các thành viên
Thành viên          | Công việc được giao
--------------------|-------------------------------------------------------------------------------------
congvu             | Xây dựng nền tảng cơ bản (lớp Customer, User, Manager); phát triển hàm main; triển khai và sửa lỗi các chức năng người dùng (getList, regis, loadFromID); sửa lỗi chức năng giao dịch (transaction).
truong-ngo-edu-0912| Thiết kế giao diện đăng nhập; xây dựng logic đăng nhập; phát triển các chức năng người dùng (updateInfor, genPass); triển khai hệ thống ví (wallet); thêm quản lý ví (WalletManager) và giao diện quản lý ví.
K24dtcn380         | Thiết kế giao diện khách hàng (Customer); phát triển các chức năng khách hàng; triển khai hệ thống ví (wallet); thêm ví khách hàng (WalletCustomer); viết mã cho chức năng giao dịch (transaction).
namnh1988          | Thiết kế giao diện quản lý (Manager); phát triển các chức năng quản lý; triển khai và sửa lỗi các chức năng người dùng (getList, regis, loadFromID); xây dựng cơ chế xác thực OTP.

---

## Tính năng chính

### 1. Quản lý tài khoản
- **Đăng ký tài khoản**: Người dùng có thể đăng ký tài khoản mới với thông tin gồm tên, ngày sinh, địa chỉ, tên đăng nhập, và mật khẩu.
- **Đăng nhập**: Xác thực người dùng thông qua tên đăng nhập và mật khẩu đã băm.
- **Cập nhật thông tin**: Người dùng thông thường có thể chỉnh sửa thông tin cá nhân (tên, ngày sinh, địa chỉ). Quản lý có thể chỉnh sửa thông tin của bất kỳ người dùng nào.

### 2. Quản lý ví và giao dịch
- **Ví người dùng**: Mỗi người dùng có một ví với số dư điểm, được lưu trong `wallets.txt`.
- **Chuyển điểm**: Người dùng thông thường có thể chuyển điểm từ ví của mình sang ví của người dùng khác.
- **Thêm điểm**: Quản lý có thể thêm điểm vào ví của người dùng hoặc ví tổng (walletId = 0).
- **Lịch sử giao dịch**: Người dùng thông thường có thể xem lịch sử giao dịch của mình, quản lý có thể xem toàn bộ lịch sử giao dịch.

### 3. Bảo mật và xác thực

#### Mã hóa mật khẩu
- Mật khẩu của người dùng được băm trước khi lưu trữ để đảm bảo an toàn.
- Sử dụng hàm băm (SHA-256) để mã hóa mật khẩu.
- Mật khẩu băm được lưu trong tệp `taikhoan.txt`.
  - Ví dụ: Mật khẩu "password123" được băm thành "2da1eed431f8991b".

#### Xác thực OTP
- **Sinh mã OTP**:
  - Sử dụng thuật toán **TOTP (Time-based One-Time Password)** để tạo mã OTP cho các thao tác quan trọng như cập nhật thông tin và giao dịch chuyển điểm.
  - **Thuật toán TOTP**:
    - TOTP là một biến thể của HOTP (HMAC-based One-Time Password), dựa trên thời gian thay vì số đếm.
    - Công thức:  
      ```
      TOTP = HMAC-SHA1(secret, T) mod 10^digits
      ```
      Trong đó:
      - `secret`: Khóa bí mật cố định ("MYAPPSECRET12345").
      - `T`: Số bước thời gian, tính bằng cách chia thời gian hiện tại (Unix timestamp) cho khoảng thời gian bước (period, mặc định 30 giây).
      - `digits`: Số chữ số của mã OTP (mặc định 6 chữ số).
    - Sau khi tính HMAC-SHA1, giá trị băm được rút gọn bằng kỹ thuật **Dynamic Truncation** (lấy 4 byte từ vị trí offset và chuyển thành số nguyên), rồi lấy modulo để tạo mã OTP.
  - **Cách mã hoạt động**:
    - Lưu thời gian tạo OTP để kiểm tra thời gian hết hạn:  
      ```cpp
      otpGeneratedTime = time(nullptr);
      ```
    - Lấy thời gian hiện tại và tính số bước thời gian `T`:  
      ```cpp
      uint64_t time_step = static_cast<uint64_t>(otpGeneratedTime) / period;
      ```
    - Chuyển `time_step` thành dạng binary (big-endian) để làm đầu vào cho HMAC-SHA1:  
      ```cpp
      std::vector<uint8_t> time_bytes(8);
      for (int i = 7; i >= 0; --i) {
          time_bytes[i] = static_cast<uint8_t>(time_step & 0xFF);
          time_step >>= 8;
      }
      ```
    - Tính HMAC-SHA1 với khóa bí mật và `time_bytes`:  
      ```cpp
      std::vector<uint8_t> hmac_result = hmac_sha1(secret, time_bytes);
      ```
    - Áp dụng Dynamic Truncation để rút gọn giá trị băm:  
      - Lấy offset từ byte cuối của giá trị băm:  
        ```cpp
        int offset = hmac_result[hmac_result.size() - 1] & 0x0F;
        ```
      - Lấy 4 byte từ vị trí offset và chuyển thành số nguyên 31-bit:  
        ```cpp
        uint32_t binary_code = 
            ((hmac_result[offset] & 0x7F) << 24) |
            ((hmac_result[offset + 1] & 0xFF) << 16) |
            ((hmac_result[offset + 2] & 0xFF) << 8) |
            (hmac_result[offset + 3] & 0xFF);
        ```
    - Rút gọn thành mã 6 chữ số:  
      ```cpp
      binary_code = binary_code % static_cast<uint32_t>(std::pow(10, digits));
      ```
    - Định dạng mã OTP với số 0 đằng trước nếu cần:  
      ```cpp
      std::string otp = std::to_string(binary_code);
      while (otp.length() < digits) {
          otp = "0" + otp;
      }
      ```
  - Mã OTP có thời gian hết hạn là 30 giây.
- **Hiển thị OTP**:
  - Mã OTP được hiển thị trên giao diện thông qua hộp thoại `wxMessageBox` (giả lập gửi OTP cho người dùng).
- **Kiểm tra OTP**:
  - Người dùng nhập mã OTP vào hộp thoại `wxTextEntryDialog`.
  - Hệ thống kiểm tra tính hợp lệ của mã OTP:
    - So sánh mã OTP nhập vào với mã đã tạo.
    - Kiểm tra thời gian hết hạn (30 giây kể từ khi mã được tạo, dựa trên biến `otpGeneratedTime`).
  - Nếu OTP không khớp hoặc đã hết hạn, thao tác (cập nhật thông tin, giao dịch) sẽ bị hủy và thông báo lỗi được hiển thị.

#### Phân quyền người dùng
- **Người dùng thông thường (Customer)**:
  - Truy cập và chỉnh sửa thông tin cá nhân (tên, ngày sinh, địa chỉ).
  - Đổi mật khẩu cá nhân.
  - Chuyển điểm giữa các ví và xem lịch sử giao dịch của bản thân.
  - Tìm kiếm thông tin của người dùng khác qua tên đăng nhập.
- **Người dùng quản lý (Manager)**:
  - Tạo tài khoản mới cho người dùng.
  - Chỉnh sửa thông tin của bất kỳ người dùng nào.
  - Xem danh sách tất cả người dùng (bao gồm tên đăng nhập, ngày sinh, địa chỉ, và số dư ví).
  - Thêm điểm vào ví của người dùng hoặc ví tổng.
  - Xem toàn bộ lịch sử giao dịch của hệ thống.

### 4. Lưu trữ và sao lưu dữ liệu

#### Lưu trữ dữ liệu
- **Tệp `taikhoan.txt`**:
  - Lưu thông tin tài khoản người dùng.
  - Định dạng: `id|accountType|username|hashedPassword|name|dob|address|walletId`.
  - Ví dụ:
    ```
    1|1|admin|2da1eed431f8991b|Admin|01/01/1990|Ha Noi|1001
    2|0|khach1|942b0c273781c4d2|Khach Mot|15/05/1995|Ho Chi Minh|1002
    ```
- **Tệp `wallets.txt`**:
  - Lưu thông tin ví và số dư.
  - Định dạng: `walletId|balance`.
  - Ví dụ:
    ```
    1001|0
    1002|100
    ```
- **Tệp `transactions.txt`**:
  - Lưu lịch sử giao dịch.
  - Định dạng: `senderWalletId|receiverWalletId|points|timestamp|status`.
  - Ví dụ:
    ```
    0|1002|100|Fri Apr 26 12:34:56 2025|success
    ```

#### Sao lưu và phục hồi
- **Sao lưu tự động**:
  - Tạo bản sao lưu cho `taikhoan.txt`, `transactions.txt`, và `wallets.txt` sau mỗi thao tác cập nhật dữ liệu (đăng ký, chỉnh sửa thông tin, giao dịch).
  - Sao lưu định kỳ mỗi 6 phút (để kiểm tra, có thể điều chỉnh lại sau).
  - Bản sao lưu được lưu vào thư mục `E:/tai_lieu/c++/backups` với nhãn thời gian (ví dụ: `taikhoan_backup_1696112400.txt`).
  - Giữ tối đa 7 bản sao gần nhất cho mỗi loại tệp để tiết kiệm không gian.

---


## Yêu cầu hệ thống
- **Hệ điều hành**: Windows (đường dẫn sử dụng `E:/tai_lieu/c++`).
- **Thư viện**:
  - wxWidgets: Để xây dựng giao diện người dùng.
  - OpenSSL: Để tính toán mã OTP (TOTP với HMAC-SHA1).
- **Trình biên dịch**: Hỗ trợ C++11 trở lên.
- **Phụ thuộc**:
  - Thư viện `filesystem` (C++17) để quản lý tệp sao lưu.

---
## Hướng dẫn cài đặt
### 1. Tải chương trình
Để tải mã nguồn của dự án từ kho GitHub, làm theo một trong các cách sau:

#### Clone kho mã nguồn bằng Git
- Cài đặt Git từ [https://git-scm.com/](https://git-scm.com/) nếu chưa có.
- Mở terminal (Command Prompt trên Windows, Terminal trên Linux/macOS).
- Chạy lệnh sau để tải kho:

  ```bash
  git clone https://github.com/vucongrox/laptrinh-ptit.git

- chạy chương trình bằng [embarcadero C++/](https://www.embarcadero.com/free-tools/dev-cpp)
- file mã nguồn:
    - main.cpp: Điểm vào chương trình, khởi tạo ứng dụng.
    - main.h: Header chứa các định nghĩa chung.
    - customer.cpp: Xử lý logic liên quan đến khách hàng.
    - customer.h: Header định nghĩa lớp khách hàng.
    - customer_frame.cpp: Giao diện khách hàng, sử dụng wxWidgets.
    - customer_frame.h: Header cho giao diện khách hàng.
    - login_frame.cpp: Giao diện đăng nhập.
    - login_frame.h: Header cho giao diện đăng nhập.
    - manager.cpp: Xử lý logic quản lý, bao gồm thêm điểm.
    - manager.h: Header định nghĩa lớp quản lý.
    - manager_frame.cpp: Giao diện quản lý, sử dụng wxWidgets.
    - manager_frame.h: Header cho giao diện quản lý.
    - transaction.cpp: Xử lý giao dịch ví điểm thưởng.
    - transaction.h: Header định nghĩa lớp giao dịch.
    - user.cpp: Xử lý logic tài khoản người dùng (đăng ký, đăng nhập, cập nhật).
    - user.h: Header định nghĩa lớp người dùng.
    - wallet.cpp: Quản lý ví điểm thưởng.
    - wallet.h: Header định nghĩa lớp ví.
## 2. Thư viện: 
    - **wxWidgets**: Bắt buộc, vì các tệp như `customer_frame.cpp`, `manager_frame.cpp` cho thấy dự án dùng giao diện wxWidgets.Tải từ https://www.wxwidgets.org/downloads/, chọn phiên bản cho Windows.
    - **OpenSSL**: Bắt buộc, vì dự án có thể băm mật khẩu.
    - **C++ Standard Library**: Bao gồm các thành phần chuẩn như `<filesystem>`, `<random>` (hỗ trợ C++17).



##  Hướng dẫn chạy chương trình

###  Bước 1: Thêm mã nguồn vào Project

1. Mở **Embarcadero Dev-C++**
2. Vào menu `File` → `New` → `Project` → chọn **Empty Project**
3. Đặt tên và lưu project vào thư mục chứa mã nguồn
4. Thêm các tệp `.cpp` và `.h` vào project:
   - Vào menu `Project` → `Add to Project...`
   - Chọn tất cả các file trong thư mục (giữ Ctrl để chọn nhiều file)

---

### ⚙ Bước 2: Cấu hình thư viện và biên dịch

Vào `Project` → `Project Options...` để thiết lập các cấu hình sau:

---

## Hướng dẫn cài đặt
1. **Cài đặt thư viện**:
   - **wxWidgets**:
     - Tải và cài đặt wxWidgets từ trang chính thức (https://www.wxwidgets.org/downloads/).
     - Đảm bảo bạn đã biên dịch wxWidgets theo hướng dẫn trên trang web (ví dụ: dùng MinGW hoặc MSVC).
   - **OpenSSL**:
     - Tải OpenSSL từ trang chính thức hoặc kho lưu trữ (https://www.openssl.org/source/).
     - Biên dịch OpenSSL với MinGW:
       - Giải nén mã nguồn OpenSSL (ví dụ: vào thư mục `E:\openssl-master`).
       - Mở terminal MinGW, di chuyển vào thư mục OpenSSL và chạy:
         ```
         ./config --prefix=E:/openssl-master/openssl-master --openssldir=E:/openssl-master/openssl-master/ssl
         make
         make install
         ```
       - Sau khi cài đặt, thư viện OpenSSL sẽ nằm trong `E:/openssl-master/openssl-master/lib/mingw/x64` và các header trong `E:/openssl-master/openssl-master/include`.

2. **Cấu hình thư viện và biên dịch**:
   - Vào `Project` → `Project Options...` để thiết lập các cấu hình sau:
   
   #### Cài đặt thư viện wxWidgets
   - **Tab Parameters**:
     - **C++ Compiler**:
       Thêm vào ô `Compiler`:
       ```
       -D__WXDEBUG__ -D__WXMSW__ -g -O0 -mthreads -Wall
       ```
     - **C++ Linker**:
       Thêm vào ô `Linker`:
       ```
       -mthreads -Wl,--subsystem,windows -mwindows -lwxjpeg -lwxpng -lwxzlib -lrpcrt4 -loleaut32 -lole32 -luuid -lwinspool -lwinmm -lshell32 -lcomctl32 -lcomdlg32 -ladvapi32 -lwsock32 -lgdi32 -lwxtiff -lwxmsw32u_core -lwxbase32u -lwxexpat
       ```
   - **Tab Directories**:
     - **Library Directories**:
       ```
       E:\libwx\wxWidgets-3.2.0\lib\gcc1030TDM_x64_dll
       ```
     - **Include Directories**:
       ```
       E:\libwx\wxWidgets-3.2.0\include
       ```
   
   #### Cài đặt thư viện OpenSSL
   - **Tab Parameters**:
     - **C++ Linker**:
       Thêm vào ô `Linker` (kèm theo các tham số của wxWidgets):
       ```
       -L"E:\openssl-master\openssl-master\lib\mingw\x64" -lcrypto -lws2_32 -lcrypt32
       ```
   - **Tab Directories**:
     - **Library Directories**:
       ```
       E:\openssl-master\openssl-master\lib\mingw\x64
       ```
     - **Include Directories**:
       ```
       E:\openssl-master\openssl-master\include
       ```
3. **Tạo thư mục sao lưu**:
   - Tạo thư mục `E:/tai_lieu/c++/backups` để lưu bản sao lưu.
   - Đảm bảo ứng dụng có quyền đọc/ghi trên thư mục `E:/tai_lieu/c++`.

4. **Biên dịch và chạy**:
   - Biên dịch mã nguồn với trình biên dịch hỗ trợ C++11.
   - Chạy ứng dụng và kiểm tra chức năng sao lưu.

---

### Bước 3: Build và chạy chương trình
    1. Nhấn F9 để Build & Run chương trình
    2. Giao diện đăng nhập sẽ hiển thị
    3. Đăng nhập bằng tài khoản có sẵn hoặc đăng ký tài khoản mới
    4. Sau khi đăng nhập:
        - Người dùng sẽ truy cập giao diện khách hàng
        - Người dùng sẽ truy cập giao diện quản lý
