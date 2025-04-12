
# Hệ thống đăng nhập và đăng ký tài khoản và quản lý ví điểm thưởng




## Giới thiệu
Hệ thống Quản lý Tài khoản và Ví Điểm thưởng là một giải pháp phần mềm toàn diện được thiết kế để cung cấp các chức năng quản lý tài khoản người dùng và hệ thống giao dịch điểm thưởng một cách an toàn, hiệu quả. Dự án tập trung vào ba trụ cột chính:

Quản lý tài khoản: Hỗ trợ đăng ký, đăng nhập, và cập nhật thông tin người dùng với cơ chế bảo mật tiên tiến, bao gồm xác thực bằng mật khẩu băm (hash) và OTP (One-Time Password).
Hệ thống ví điểm thưởng: Cho phép người dùng thực hiện các giao dịch chuyển điểm giữa các ví, theo dõi số dư, và xem lịch sử giao dịch với tính toàn vẹn dữ liệu được đảm bảo.
Phân quyền linh hoạt: Phân tách rõ ràng giữa người dùng thông thường (quản lý thông tin cá nhân) và người dùng quản lý (thêm tài khoản, chỉnh sửa thông tin, giám sát hệ thống).
Dự án được xây dựng với trọng tâm vào bảo mật, khả năng mở rộng, và trải nghiệm người dùng. Dữ liệu được lưu trữ an toàn với cơ chế sao lưu tự động, đảm bảo tính sẵn sàng và khôi phục nhanh chóng khi cần thiết. Hệ thống hướng đến việc cung cấp một nền tảng đáng tin cậy cho các ứng dụng quản lý điểm thưởng trong nhiều lĩnh vực, từ thương mại điện tử đến chương trình khách hàng thân thiết.

## Các thành viên
Thành viên          | Công việc được giao
--------------------|-------------------------------------------------------------------------------------
congvu             | Xây dựng nền tảng cơ bản (lớp Customer, User, Manager); phát triển hàm main; triển khai và sửa lỗi các chức năng người dùng (getList, regis, loadFromID); sửa lỗi chức năng giao dịch (transaction).
truong-ngo-edu-0912| Thiết kế giao diện đăng nhập; xây dựng logic đăng nhập; phát triển các chức năng người dùng (updateInfor, genPass); triển khai hệ thống ví (wallet); thêm quản lý ví (WalletManager) và giao diện quản lý ví.
K24dtcn380         | Thiết kế giao diện khách hàng (Customer); phát triển các chức năng khách hàng; triển khai hệ thống ví (wallet); thêm ví khách hàng (WalletCustomer); viết mã cho chức năng giao dịch (transaction).
namnh1988          | Thiết kế giao diện quản lý (Manager); phát triển các chức năng quản lý; triển khai và sửa lỗi các chức năng người dùng (getList, regis, loadFromID); xây dựng cơ chế xác thực OTP.

## chức năng dự án
### 1. Quản lý tài khoản người dùng
#### Đăng ký tài khoản: 
Người dùng hoặc quản lý nhập thông tin để tạo tài khoản mới (username, mật khẩu, họ tên, ngày sinh, địa chỉ).
Kiểm tra tính hợp lệ (username không trùng, mật khẩu đủ mạnh).
Hỗ trợ quản lý tạo tài khoản hộ với thông tin được cung cấp.
#### Đăng nhập:
Xác thực thông tin đăng nhập (username và mật khẩu).
Kiểm tra mật khẩu tự sinh và yêu cầu đổi mật khẩu ở lần đăng nhập đầu tiên (nếu áp dụng).
#### Cập nhật thông tin:
Người dùng chỉnh sửa thông tin cá nhân (họ tên, ngày sinh, địa chỉ, mật khẩu), trừ username và ID.
Xác nhận cập nhật bằng mã OTP.
#### Thay đổi mật khẩu:
Người dùng tự đổi mật khẩu sau khi xác thực mật khẩu cũ.
Yêu cầu mật khẩu mới đủ mạnh (chữ hoa, chữ thường, số, ký tự đặc biệt).
Xác nhận cập nhật bằng mã OTP.
#### Sinh mật khẩu tự động:
Tạo mật khẩu ngẫu nhiên khi quản lý mở tài khoản mới mà người dùng không cung cấp mật khẩu.
Đánh dấu mật khẩu tự sinh và yêu cầu đổi ở lần đăng nhập đầu tiên.
