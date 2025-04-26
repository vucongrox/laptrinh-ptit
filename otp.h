#ifndef OTP_H
#define OTP_H

#include <string>
#include <vector>
#include <ctime>

class OTP {
public:
    // Sinh mã OTP 6 chữ số dựa trên thời gian
    static std::string generateTOTP(size_t digits = 6, int period = 30);
    static time_t getOtpGeneratedTime() { return otpGeneratedTime; }

private:
    // Secret cố định cho tất cả người dùng
    static const std::string secret;
    // Thời gian tạo OTP
    static time_t otpGeneratedTime;
    // Hàm tính HMAC-SHA1
    static std::vector<uint8_t> hmac_sha1(const std::string& key, const std::vector<uint8_t>& message);
};

#endif
