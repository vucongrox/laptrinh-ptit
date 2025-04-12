
# Hệ thống đăng nhập và đăng ký tài khoản và quản lý ví điểm thưởng




## Giới thiệu
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

## Chức năng dự án

### 1. Quản lý tài khoản người dùng

#### Đăng ký tài khoản
- Người dùng hoặc quản lý nhập thông tin để tạo tài khoản mới (username, mật khẩu, họ tên, ngày sinh, địa chỉ).
- Kiểm tra tính hợp lệ (username không trùng lặp, mật khẩu đủ mạnh).
- Hỗ trợ quản lý tạo tài khoản hộ với thông tin được cung cấp đầy đủ.

#### Đăng nhập
- Xác thực thông tin đăng nhập bằng username và mật khẩu.
- Kiểm tra nếu mật khẩu là tự sinh, yêu cầu người dùng đổi mật khẩu ngay lần đăng nhập đầu tiên.

#### Cập nhật thông tin
- Người dùng chỉnh sửa thông tin cá nhân (họ tên, ngày sinh, địa chỉ, mật khẩu), trừ username và ID.
- Yêu cầu xác nhận cập nhật thông qua mã OTP gửi đến người dùng.

#### Thay đổi mật khẩu
- Người dùng tự đổi mật khẩu sau khi xác thực mật khẩu hiện tại.
- Yêu cầu mật khẩu mới đủ mạnh (bao gồm chữ hoa, chữ thường, số và ký tự đặc biệt).
- Xác nhận thay đổi bằng mã OTP.

#### Sinh mật khẩu tự động
- Tạo mật khẩu ngẫu nhiên khi quản lý mở tài khoản mới mà người dùng không cung cấp mật khẩu.
- Đánh dấu mật khẩu tự sinh và yêu cầu đổi mật khẩu ở lần đăng nhập đầu tiên.

### 2. Quản lý ví điểm thưởng

#### Tạo và quản lý ví
- Mỗi người dùng được gán một ví với mã định danh duy nhất.
- Quản lý ví tổng để phát sinh và phân phối điểm cho các ví khác.

#### Giao dịch chuyển điểm
- Chuyển điểm từ ví A sang ví B với các bước kiểm tra:
  - Xác minh ví nguồn và ví đích tồn tại.
  - Yêu cầu xác thực giao dịch bằng mã OTP.
  - Kiểm tra số dư ví nguồn đủ để thực hiện chuyển điểm.
  - Thực hiện giao dịch nguyên tử: trừ điểm ví A, cộng điểm ví B.
  - Hủy giao dịch nếu có lỗi (OTP sai, số dư không đủ).

#### Theo dõi số dư và lịch sử giao dịch
- Hiển thị số dư hiện tại của ví.
- Cung cấp danh sách lịch sử giao dịch (mã giao dịch, ví nguồn, ví đích, số điểm, thời gian, trạng thái).

### 3. Bảo mật và xác thực

#### Mã hóa mật khẩu
- Lưu trữ mật khẩu dưới dạng băm sử dụng hàm băm (ví dụ: SHA-256) để đảm bảo an toàn.

#### Xác thực OTP
- Sinh mã OTP cho các thao tác quan trọng (cập nhật thông tin, giao dịch chuyển điểm).
- Gửi OTP (giả lập hiển thị trên giao diện) và kiểm tra tính hợp lệ, bao gồm thời gian hết hạn.

#### Phân quyền người dùng
- Người dùng thông thường: Chỉ truy cập và chỉnh sửa thông tin cá nhân, thực hiện giao dịch ví.
- Người dùng quản lý: Có quyền tạo tài khoản mới, chỉnh sửa thông tin người dùng, theo dõi danh sách người dùng.

### 4. Lưu trữ và sao lưu dữ liệu

#### Lưu trữ dữ liệu
- Lưu thông tin tài khoản và ví vào tệp (đề xuất một tệp duy nhất như `users.dat` và `wallets.dat`).

#### Sao lưu và phục hồi
- Tạo bản sao lưu tự động sau mỗi cập nhật dữ liệu (tệp chính và backup có nhãn thời gian).
- Hỗ trợ khôi phục dữ liệu từ bản sao lưu mới nhất nếu tệp chính bị lỗi.

### 5. Chức năng dành riêng cho quản lý

#### Theo dõi danh sách người dùng
- Hiển thị danh sách tất cả người dùng (trừ mật khẩu) với thông tin như username, ngày sinh, địa chỉ, số dư ví.

#### Tạo tài khoản mới
- Quản lý nhập thông tin và tạo tài khoản mới cho người dùng khác.

#### Chỉnh sửa thông tin người dùng
- Điều chỉnh thông tin tài khoản theo yêu cầu, với xác nhận bằng OTP gửi đến người dùng.

### 6. Giao diện và báo cáo

#### Giao diện người dùng
- Giao diện đăng nhập và đăng ký tài khoản.
- Giao diện khách hàng: Xem và chỉnh sửa thông tin cá nhân, quản lý ví.
- Giao diện quản lý: Quản lý danh sách người dùng, tạo tài khoản, chỉnh sửa thông tin.

#### Báo cáo
- Hiển thị báo cáo số dư ví và lịch sử giao dịch.
- Hỗ trợ lọc giao dịch theo thời gian hoặc trạng thái (thành công/thất bại).
## Hướng dẫn cài đặt và mô tả tệp tin

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
    - **OpenSSL**: Tùy chọn, vì dự án có thể băm mật khẩu (theo mô tả OTP và bảo mật trước).
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

####  Tab **Parameters**

#####  C++ Compiler

Thêm vào ô `Compiler`:

```text
-D__WXDEBUG__ -D__WXMSW__ -g -O0 -mthreads -Wall
```
#####  C++ Linker
```text
-mthreads -Wl,--subsystem,windows -mwindows -lwxjpeg -lwxpng -lwxzlib 
-lrpcrt4 -loleaut32 -lole32 -luuid -lwinspool -lwinmm -lshell32 
-lcomctl32 -lcomdlg32 -ladvapi32 -lwsock32 -lgdi32 -lwxtiff 
-lwxmsw32u_core -lwxbase32u -lwxexpat
```
#### Tab Directories
- Library Directories
ví dụ:
```text
E:\libwx\wxWidgets-3.2.0\lib\gcc1030TDM_x64_dll
```
- Include Directories
```text
E:\libwx\wxWidgets-3.2.0\include
```
### Bước 3: Build và chạy chương trình
    1. Nhấn F9 để Build & Run chương trình
    2. Giao diện đăng nhập sẽ hiển thị
    3. Đăng nhập bằng tài khoản có sẵn hoặc đăng ký tài khoản mới
    4. Sau khi đăng nhập:
        - Người dùng sẽ truy cập giao diện khách hàng
        - Người dùng sẽ truy cập giao diện quản lý
